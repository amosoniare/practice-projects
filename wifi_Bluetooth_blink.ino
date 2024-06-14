#include <WiFi.h>
#include <BluetoothSerial.h>

const char* ssid     = "910";
const char* password = "Bl3ss3d@20";

BluetoothSerial SerialBT;
WiFiServer server(80);
const int ledpin = 13;

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_BT_Light");

    pinMode(ledpin, OUTPUT);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    server.begin();
}

void loop() {
    WiFiClient client = server.available();
    if (client) {
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n' && currentLine.length() == 0) {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println();
                    client.print("Click <a href=\"/H\">here</a> to turn the LED on.<br>");
                    client.print("Click <a href=\"/L\">here</a> to turn the LED off.<br>");
                    client.println();
                    break;
                } else if (c == '\n') {
                    currentLine = "";
                } else if (c != '\r') {
                    currentLine += c;
                }

                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(ledpin, HIGH);
                }
                if (currentLine.endsWith("GET /L")) {
                    digitalWrite(ledpin, LOW);
                }
                if (currentLine.endsWith("GET /favicon.ico")) {
                    client.println("HTTP/1.1 204 No Content");
                    client.println("Connection: close");
                    client.println();
                    break;
                }
            }
        }
        client.stop();
    }

    if (SerialBT.available()) {
        char btData = SerialBT.read();
        if (btData == '1') {
            digitalWrite(ledpin, HIGH);
            SerialBT.println("LED ON");
        } else if (btData == '0') {
            digitalWrite(ledpin, LOW);
            SerialBT.println("LED OFF");
        }
    }
}
