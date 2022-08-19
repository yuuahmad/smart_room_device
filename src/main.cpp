// // #include <Arduino.h>
// // // include board
// // // #if defined(ESP32)
// // // #include <WiFi.h>
// // // #elif defined(ESP8266)
// // // #include <ESP8266WiFi.h>
// // // #endif

// // #include <Firebase_ESP_Client.h>
// // #include <addons/TokenHelper.h>
// // #include <addons/RTDBHelper.h>

// // // include untuk mendapatkan nilai dht
// // #include <Adafruit_Sensor.h>
// // #include <DHT.h>
// // #include <DHT_U.h>

// // // perbaiki delay
// // // Include WiFi library
// // #if defined(ESP32)
// // #include <WiFi.h>
// // #elif defined(ESP8266)
// // #include <ESP8266WiFi.h>
// // #endif

// // // Include Firebase library (this library)
// // #include <Firebase_ESP_Client.h>

// // // Define the Firebase Data object
// // FirebaseData fbdo;
// // // Define the FirebaseAuth data for authentication data
// // FirebaseAuth auth;
// // // Define the FirebaseConfig data for config data
// // FirebaseConfig config;
// // // Assign the project host and api key
// // config.host = "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app";
// // config.api_key = "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM";
// // // Assign the user sign in credentials
// // auth.user.email = "ahmad@gmail.com";
// // auth.user.password = "yusuf1112";
// // // Initialize the library with the Firebase authen and config.
// // Firebase.begin(&config, &auth);

// // // Optional, set AP reconnection in setup()
// // Firebase.reconnectWiFi(true);

// // // Optional, set number of error retry
// // Firebase.RTDB.setMaxRetry(&fbdo, 3);

// // // Optional, set number of error resumable queues
// // Firebase.RTDB.setMaxErrorQueue(&fbdo, 30);

// // // Optional, use classic HTTP GET and POST requests.
// // // This option allows get and delete functions (PUT and DELETE HTTP requests) works for
// // // device connected behind the Firewall that allows only GET and POST requests.
// // Firebase.RTDB.enableClassicRequest(&fbdo, true);

// // #if defined(ESP8266)
// // fbdo.setBSSLBufferSize(1024, 1024); // minimum size is 512 bytes, maximum size is 16384 bytes
// // #endif
// // fbdo.setResponseSize(1024); // minimum size is 1024 bytes

// // // include firebase dan wifi
// // #define WIFI_SSID "WIFI@ITERA-IOT" // ini adalah nama wifi
// // #define WIFI_PASSWORD "IOT-ITERA"  // dan ini adalah passwordnya. kosongkan bagian ini kalau tidak pakai password
// // // #define API_KEY "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM"
// // // #define DATABASE_URL "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
// // // #define USER_EMAIL "ahmad@gmail.com"
// // // #define USER_PASSWORD "yusuf1112"

// // // setup sensor dht
// // #define DHTPIN D5     // Digital pin connected to the DHT sensor
// // #define DHTTYPE DHT22 // DHT 22 (AM2302)
// // DHT_Unified dht(DHTPIN, DHTTYPE);
// // float temperatur, kelembaban;

// // // Define Firebase Data object
// // FirebaseData fbdo;
// // // Database main path (to be updated in setup with the user UID)
// // // String databasePath = "/data_iot_device/device_a";
// // // Database child nodes
// // // String tempPath = "/sensor_1";
// // // String humPath = "/sensor_2";
// // // String presPath = "/pressure";
// // // String timePath = "/timestamp";
// // // FirebaseJson json;

// // FirebaseAuth auth;
// // FirebaseConfig config;
// // unsigned long sendDataPrevMillis = 0;
// // bool relay1data, relay2data, relay3data, relay4data;

// // void setup()
// // {
// //   // mulai komunikasi serial
// //   Serial.begin(115200);
// //   pinMode(D0, OUTPUT);
// //   pinMode(D1, OUTPUT);
// //   pinMode(D2, OUTPUT);
// //   pinMode(D3, OUTPUT);
// //   pinMode(D4, INPUT);

// //   // setup dht
// //   dht.begin();

// //   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
// //   Serial.print("Connecting to Wi-Fi");
// //   while (WiFi.status() != WL_CONNECTED)
// //   {
// //     Serial.print(".");
// //     delay(3000);
// //   }
// //   Serial.println();
// //   Serial.print("Connected with IP: ");
// //   Serial.println(WiFi.localIP());
// //   delay(1000);

// //   Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
// //   config.api_key = API_KEY;
// //   auth.user.email = USER_EMAIL;
// //   auth.user.password = USER_PASSWORD;
// //   config.database_url = DATABASE_URL;
// //   config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
// //   Firebase.begin(&config, &auth);
// //   Firebase.reconnectWiFi(true);
// //   Firebase.setDoubleDigits(5);

