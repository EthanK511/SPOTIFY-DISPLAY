#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

#define TFT_CS   1
#define TFT_RST  2
#define TFT_DC   3
#define TFT_SCLK 4
#define TFT_MOSI 5

// Button / switch pin
#define BUTTON_PIN 15   // connect one switch pin here, the other to GND

char* SSID = "YOUR WIFI SSID";
const char* PASSWORD = "YOUR WIFI PASSWORD";
const char* CLIENT_ID = "YOUR CLIENT ID FROM THE SPOTIFY DASHBOARD";
const char* CLIENT_SECRET = "YOUR CLIENT SECRET FROM THE SPOTIFY DASHBOARD";

String lastArtist;
String lastTrackname;

Spotify sp(CLIENT_ID, CLIENT_SECRET);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// simple debouncing
unsigned long lastButtonChange = 0;
bool lastButtonState = HIGH;
bool buttonPressed = false;

void setup() {
    Serial.begin(115200);

    // Set up the button with internal pull-up.
    // Wiring: BUTTON_PIN ↔ switch ↔ GND
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    tft.initR(INITR_BLACKTAB); // the type of screen
    tft.setRotation(1);        // landscape
    Serial.println("TFT Initialized!");
    tft.fillScreen(ST77XX_BLACK);

    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.printf("\nConnected!\n");

    tft.setCursor(0, 0);
    tft.write(WiFi.localIP().toString().c_str());

    sp.begin();
    while (!sp.is_auth()) {
        sp.handle_client();
    }
    Serial.println("Authenticated");
}

void handleButton() {
    // basic debounce
    bool rawState = digitalRead(BUTTON_PIN); // HIGH = not pressed, LOW = pressed
    unsigned long now = millis();

    if (rawState != lastButtonState) {
        // state changed, reset timer
        lastButtonChange = now;
        lastButtonState = rawState;
    }

    // if state has been stable for 30ms, treat it as real
    if ((now - lastButtonChange) > 30) {
        if (rawState == LOW && !buttonPressed) {
            // new press detected
            buttonPressed = true;
            Serial.println("Button pressed!");

            // 👉 PUT YOUR ACTION HERE
            // e.g. force refresh, change display mode, next track, etc.
            // For now, just clear and show a short message:
            tft.fillScreen(ST77XX_BLACK);
            tft.setCursor(10, 10);
            tft.write("Button pressed!");
        } else if (rawState == HIGH && buttonPressed) {
            // button released
            buttonPressed = false;
        }
    }
}

void loop() {
    // Handle button every loop iteration
    handleButton();

    // Spotify / display logic
    String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();

    if (lastArtist != currentArtist &&
        currentArtist != "Something went wrong" &&
        !currentArtist.isEmpty()) {

        tft.fillScreen(ST77XX_BLACK);
        lastArtist = currentArtist;
        Serial.println("Artist: " + lastArtist);
        tft.setCursor(10, 10);
        tft.write(lastArtist.c_str());
    }

    if (lastTrackname != currentTrackname &&
        currentTrackname != "Something went wrong" &&
        currentTrackname != "null") {

        lastTrackname = currentTrackname;
        Serial.println("Track: " + lastTrackname);
        tft.setCursor(10, 40);
        tft.write(lastTrackname.c_str());
    }

    delay(200); // slightly faster update to keep UI responsive
}
