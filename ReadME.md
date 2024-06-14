**ESP32 Web Server and Bluetooth LED Control**

This project empowers you to control an LED connected to an ESP32 board using two convenient methods:

1. **Web Interface:** Access a user-friendly web page served by the ESP32 through a web browser on any Wi-Fi-connected device (smartphone, tablet, computer).
2. **Bluetooth Serial Communication:** Send commands via Bluetooth from your smartphone or other Bluetooth-enabled device for effortless LED control.

**Project Goals:**

* **Hands-on Learning:** Gain practical experience with ESP32 development, Wi-Fi connectivity, Bluetooth communication, and web server creation.
* **Interactive LED Control:** Experiment with controlling an LED remotely using web and Bluetooth interfaces.

**Hardware Requirements:**

* ESP32 development board (any model with Wi-Fi and Bluetooth capabilities)
* LED (choose a suitable LED based on its forward voltage and current requirements)
* Resistor (value depends on LED specifications; typically 220 ohms or higher)
* Connecting wires

**Software Requirements:**

* Arduino IDE ([https://www.arduino.cc/](https://www.arduino.cc/))

**Connections:**

1. Connect the LED's positive leg to ESP32 pin `13` through a suitable resistor (e.g., 220 ohms for a typical LED).
2. Connect the LED's negative leg to ground (GND).

**Setup Instructions:**

1. **Install Libraries:**
   - Open the Arduino IDE. Go to **Sketch > Include Library > Manage Libraries**.
   - Search for and install the following libraries:
     - `WiFi`
     - `BluetoothSerial`

2. **Update Wi-Fi Credentials:**
   - In the code (Section: Wi-Fi Credentials), replace `your_wifi_ssid` with the name of your Wi-Fi network and `your_wifi_password` with its password. Ensure these values are accurate for successful network connection.

3. **Upload Code:**
   - Connect the ESP32 to your computer using a USB cable.
   - Select the appropriate ESP32 board and serial port from the Arduino IDE tools menu.
   - Click the upload button to transfer the code to the ESP32.

**Web Interface Usage:**

1. **Connect to Wi-Fi:** Ensure your smartphone, tablet, or computer is connected to the same Wi-Fi network as the ESP32.
2. **Open Web Browser:** Launch a web browser on your device.
3. **Enter IP Address:** In the address bar, type the IP address assigned to the ESP32. You can find this by opening the serial monitor in the Arduino IDE after uploading the code (look for lines starting with "IP address:"). If you can't locate the IP this way, consider using a Wi-Fi network scanner app on your device to identify the ESP32's device name or IP.
4. **Control LED:** The web page will display user-friendly buttons or links. Click the corresponding button or link to turn the LED on or off.

**Bluetooth Serial Communication Usage:**

1. **Pair Bluetooth Device:** Pair your smartphone or other Bluetooth-enabled device with the ESP32. The ESP32's Bluetooth name will be "ESP32_BT_Light" (you can customize this name in the code if desired).
2. **Send Commands:** Use a Bluetooth terminal app on your device to send characters to the ESP32:
   - Send `"1"` (without quotes) to turn the LED on.
   - Send `"0"` (without quotes) to turn the LED off.

**Explanation of the Code:**

* **Libraries:** `WiFi.h` enables Wi-Fi connectivity, and `BluetoothSerial.h` facilitates Bluetooth communication.
* **Constants:**
   - `your_wifi_ssid`: Replace with your Wi-Fi network name (SSID).
   - `your_wifi_password`: Replace with your Wi-Fi network password.
   - `led_pin`: Defines the pin connected to the LED (default: 13). This can be modified based on your hardware setup.
* **Setup:**
   - `Serial.begin(115200)`: Initializes serial communication for debugging output (optional).
   - `SerialBT.begin("ESP32_BT_Light")`: Starts the Bluetooth module and sets its name. You can customize this name if preferred.
   - `pinMode(led_pin, OUTPUT)`: Sets the LED pin as an output.
   - `WiFi.begin(your_wifi_ssid, your_wifi_password)`: Connects the ESP32 to the Wi-Fi network using the provided credentials.