// //   digitalWrite(D0, LOW);
// //   digitalWrite(D1, LOW);
// //   digitalWrite(D2, LOW);
// //   digitalWrite(D3, LOW);
// // }

// // void loop()
// // {
// //   // set sensor tempertature
// //   sensors_event_t event;

// //   if (Firebase.ready() && (millis() - sendDataPrevMillis > 3000 || sendDataPrevMillis == 0))
// //   {
// //     sendDataPrevMillis = millis();

// //     Serial.printf("Get r1 ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_1"), &relay1data) ? relay1data ? "true" : "false" : fbdo.errorReason().c_str());
// //     Serial.printf("Get r2 ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_2"), &relay2data) ? relay2data ? "true" : "false" : fbdo.errorReason().c_str());
// //     Serial.printf("Get r3 ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_3"), &relay3data) ? relay3data ? "true" : "false" : fbdo.errorReason().c_str());
// //     // realay 4 adalah relay untuk menghidupkan lampu dari sensor pir dan kirim datanya ke firebase
// //     // relay4data = digitalRead(D4);
// //     // Serial.printf("Set bool r4... %s\n", Firebase.RTDB.setBool(&fbdo, "/data_iot_device/device_a/relay_4", &relay4data) ? "ok" : fbdo.errorReason().c_str());
// //     // dapatkan nilai temp
// //     dht.temperature().getEvent(&event);
// //     if (isnan(event.temperature))
// //       Serial.println(F("Error reading temperature!"));
// //     else
// //     {
// //       Serial.print(F("temp c: "));
// //       Serial.println(event.temperature);
// //       temperatur = event.temperature;
// //     }
// //     // daptakan nilai hum
// //     dht.humidity().getEvent(&event);
// //     if (isnan(event.relative_humidity))
// //       Serial.println(F("Error reading humidity!"));
// //     else
// //     {
// //       Serial.print(F("hum c: "));
// //       Serial.println(event.relative_humidity);
// //       kelembaban = event.relative_humidity;
// //     }
// //     // /***** kumpulkan data pada satu  ****/
// //     // jsonRelay1.set("/relay_1", relay1data);
// //     // jsonRelay2.set("/relay_2", relay2data);
// //     // jsonRelay3.set("/relay_3", relay3data);
// //     // jsonRelay4.set("/relay_4", relay4data);
// //     // jsonSuhu.set("/sensor_1", relay4data);
// //     // jsonTemp.set("/sensor_2", relay4data);

// //     // // kim data ke firebase
// //     // Firebase.updateNode(firebaseData, "/datasensor", Daya1);
// //     // Firebase.updateNode(firebaseData, "/datasensor", Daya2);
// //     // Firebase.updateNode(firebaseData, "/datasensor", SuhuPV);
// //     // Firebase.updateNode(firebaseData, "/datasensor", Vair);

// //     // json.set(tempPath.c_str(), String(temperatur));
// //     // json.set(humPath.c_str(), String(kelembaban));
// //     // Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, databasePath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
// //   }
// //   digitalWrite(D0, relay1data);
// //   digitalWrite(D1, relay2data);
// //   digitalWrite(D2, relay3data);
// // }

// /**
//  * Created by K. Suwatchai (Mobizt)
//  *
//  * Email: k_suwatchai@hotmail.com
//  *
//  * Github: https://github.com/mobizt/Firebase-ESP-Client
//  *
//  * Copyright (c) 2022 mobizt
//  *
//  */

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

// // include untuk mendapatkan nilai dht
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "WIFI@ITERA-IOT"
#define WIFI_PASSWORD "IOT-ITERA"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM"

/* 3. Define the RTDB URL */
#define DATABASE_URL "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "ahmad@gmail.com"
#define USER_PASSWORD "yusuf1112"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
bool bVal1, bVal2, bVal3;

// // setup sensor dht
#define DHTPIN D5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
float suhuVal = 0;
float humVal = 0;
uint32_t delayMS;

