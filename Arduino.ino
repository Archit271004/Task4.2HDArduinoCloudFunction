#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "arduinoledcontrol-38ac5-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "..........................................................."
#define WIFI_SSID "MyRepublic 5667"
#define WIFI_PASSWORD "v9nkx9cpg5"

FirebaseData firebaseData;

void setup() {
    pinMode(2, OUTPUT); // Red LED
    pinMode(5, OUTPUT); // Green LED
    pinMode(4, OUTPUT); // Blue LED

    Serial.begin(9600);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Initialize Firebase with WiFi credentials
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
    Firebase.reconnectWiFi(true);
}

void loop() {
    if (Firebase.getBool(firebaseData, "/LEDcolor/Red")) {
        bool redState = firebaseData.boolData();
        digitalWrite(2, redState ? HIGH : LOW);
    }
    if (Firebase.getBool(firebaseData, "/LEDcolor/Green")) {
        bool greenState = firebaseData.boolData();
        digitalWrite(5, greenState ? HIGH : LOW);
    }
    if (Firebase.getBool(firebaseData, "/LEDcolor/Blue")) {
        bool blueState = firebaseData.boolData();
        digitalWrite(4, blueState ? HIGH : LOW);
    }

    delay(1000);
}
