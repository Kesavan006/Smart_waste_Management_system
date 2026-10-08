//=========================================================
// SmartBin.ino
// Part 1 (Lines 1 - 120)
//=========================================================

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//================ OLED ======================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

//================ Ultrasonic =================

#define TRIG_PIN 5
#define ECHO_PIN 18

//================ LEDs =======================

#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 27

//================ Buzzer =====================

#define BUZZER 14

//================ Bin ========================

const float BIN_HEIGHT = 30.0;

//================ WiFi =======================

const char* ssid = "Wokwi-GUEST";
const char* wifiPassword = "";

//================ MQTT =======================
// IMPORTANT: Never commit real MQTT credentials to GitHub.
// Replace the placeholders below locally before running with a private broker.

const char* mqttServer =
"25ee5ac599fe4b0ebee3eeafedd9d824.s1.eu.hivemq.cloud";

const int mqttPort = 8883;

const char* mqttUser = "YOUR_HIVEMQ_USERNAME";

const char* mqttPassword = "YOUR_HIVEMQ_PASSWORD";

//================ MQTT Client =================

WiFiClientSecure espClient;
PubSubClient client(espClient);

//================ Variables ===================

float distance = 0.0;

int fillPercent = 0;

unsigned long previousPublish = 0;

const unsigned long publishInterval = 5000;

//================ Function Prototypes =========

void connectWiFi();

void connectMQTT();

float readDistance();

int calculateFillLevel(float distance);

void updateDisplay();

void updateIndicators();

void publishData(float distance, int fillLevel);

//================ Setup =======================

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Wire.begin(21, 22);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C))
  {
    Serial.println("OLED Failed");

    while (true);
  }

  display.clearDisplay();
  display.display();

  connectWiFi();

  connectMQTT();

  Serial.println();
  Serial.println("=================================");
  Serial.println(" Smart Bin Started Successfully ");
  Serial.println("=================================");
}

//================ Loop ========================

void loop()
{
  //=========================================================
// SmartBin.ino
// Part 2 (Loop + Sensor Functions)
//=========================================================

  // Reconnect MQTT if disconnected
  if (!client.connected())
  {
    connectMQTT();
  }

  client.loop();

  // Read Sensor
  distance = readDistance();

  // Calculate Fill Level
  fillPercent = calculateFillLevel(distance);

  // Update OLED
  updateDisplay();

  // Update LEDs & Buzzer
  updateIndicators();

  // Print to Serial Monitor
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.print(" cm");

  Serial.print("   Fill : ");
  Serial.print(fillPercent);
  Serial.println("%");

  // Publish every 5 seconds
  if (millis() - previousPublish >= publishInterval)
  {
    previousPublish = millis();

    publishData(distance, fillPercent);
  }

  delay(500);
}

//=========================================================
// Read Ultrasonic Distance
//=========================================================

float readDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration =
      pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    return BIN_HEIGHT;
  }

  float d = duration * 0.0343 / 2.0;

  return d;
}

//=========================================================
// Calculate Fill Level
//=========================================================

int calculateFillLevel(float d)
{
  d = constrain(d, 0, BIN_HEIGHT);

  int fill =
      ((BIN_HEIGHT - d) / BIN_HEIGHT) * 100;

  fill = constrain(fill, 0, 100);

  return fill;
}
//=========================================================
// SmartBin.ino
// Part 3 (OLED + LEDs + Buzzer)
//=========================================================

//---------------------------------------------------------
// Update OLED Display
//---------------------------------------------------------

void updateDisplay()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setCursor(20,0);
  display.println("SMART BIN");

  // Distance
  display.setCursor(0,18);
  display.print("Distance:");

  display.setCursor(70,18);
  display.print(distance,1);
  display.print(" cm");

  // Fill Level
  display.setCursor(0,34);
  display.print("Fill:");

  display.setCursor(70,34);
  display.print(fillPercent);
  display.print("%");

  // Status
  display.setCursor(0,48);

  if(fillPercent < 40)
  {
    display.print("Status: LOW");
  }
  else if(fillPercent < 80)
  {
    display.print("Status: MEDIUM");
  }
  else
  {
    display.print("Status: FULL");
  }

  display.display();
}

//---------------------------------------------------------
// Update LEDs and Buzzer
//---------------------------------------------------------

void updateIndicators()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

  noTone(BUZZER);

  if(fillPercent < 40)
  {
    digitalWrite(GREEN_LED, HIGH);
  }
  else if(fillPercent < 80)
  {
    digitalWrite(YELLOW_LED, HIGH);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 1000);
  }
}
//=========================================================
// SmartBin.ino
// Part 4 (WiFi + MQTT + Publish Data)
//=========================================================

//---------------------------------------------------------
// Connect to WiFi
//---------------------------------------------------------

void connectWiFi()
{
  Serial.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

//---------------------------------------------------------
// Connect to MQTT
//---------------------------------------------------------

void connectMQTT()
{
  espClient.setInsecure();   // For testing in Wokwi

  client.setServer(mqttServer, mqttPort);

  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");

    if (client.connect("ESP32_BIN001",
                       mqttUser,
                       mqttPassword))
    {
      Serial.println("Connected!");
    }
    else
    {
      Serial.print("Failed. State = ");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

//---------------------------------------------------------
// Publish Sensor Data
//---------------------------------------------------------

void publishData(float distance, int fillLevel)
{
  String status;

  if (fillLevel < 40)
    status = "LOW";
  else if (fillLevel < 80)
    status = "MEDIUM";
  else
    status = "FULL";

  String payload = "{";
  payload += "\"bin_id\":\"BIN001\",";
  payload += "\"distance\":";
  payload += String(distance, 1);
  payload += ",";
  payload += "\"fill\":";
  payload += String(fillLevel);
  payload += ",";
  payload += "\"status\":\"";
  payload += status;
  payload += "\"}";

  Serial.println("------------------------------");
  Serial.println("Publishing MQTT Message");
  Serial.println(payload);

  if (client.publish("smartbin/bin001/data", payload.c_str()))
  {
    Serial.println("Publish Successful");
  }
  else
  {
    Serial.println("Publish Failed");
  }

  Serial.println("------------------------------");
}