void setup()
{

  Serial.begin(115200);
  dht.begin();
  sensor_t sensor;

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);

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

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  //   //////////////////////////////////////////////////////////////////////////////////////////////
  //   // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  //   // otherwise the SSL connection will fail.
  //   //////////////////////////////////////////////////////////////////////////////////////////////

  // #if defined(ESP8266)
  //   // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
  //   fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
  // #endif

  //   // Limit the size of response payload to be collected in FirebaseData
  //   fbdo.setResponseSize(2048);

  //   Firebase.begin(&config, &auth);

  //   // Comment or pass false value when WiFi reconnection will control by your code or third party library
  //   Firebase.reconnectWiFi(true);

  //   Firebase.setDoubleDigits(5);

  //   config.timeout.serverResponse = 10 * 1000;

  /** Timeout options.

  //WiFi reconnect timeout (interval) in ms (10 sec - 5 min) when WiFi disconnected.
  config.timeout.wifiReconnect = 10 * 1000;

  //Socket connection and SSL handshake timeout in ms (1 sec - 1 min).
  config.timeout.socketConnection = 10 * 1000;

  //Server response read timeout in ms (1 sec - 1 min).
  config.timeout.serverResponse = 10 * 1000;

  //RTDB Stream keep-alive timeout in ms (20 sec - 2 min) when no server's keep-alive event data received.
  config.timeout.rtdbKeepAlive = 45 * 1000;

  //RTDB Stream reconnect timeout (interval) in ms (1 sec - 1 min) when RTDB Stream closed and want to resume.
  config.timeout.rtdbStreamReconnect = 1 * 1000;

  //RTDB Stream error notification timeout (interval) in ms (3 sec - 30 sec). It determines how often the readStream
  //will return false (error) when it called repeatedly in loop.
  config.timeout.rtdbStreamError = 3 * 1000;

  Note:
  The function that starting the new TCP session i.e. first time server connection or previous session was closed, the function won't exit until the
  time of config.timeout.socketConnection.

  You can also set the TCP data sending retry with
  config.tcp_data_sending_retry = 1;

  */
  delayMS = sensor.min_delay / 1000;
}
// unsigned int state=1;
void loop()
{

  switch (state)
  {
  case 0:
    sensors_event_t event;
    delay(delayMS);

    dht.temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
      Serial.println(F("Error reading temperature!"));
      suhuVal = 0;
    }
    else
    {
      Serial.print(F("temp c: "));
      Serial.println(event.temperature);
      suhuVal = event.temperature;
    }
    // daptakan nilai hum
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
      Serial.println(F("Error reading humidity!"));
      humVal = 0;
    }
    else
    {
      Serial.print(F("hum c: "));
      Serial.println(event.relative_humidity);
      humVal = event.relative_humidity;
    }

    state = 1;
    break;
  case 1:
    sendDataPrevMillis = millis();
    if (Firebase.ready()) //&& (millis() - sendDataPrevMillis > 3000
    {

      // Serial.printf("Set bool... %s\n", Firebase.RTDB.setBool(&fbdo, F("/test/bool"), count % 2 == 0) ? "ok" : fbdo.errorReason().c_str());

      // Serial.printf("Get bool... %s\n", Firebase.RTDB.getBool(&fbdo, FPSTR("/test/bool")) ? fbdo.to<bool>() ? "true" : "false" : fbdo.errorReason().c_str());

      Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_1"), &bVal1) ? bVal1 ? "true" : "false" : fbdo.errorReason().c_str());

      // bool bVal2;
      Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_2"), &bVal2) ? bVal2 ? "true" : "false" : fbdo.errorReason().c_str());
      // digitalWrite(D1, bVal2);
      // bool bVal3;
      Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/data_iot_device/device_a/relay_3"), &bVal3) ? bVal3 ? "true" : "false" : fbdo.errorReason().c_str());
      // digitalWrite(D2, bVal3);

      Serial.printf("Set temp... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/data_iot_device/device_a/sensor_1"), suhuVal) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set temp... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/data_iot_device/device_a/sensor_2"), humVal) ? "ok" : fbdo.errorReason().c_str());

      // Serial.printf("Get int... %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/int")) ? String(fbdo.to<int>()).c_str() : fbdo.errorReason().c_str());

      // int iVal = 0;
      // Serial.printf("Get int ref... %s\n", Firebase.RTDB.getInt(&fbdo, F("/test/int"), &iVal) ? String(iVal).c_str() : fbdo.errorReason().c_str());

      // Serial.printf("Set float... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/test/float"), count + 10.2) ? "ok" : fbdo.errorReason().c_str());

      // Serial.printf("Get float... %s\n", Firebase.RTDB.getFloat(&fbdo, F("/test/float")) ? String(fbdo.to<float>()).c_str() : fbdo.errorReason().c_str());

      // Serial.printf("Set double... %s\n", Firebase.RTDB.setDouble(&fbdo, F("/test/double"), count + 35.517549723765) ? "ok" : fbdo.errorReason().c_str());

      // Serial.printf("Get double... %s\n", Firebase.RTDB.getDouble(&fbdo, F("/test/double")) ? String(fbdo.to<double>()).c_str() : fbdo.errorReason().c_str());

      // Serial.printf("Set string... %s\n", Firebase.RTDB.setString(&fbdo, F("/test/string"), F("Hello World!")) ? "ok" : fbdo.errorReason().c_str());

      // Serial.printf("Get string... %s\n", Firebase.RTDB.getString(&fbdo, F("/test/string")) ? fbdo.to<const char *>() : fbdo.errorReason().c_str());

      // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Edit_Parse.ino
      FirebaseJson json;

      // if (count == 0)
      // {
      //   json.set("value/round/" + String(count), F("cool!"));
      //   json.set(F("value/ts/.sv"), F("timestamp"));
      //   Serial.printf("Set json... %s\n", Firebase.RTDB.set(&fbdo, F("/test/json"), &json) ? "ok" : fbdo.errorReason().c_str());
      // }
      // else
      // {
      //   json.add(String(count), F("smart!"));
      //   Serial.printf("Update node... %s\n", Firebase.RTDB.updateNode(&fbdo, F("/test/json/value/round"), &json) ? "ok" : fbdo.errorReason().c_str());
      // }

      Serial.println();
      sendDataPrevMillis = 0;
      state = 1;
    }
    break;

    // Firebase.ready() should be called repeatedly to handle authentication tasks.

    // For generic set/get functions.

    // For generic set, use Firebase.RTDB.set(&fbdo, <path>, <any variable or value>)

    // For generic get, use Firebase.RTDB.get(&fbdo, <path>).
    // And check its type with fbdo.dataType() or fbdo.dataTypeEnum() and
    // cast the value from it e.g. fbdo.to<int>(), fbdo.to<std::string>().

    // The function, fbdo.dataType() returns types String e.g. string, boolean,
    // int, float, double, json, array, blob, file and null.

    // The function, fbdo.dataTypeEnum() returns type enum (number) e.g. fb_esp_rtdb_data_type_null (1),
    // fb_esp_rtdb_data_type_integer, fb_esp_rtdb_data_type_float, fb_esp_rtdb_data_type_double,
    // fb_esp_rtdb_data_type_boolean, fb_esp_rtdb_data_type_string, fb_esp_rtdb_data_type_json,
    // fb_esp_rtdb_data_type_array, fb_esp_rtdb_data_type_blob, and fb_esp_rtdb_data_type_file (10)

    // count++;
  }

  // Serial.print(bVal1);
  digitalWrite(D0, bVal1);
  digitalWrite(D1, bVal2);
  digitalWrite(D2, bVal3);
}
/* Sending Sensor Data to Firebase Database by CircuitDigest(www.circuitdigest.com) */

