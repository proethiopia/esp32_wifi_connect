![Image images](https://raw.githubusercontent.com/proethiopia/esp32_wifi_connect/main/Screenshot%202023-05-11%20163540.png)



# ESP Web Server with Login

This is an ESP8266/ESP32 project that demonstrates a web server with a login functionality. Users need to log in with a username and password before accessing the other functionality, such as controlling an LED.

## Prerequisites

- ESP8266 or ESP32 board
- Arduino IDE or PlatformIO with the necessary libraries installed

## Getting Started

1. Clone this repository to your local machine or download the ZIP file.

2. Open the project in Arduino IDE or PlatformIO.

3. Update the following variables in the code to match your Wi-Fi credentials:
   - `wifi_ssid1` - SSID of your Wi-Fi network.
   - `wifi_password` - Password for your Wi-Fi network.

4. (Optional) Update the following variables in the code to set your desired login credentials:
   - `login_username` - Username for login.
   - `login_password` - Password for login.

5. Build and upload the code to your ESP8266/ESP32 board.

6. Open the Serial Monitor to see the output. It will display the IP address once connected to Wi-Fi.

7. Connect to the Wi-Fi network hosted by the ESP board.

8. Open a web browser and enter the IP address displayed in the Serial Monitor.

9. You will be redirected to the login page. Enter the login credentials set in the code.

10. Once logged in, you can control the LED by clicking the ON and OFF buttons on the web page.

## Circuit Diagram

Insert your circuit diagram here if applicable.

## License

This project is licensed under the [MIT License](LICENSE).
