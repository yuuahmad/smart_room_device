#include <Arduino.h>
// include board
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

// include firebase dan wifi
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define WIFI_SSID "WIFI@ITERA-IOT" // ini adalah nama wifi
#define WIFI_PASSWORD "IOT-ITERA"  // dan ini adalah passwordnya. kosongkan bagian ini kalau tidak pakai password
#define API_KEY "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM"
#define DATABASE_URL "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "ahmad@gmail.com"
#define USER_PASSWORD "yusuf1112"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int nilaitambah = 0;

void setup()
{
  // mulai komunikasi serial
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  bool relay1data, relay2data, relay3data, relay4data;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(3000);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  Firebase.setDoubleDigits(5);
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, "/data_iot_device/device_a/relay_1", &relay1data) ? relay1data ? digitalWrite(D0, HIGH) : digitalWrite(D0, LOW) : fbdo.errorReason().c_str());
  }
}