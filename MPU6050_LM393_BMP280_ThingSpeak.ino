#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>

/* WiFi Credentials */
const char* wifiName = "YOUR_WIFI_NAME";
const char* wifiPass = "YOUR_WIFI_PASSWORD";

/* ThingSpeak Details */
const char* tsServer = "api.thingspeak.com";
String tsKey = "YOUR_THINGSPEAK_API_KEY";

WiFiClient tsClient;

/* Sensor Objects */
Adafruit_BMP280 bmpSensor;
MPU6050 motionSensor;

/* Motor Speed Sensor */
#define MOTOR_PIN D5
volatile unsigned int rpmPulse = 0;

/* Interrupt Function */
void pulseDetect() {
  rpmPulse++;
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  Wire.begin();

  pinMode(MOTOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(MOTOR_PIN), pulseDetect, RISING);

  if (!bmpSensor.begin(0x76)) {
    Serial.println("BMP280 not detected");
  }

  motionSensor.initialize();

  Serial.print("Connecting to WiFi");
  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
}

void loop() {

  /* MPU6050 Data */
  int16_t xAcc, yAcc, zAcc;
  motionSensor.getAcceleration(&xAcc, &yAcc, &zAcc);

  /* BMP280 Data */
  float tempValue = bmpSensor.readTemperature();
  float pressValue = bmpSensor.readPressure() / 100.0;

  /* Motor Speed Calculation */
  rpmPulse = 0;
  delay(1000);
  int motorRPM = rpmPulse * 60;

  /* Send Data to ThingSpeak */
  if (tsClient.connect(tsServer, 80)) {

    String dataURL = "/update?api_key=" + tsKey;
    dataURL += "&field1=" + String(xAcc);
    dataURL += "&field2=" + String(yAcc);
    dataURL += "&field3=" + String(tempValue);
    dataURL += "&field4=" + String(pressValue);
    dataURL += "&field5=" + String(motorRPM);

    tsClient.print("GET " + dataURL + " HTTP/1.1\r\n");
    tsClient.print("Host: api.thingspeak.com\r\n");
    tsClient.print("Connection: close\r\n\r\n");

    Serial.println("Data Sent to ThingSpeak");
  }

  delay(15000);   // Required delay for ThingSpeak
}
