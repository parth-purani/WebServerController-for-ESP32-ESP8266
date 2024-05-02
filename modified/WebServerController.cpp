#include "WebServerController.h"

int inputFromESP = 0;
int ledState = 0;

int WebServerController::getInputFromESP() {
  return inputFromESP;
}

int WebServerController::getLedState() {
  return ledState;
}

WebServerController::WebServerController(const char* ssid, const char* password, int ledPinNumber)
  : _ssid(ssid), _password(password), _ledPinNumber(ledPinNumber), _server(80) {}

void WebServerController::begin() {
  Serial.begin(115200);
  WiFi.begin(_ssid, _password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(_ledPinNumber, OUTPUT);

  _server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
    request->send(200, "text/html", "<h1>ESP Web Server</h1><p><a href=\"/on\">Turn LED ON</a></p><p><a href=\"/off\">Turn LED OFF</a></p>");
  });

  _server.on("/on", HTTP_GET, [this](AsyncWebServerRequest *request) {
    sendCommandToArduino("LED=1");
    request->send(200, "text/plain", "LED is ON");
  });

  _server.on("/off", HTTP_GET, [this](AsyncWebServerRequest *request) {
    sendCommandToArduino("LED=0");
    request->send(200, "text/plain", "LED is OFF");
  });

  _server.begin();
}

void WebServerController::sendCommandToArduino(const char* command) {
  Serial.println(command); // Send the command to the Arduino via Serial communication
  
    if (strcmp(command, "LED=1") == 0) {
    ledState = 1;
  } else if (strcmp(command, "LED=0") == 0) {
    ledState = 0;
  }
}

void WebServerController::loop() {
  // Your other code (if any) can go here
}


