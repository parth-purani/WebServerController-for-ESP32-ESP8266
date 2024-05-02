#ifndef WebServerController_h
#define WebServerController_h

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class WebServerController {
public:
  int getInputFromESP();
  int getLedState(); // New function to get the LED state
  WebServerController(const char* ssid, const char* password, int ledPinNumber);
  void begin();
  void loop();

private:
  const char* _ssid;
  const char* _password;
  int _ledPinNumber;
  AsyncWebServer _server;

  void sendCommandToArduino(const char* command);
};

#endif
