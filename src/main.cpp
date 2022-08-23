#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// #define DHTPIN D5
// #define DHTTYPE DHT22 // DHT 22 (AM2302)
// DHT_Unified dht(DHTPIN, DHTTYPE);
// uint32_t delayMS;

/* 1. Define the WiFi credentials */
#define WIFI_SSID "WIFI@ITERA-IOT"
#define WIFI_PASSWORD "IOT-ITERA"
/* 2. Define the API Key */
#define API_KEY "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM"
/* 3. Define the RTDB URL */
#define DATABASE_URL "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

#define USER_EMAIL "ahmad@gmail.com"
#define USER_PASSWORD "yusuf1112"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;

bool bVal1, bVal2, bVal3;

float nilaitemp, nilaihum;

bool nilaigerakan;

void setup()
{
  Serial.begin(115200);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT); // ini relay sensor pir
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, INPUT);

  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW); // ini yang sensor pir
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);

  // dht.temperature().getSensor(&sensor);
  // Serial.println(sensor.name);
  // Serial.println(sensor.sensor_id);

  // dht.humidity().getSensor(&sensor);
  // Serial.println(sensor.name);
  // Serial.println(sensor.sensor_id);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

#if defined(ESP8266)
  // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
  fbdo.setBSSLBufferSize(4096, 4096);
#endif

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

  // dht.begin();
  // sensor_t sensor;

  // delayMS = sensor.min_delay / 1000;
}

void loop()
{

  nilaigerakan = digitalRead(D5);
  Serial.print("gerakan:");
  Serial.print(nilaigerakan);

  if (nilaigerakan == HIGH)
  {
    digitalWrite(D1, HIGH);
    delay(1);
  }
  else
  {
    digitalWrite(D1, LOW);
    delay(1);
  }

  // Firebase.ready() should be called repeatedly to handle authentication tasks.
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Serial.printf("Get relay1... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_1"), &bVal1) ? bVal1 ? "true" : "false" : fbdo.errorReason().c_str());

    // Serial.printf("Get relay2... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_2"), &bVal2) ? bVal2 ? "true" : "false" : fbdo.errorReason().c_str());

    // Serial.printf("Get relay3... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_3"), &bVal3) ? bVal3 ? "true" : "false" : fbdo.errorReason().c_str());

    // sensors_event_t event;
    // dht.temperature().getEvent(&event);
    // nilaitemp = event.temperature;

    if (Firebase.RTDB.setBool(&fbdo, "/data_iot_device/device_a/relay_4", nilaigerakan))
      Serial.print("gerakan terupload...");
    else
      Serial.println(fbdo.errorReason());

    // // dht.humidity().getEvent(&event);
    // dht.humidity().getEvent(&event);
    // nilaihum = event.relative_humidity;
    // if (Firebase.RTDB.setFloat(&fbdo, "/data_iot_device/device_a/sensor_2", nilaihum))
    //   Serial.print("hum terupload...");
    // else
    //   Serial.println(fbdo.errorReason());

    Serial.println();
  }
  digitalWrite(D0, bVal1);
  // digitalWrite(D1, bVal2);
  digitalWrite(D2, bVal3);
}