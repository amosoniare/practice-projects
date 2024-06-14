#include <WiFi.h>
#include <ESP32Servo.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
#include "thingProperties.h"

// GPIO pins
#define servoPin 18
#define relay1Pin 5
#define relay2Pin 4
#define ledInBuilt 2

Servo myservo;
int servoPosition = 90; // default position
bool sweeping = false;
bool cloudConnected = false;

hd44780_I2Cexp lcd; // declare lcd object: auto locate & config expander chip

// LCD geometry
const int LCD_COLS = 16;
const int LCD_ROWS = 4;

// Replace with your network credentials
const char* ssid     = "910";
const char* password = "Bl3ss3d@20";

void setup() {
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(ledInBuilt, OUTPUT);
  
  Serial.begin(115200);
  myservo.attach(servoPin);  // attaches the servo on the servoPin to the servo object

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // Cloud Part
  lcd.setCursor(0, 2);
  lcd.print("Connecting to Cloud");
  // Initialize properties
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  cloudConnected = true;
  
  lcd.setCursor(0, 2);
  lcd.print("Cloud Connected");
  delay(1000);
  lcd.clear();
}

void loop() {
  ArduinoCloud.update();

  // Update LCD with current status
  lcd.setCursor(0, 0);
  lcd.print("Sol: ");
  lcd.print(digitalRead(relay1Pin) ? "ON " : "OFF");
  lcd.print(" Motor: ");
  lcd.print(digitalRead(relay2Pin) ? "ON " : "OFF");
  lcd.setCursor(0, 1);
  lcd.print("LED: ");
  lcd.print(digitalRead(ledInBuilt) ? "ON " : "OFF ");
  lcd.print(" Cloud: ");
  lcd.print(cloudConnected ? "ON " : "OFF");

  if (sweeping) {
    servoPosition += 1; // Incrementing by 1 for sweeping effect
    if (servoPosition >= 180 || servoPosition <= 0) {
      servoPosition = 90; // Reset to default position
    }
    myservo.write(servoPosition);
    delay(15); // Adjust speed of sweeping
  }
}

void onRelay1Change() {
  if (relay1) {
    digitalWrite(relay1Pin, LOW);
    Serial.println("Solenoid OFF");
  } else {
    digitalWrite(relay1Pin, HIGH);
    Serial.println("Solenoid ON");
  }
}

void onLEDInBuiltChange() {
  if (lED_In_Built) {
    digitalWrite(ledInBuilt, HIGH);
    Serial.println("LED_In_Built ON");
  } else {
    digitalWrite(ledInBuilt, LOW);
    Serial.println("LED_In_Built OFF");
  }
}

void onMotorChange() {
  if (motor) {
    digitalWrite(relay2Pin, HIGH);
    Serial.println("Motor ON");
  } else {
    digitalWrite(relay2Pin, LOW);
    Serial.println("Motor OFF");
  }
}

void onServoChange() {
  myservo.write(servo);
}
