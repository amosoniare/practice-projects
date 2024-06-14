# ESP32 Servo Control with Web Server, I2C LCD, and Button

This project uses an ESP32 to control a servo motor via a web interface. It also displays the IP address on an I2C LCD and the servo angle when a button is pressed.

## Components Used
- ESP32
- Servo Motor
- I2C LCD Display
- Push Button
- Jumper Wires
- Breadboard

## <img src="images/photo1.jpeg" alt="WIFI servo motor with LCD and push button" width="400"/>

## Libraries Required
- `WiFi.h`
- `ESP32Servo.h`
- `Wire.h`
- `LiquidCrystal_I2C.h`

## Wi-Fi Credentials
Replace the placeholder SSID and password with your network credentials:
- `ssid`: Your Wi-Fi network name.
- `password`: Your Wi-Fi network password.

## Setup
### Servo
The servo is attached to GPIO pin 2 of the ESP32. The servo object is created and attached to the specified pin.

### Web Server
A web server is set up on port 80. The server listens for incoming client connections and serves an HTML page that allows users to control the servo position with a slider.

### I2C LCD
The LCD is initialized with the I2C address `0x27` and set to display 16 columns and 2 rows. It displays the IP address of the ESP32 upon connection to the Wi-Fi network.

### Button
A button is connected to GPIO pin 23. When pressed, it displays the current servo angle on the LCD.

## Functions
### Setup Function
- Initializes serial communication at 115200 baud.
- Attaches the servo to the specified GPIO pin.
- Connects to the Wi-Fi network using the provided SSID and password.
- Prints the IP address to the serial monitor and displays it on the LCD.
- Initializes the button pin as input.

### Loop Function
- Reads the button state and, if pressed, displays the servo angle on the LCD.
- Manages incoming client connections and serves the web page.
- Parses HTTP GET requests to read the servo position value from the slider.
- Updates the servo position based on the slider value.

### HTML Web Interface
The web interface includes:
- A slider to control the servo position (0 to 180 degrees).
- JavaScript to update the slider position and send the new position to the ESP32 via an AJAX request.

## How It Works
1. **Connecting to Wi-Fi**: The ESP32 connects to the specified Wi-Fi network and starts the web server.
2. **Displaying IP Address**: The IP address is displayed on the LCD once the ESP32 connects to the Wi-Fi.
3. **Handling Client Requests**: The ESP32 listens for incoming HTTP client requests.
4. **Web Page Interaction**: The web page served by the ESP32 contains a slider that allows the user to set the servo position. Moving the slider sends an AJAX request to the ESP32 with the new position value.
5. **Updating Servo Position**: The ESP32 reads the position value from the HTTP GET request and moves the servo accordingly.
6. **Button Press**: When the button is pressed, the current servo angle is displayed on the LCD.

## Example Code Snippets
### Setting Up the Servo
```cpp
Servo myservo;
static const int servoPin = 2;
myservo.attach(servoPin);

## Circuit Image
![servo motor](wifi_servomotor_withLcd_pushButton_copy_20240530181829/images/CircuitImage.jpg)

<img src="wifi_servomotor_withLcd_pushButton_copy_20240530181829/images/CircuitImage.jpg" alt="Circuit Image" width="500"/>
