//Viral science www.youtube.com/c/viralscience
//Temperature sensor
/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how value can be pushed from Arduino to
 * the Blynk App.
 *
 * WARNING :
 * For this example you'll need SimpleTimer library:
 *   https://github.com/jfturcot/SimpleTimer
 * and Adafruit DHT sensor library:
 *   https://github.com/adafruit/DHT-sensor-library
 *
 * App project setup:
 *   Value Display widget attached to V5
 *   Value Display widget attached to V6
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "link.firebaseio.com"
#define FIREBASE_AUTH "secret"
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "pass"
#include <Wire.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "secret"; //Enter the Auth code which was send by Blink
#define DHTPIN 2
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
float a = 0.000091367;
float b = -0.01452993;
float c = 1.77623089;
float d = -14.17403758;
float calcT(float t){
  return a*pow(t,3)+b*pow(t,2)+c*t+d;
}
float calcH(float h){
  return a*pow(h,3)+b*pow(h,2)+c*h+d;
}
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, calcH(h));  //V5 is for Humidity
  Blynk.virtualWrite(V5, calcT(t));  //V6 is for Temperature
  StaticJsonBuffer<50> jsonBuffer;
  JsonObject& timeStampObject = jsonBuffer.createObject();
  timeStampObject[".sv"] = "timestamp";
  Firebase.set("timeStampDHT11", timeStampObject);
  Firebase.setFloat("temperaturaDHT11", calcT(t));
  // handle error
  if (Firebase.failed()) {
      Serial.print("temperatura failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Firebase.setFloat("umiditateDHT11", calcH(h));
  // handle error
  if (Firebase.failed()) {
      Serial.print("umiditate failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, WIFI_SSID, WIFI_PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
