/*
 * ESP8266 WS2812 Wifi Light
 * 2023 francesco.anselmo@aaschool.ac.uk
 * ESP8266 + WS2812 lighting control for dynamic lighting
 *
 * Dependencies
 * ESP8266 board manager library v2.7.4
 * FastLED v3.5.0
 *
 */

// use the ESP and FastLED libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FastLED.h"

// *** Variables and definitions to be changed for each devices ***

// set ACCESS_POINT to true for the ESP2866 to act aas a WiFi access point
// set ACCESS_POINT to false for the ESP8266 to connect to an existing WiFi SSID
bool ACCESS_POINT = false;

#ifndef APSSID
#define APSSID "change-with-ssid"  // change this to the desired WiFi SSID
#define APPSK  "change-with-password"     // change to to the WiFi password
#endif

const char *ssid = APSSID;
const char *password = APPSK;

IPAddress local_IP(192, 168, 74, 121);  // configure the static IP for the device
IPAddress subnet(255, 255, 255, 0);     // configure the static IP subnet mask
IPAddress gateway(192, 168, 74, 1);     // configure the IP gateway

// change DATA_PIN to the PIN used on the ESP8266
// note that sometimes the PIN number is different than what is indicated in the circuit board
#define NODE_NAME "light1"      // change this with the name of the ESP8266 WiFi device
#define NUM_LEDS 20             // change this number of LEDs in the WS2812 LED strip
#define DATA_PIN 4              // change this to the pin connected on the ESP8266 to the WS2812 data pin
#define LED_TYPE WS2812         // change this if the LED type is different than WS2812
#define COLOR_ORDER RGB         // change this to match the LED order if the colours appear in the wrong order
#define INITIAL_BRIGHTNESS 150  // change this to modify the initial brightness
#define INITIAL_TRANSITION 1    // change this to modify the initial transition type
#define FRAMES_PER_SECOND 20    // change this to speed up (lower value) or slow down (higher value) the lighting transitions
#define DELAY 20                // change this to modify the FastLED update delay

// *** Nothing to change in the code below ***

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

enum colour_enum { BLACK, WHITE, RED, GREEN, BLUE, YELLOW, ORANGE, PINK };
enum transition_enum { CONSTANT, SINELON, BPM, GRADIENT, RANDOM };

CRGB leds[NUM_LEDS];
CRGBPalette16 palette = PartyColors_p;

ESP8266WebServer server(80);
const int signal_led = LED_BUILTIN;  // signalling LED pin, only used for showing that the microcontroller is active
uint8_t idx = 0;                     // rotating index used for the LED lighting transition

int transition = INITIAL_TRANSITION;
int brightness = INITIAL_BRIGHTNESS;
int speed = FRAMES_PER_SECOND;

void setup() {
  // code that runs at startup only

  // turn on the onboard
  pinMode(signal_led, OUTPUT);
  digitalWrite(signal_led, HIGH);

  delay(3000);  // 3 second delay for device recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(brightness);

  testLEDs(); // run the initial RGB light test to help running a visual check
  
  setColor(RED);

  // serial connection to the Arduino running the encoder
  Serial.begin(115200);

  if (ACCESS_POINT == true) {
    // configure as WiFi access point
    Serial.print("Configuring access point...");
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  } else {
    // configure as WiFi client - you must have already a WiFi network setup
    WiFi.config(local_IP, gateway, subnet);
    Serial.print(F("Setting static ip to: "));
    Serial.println(local_IP);
    WiFi.begin(ssid, password);
    Serial.println("");
    // wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // setup the API enpoints and match them with changes of lighting conditions as required
  server.on("/", []() {
    handleRoot();
  });

  // set the colour to black, effectively switching off all the LEDs
  server.on("/off", []() {
    setColor(0);
    handleRoot();
  });

  // increase brightness
  server.on("/brighten", []() {
    brighten();
    handleRoot();
  });

  // decrease brightness
  server.on("/dim", []() {
    dim();
    handleRoot();
  });

  // increase speed
  server.on("/faster", []() {
    faster();
    handleRoot();
  });

  // decrease speed
  server.on("/slower", []() {
    slower();
    handleRoot();
  });

  // set specific speed values
  server.on("/s10", []() {
    setSpeed(10);
    handleRoot();
  });
  server.on("/s20", []() {
    setSpeed(20);
    handleRoot();
  });
  server.on("/s50", []() {
    setSpeed(50);
    handleRoot();
  });
  server.on("/s100", []() {
    setSpeed(100);
    handleRoot();
  });
  server.on("/s500", []() {
    setSpeed(150);
    handleRoot();
  });
  server.on("/s1000", []() {
    setSpeed(150);
    handleRoot();
  });
  server.on("/s1500", []() {
    setSpeed(150);
    handleRoot();
  });
  server.on("/s2000", []() {
    setSpeed(150);
    handleRoot();
  });

  // set LED colour to white
  server.on("/white", []() {
    setColor(WHITE);
    handleRoot();
  });
  // set LED colour to red
  server.on("/red", []() {
    setColor(RED);
    handleRoot();
  });
  // set LED colour to green
  server.on("/green", []() {
    setColor(GREEN);
    handleRoot();
  });
  // set LED colour to blue
  server.on("/blue", []() {
    setColor(BLUE);
    handleRoot();
  });
  // set LED colour to yellow
  server.on("/yellow", []() {
    setColor(YELLOW);
    handleRoot();
  });
  // set LED colour to orange
  server.on("/orange", []() {
    setColor(ORANGE);
    handleRoot();
  });
  // set LED colour to pink
  server.on("/pink", []() {
    setColor(PINK);
    handleRoot();
  });
  // set LED colour to black, which is the same as switching the LEDs off
  server.on("/black", []() {
    setColor(BLACK);
    handleRoot();
  });

  // change transition to sinelon
  server.on("/sinelon", []() {
    transition = SINELON;
    handleRoot();
  });
  // change transition to BPM
  server.on("/bpm", []() {
    transition = BPM;
    handleRoot();
  });
  // change transition to gradient
  server.on("/gradient", []() {
    transition = GRADIENT;
    handleRoot();
  });
  // change transition to random
  server.on("/random", []() {
    transition = RANDOM;
    handleRoot();
  });
  // change transition to constant
  server.on("/constant", []() {
    transition = CONSTANT;
    handleRoot();
  });

  server.onNotFound(handleNotFound); // setup server 404 not found page
  server.begin();
  Serial.println("HTTP server started");
  digitalWrite(signal_led, LOW);
}

void loop() {
  // codes that runs continuously in a loop

  server.handleClient();
  // run transition
  if (transition == SINELON) t_sinelon();
  else if (transition == BPM) t_bpm();
  else if (transition == GRADIENT) t_gradient();
  else if (transition == RANDOM) t_random();
  else if (transition == CONSTANT) t_constant();

  // send the LEDs array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate within the microcontroller capability
  FastLED.delay(1000 / speed);
  // update the LED index
  EVERY_N_MILLISECONDS(5000 / speed) {
    idx++;
  }  
}
