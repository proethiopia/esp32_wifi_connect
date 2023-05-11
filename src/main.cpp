#include <WiFi.h>
#include <WiFiClient.h>
#define wifi_ssid1 "wifi_ssid"
#define wifi_password "wifi_passsword lllll"
#define login_username "admin"
#define login_password "password"
const int ledPin = 2;
WiFiServer server(80);

boolean wifiConnected = false;

void setup() {
  Serial.begin(921600);
  delay(2000);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("██████╗░██████╗░░█████╗░███████╗████████╗██╗░░██╗██╗░█████╗░██████╗░██╗░█████╗░");
  Serial.println("██╔══██╗██╔══██╗██╔══██╗██╔════╝╚══██╔══╝██║░░██║██║██╔══██╗██╔══██╗██║██╔══██╗");
  Serial.println("██████╔╝██████╔╝██║░░██║█████╗░░░░░██║░░░███████║██║██║░░██║██████╔╝██║███████║");
  Serial.println("██╔═══╝░██╔══██╗██║░░██║██╔══╝░░░░░██║░░░██╔══██║██║██║░░██║██╔═══╝░██║██╔══██║");
  Serial.println("██║░░░░░██║░░██║╚█████╔╝███████╗░░░██║░░░██║░░██║██║╚█████╔╝██║░░░░░██║██║░░██║");
  Serial.println("╚═╝░░░░░╚═╝░░╚═╝░╚════╝░╚══════╝░░░╚═╝░░░╚═╝░░╚═╝╚═╝░╚════╝░╚═╝░░░░░╚═╝╚═╝░░╚═╝");


  pinMode(ledPin, OUTPUT);

  WiFi.begin(wifi_ssid1, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  server.begin();

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");

  Serial.println(WiFi.localIP());
  wifiConnected = true;
}

void handleLogin(WiFiClient client) {
  String loginPage =
      "<html><head><title>Login</title></head><body><h1>Login</h1>";
  loginPage += "<form method='POST' action='/login'>";
  loginPage += "Username: <input type='text' name='username'><br>";
  loginPage += "Password: <input type='password' name='password'><br>";
  loginPage += "<input type='submit' value='Login'></form>";
  loginPage += "</body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(loginPage);
  client.println();
}

void handleRoot(WiFiClient client) {
  String html =
      "<html><head><title>ESP Web Server</title><meta name='viewport' "
      "content='width=device-width, initial-scale=1'>";
  html += "<link rel='icon' href='data:,'></head><body><h1>ESP Web "
          "Server</h1><p>GPIO state: <strong>";
  html += (digitalRead(ledPin) == HIGH) ? "ON" : "OFF";
  html += "</strong></p><p><a href='/?led=on'><button "
          "class='button'>ON</button></a></p>";
  html += "<p><a href='/?led=off'><button class='button "
          "button2'>OFF</button></a></p></body></html>";

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);
  client.println();
}

void handleLoginRequest(WiFiClient client, String request) {
  int usernameIndex = request.indexOf("username=");
  int passwordIndex = request.indexOf("&password=");
  String username = request.substring(usernameIndex + 9, passwordIndex);
  String password = request.substring(passwordIndex + 10);

  if (username == login_username && password == login_password) {
    wifiConnected = true;
    handleRoot(client);
  } else {
    handleLogin(client);
  }
}

void loop() {
  if (!wifiConnected) {
    WiFiClient client = server.available();
    if (client) {
      Serial.println("New client connected.");
      String request = client.readStringUntil('\r');
      Serial.println("Request: " + request);
      client.flush();

      if (request.indexOf("GET /login") != -1) {
        handleLogin(client);
      } else if (request.indexOf("POST /login") != -1) {
        handleLoginRequest(client, request);
      } else {
        client.println("HTTP/1.1 301 Redirect");
        client.println("Location: /login");
        client.println();
        client.println();
      }

      delay(10);
      client.stop();
      Serial.println("Client disconnected.");
    }
  } else {
    // Code for handling Wi-Fi connected state and other functionality
    // Add your desired functionality here
  }
}