// #include <ESP8266WiFi.h>                                                             // esp8266 library
// #include <FirebaseArduino.h>                                                         // firebase library
// #include <DHT.h>                                                                     // dht11 temperature and humidity sensor library
// #include <SD.h>
// #include <SPI.h>
// // #include <
// #define FIREBASE_HOST "smart-tera-default-rtdb.asia-southeast1.firebasedatabase.app" // the project name address from firebase id
// #define FIREBASE_AUTH "AIzaSyCbbh0QQxwejqKNVYapf0aSIbsna96eyYM"                      // the secret key generated from firebase
// #define WIFI_SSID "WIFI@ITERA-IOT"                                                   // input your home or public wifi name
// #define WIFI_PASSWORD "IOT-ITERA"                                                    // password of wifi ssid
// #define DHTPIN D5                                                                    // what digital pin we're connected to
// #define DHTTYPE DHT22                                                                // select dht type as DHT 11 or DHT22
// DHT dht(DHTPIN, DHTTYPE);

// void setup()
// {

//   Serial.begin(115200);
//   delay(1000);
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // try to connect with wifi
//   Serial.print("Connecting to ");
//   Serial.print(WIFI_SSID);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(500);
//   }

//   Serial.println();

//   Serial.print("Connected to ");

//   Serial.println(WIFI_SSID);

//   Serial.print("IP Address is : ");

//   Serial.println(WiFi.localIP()); // print local IP address

//   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase

//   dht.begin(); // Start reading dht sensor
// }

// void loop()
// {

//   float h = dht.readHumidity();    // Reading temperature or humidity takes about 250 milliseconds!
//   float t = dht.readTemperature(); // Read temperature as Celsius (the default)
//   if (isnan(h) || isnan(t))
//   { // Check if any reads failed and exit early (to try again).
//     Serial.println(F("Failed to read from DHT sensor!"));
//     return;
//   }

//   Serial.print("Humidity: ");
//   Serial.print(h);
//   String fireHumid = String(h) + String("%"); // convert integer humidity to string humidity

//   Serial.print("%  Temperature: ");
//   Serial.print(t);
//   Serial.println("Â°C ");
//   String fireTemp = String(t) + String("Â°C"); // convert integer temperature to string temperature
//   delay(2000);
//   Firebase.pushFloat("/data_iot_device/device_a/sensor_1", h); // setup path and send readings
//   Firebase.pushFloat("/data_iot_device/device_a/sensor_2", t); // setup path and send readings
// }