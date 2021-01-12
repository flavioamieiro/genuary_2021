#include <GxEPD2_BW.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <StreamUtils.h>
#include "particle.h"

#define COLS 12
#define LINES 12
#define NUM_VECTORS (COLS*LINES)
#define NUM_PARTICLES 30

GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));
WiFiClientSecure client;
DynamicJsonDocument doc(4096);

struct Wind{
    int speed;
    float angle;
};

int loop_count = 0;

int colsize = W/COLS;
int linesize = H/LINES;

const char* ssid     = "";
const char* password = "";

struct Wind forces[NUM_VECTORS];
Particle particles[NUM_PARTICLES];

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  initDisplay();
  fullRefresh();
  initVectors();
  initParticles();
}

void initDisplay() {
  display.init(0, true, 2, false);
  display.setRotation(0);
}

void fullRefresh() {
  display.clearScreen();
}

void initVectors() {
  int d = 1;
  int i = 0;
  while (i < NUM_VECTORS) {
    getWindData(d);
    JsonArray arr = doc.as<JsonArray>();
    for (JsonObject value : arr) {
      int speed = value["wind_speed"].as<int>();
      float angle = value["wind_direction"].as<float>();
      struct Wind w;
      w.speed = speed;
      w.angle = angle * (PI / 180);
      forces[i] = w;
      i++;
    }
    d++;
    delay(1000);
  }
}

void initParticles() {
  for (int i=0; i<NUM_PARTICLES; i++) {
    Particle p(random(0, W), random(0, H));
    particles[i] = p;
  }
};

void getWindData(int day) {
  Serial.print("Downloading data for ");
  Serial.print(day);
  Serial.println("/12/2020");
  if (client.connect("www.metaweather.com", 443)) {
    char buf[75];
    sprintf(buf, "GET https://www.metaweather.com/api/location/638242/2020/12/%02d/ HTTP/1.0", day);
    client.println(buf);
    client.println("Host: www.metaweather.com");
    client.println("Connection: close");
    client.println();
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }
    }
    ReadLoggingStream loggingStream(client, Serial);
    deserializeJson(doc, client);
  } else {
    Serial.println("Connection failed!");
  }
  client.stop();
};

void loop() {
  if (loop_count % 100 == 0) {
    fullRefresh();
  }

  display.fillScreen(GxEPD_WHITE);
  drawVectors();

  for (int i=0; i<NUM_PARTICLES; i++){
    Particle& p = particles[i];
    int col = p.x/colsize;
    int line = p.y/linesize;
    int idx = col + (line * COLS);
    Wind w = forces[idx];
    #ifdef DEBUG
    Serial.print("x: ");
    Serial.print(p.x);
    Serial.print("| y: ");
    Serial.print(p.y);
    Serial.print("| col: ");
    Serial.print(col);
    Serial.print("| line: ");
    Serial.print(line);
    Serial.print("| idx: ");
    Serial.print(idx);
    Serial.print("| prev xspeed: ");
    Serial.print(p.velx);
    Serial.print("| prev yspeed: ");
    Serial.print(p.vely);
    Serial.print("| adding speed: ");
    Serial.print(w.speed);
    Serial.print("| adding angle: ");
    Serial.print(w.angle);
    Serial.println();
    #endif
    p.update();
    showParticle(p);
    p.applyForce(w.speed, w.angle);
  }
  display.displayWindow(0, 0, display.width(), display.height());
  loop_count++;
}

void drawVectors() {
  for (int i=0; i<NUM_VECTORS; i++) {
    int col = i % COLS;
    int line = i / COLS;
    int x = colsize/2 + col * colsize;
    int y = linesize/2  + line * linesize;
    struct Wind w = forces[i];
    int size = w.speed * 5;
    display.drawLine(x, y, x+size*cos(w.angle), y+size*sin(w.angle), GxEPD_BLACK);
  }
}

void showParticle(Particle a) {
  display.fillCircle(a.x, a.y, a.r, GxEPD_BLACK);
}
