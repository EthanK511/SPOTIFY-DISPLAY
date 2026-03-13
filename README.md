# SPOTIFY-DISPLAY

For Hack Club Stasis By: Ethan

This is a versatile controller for Spotify. It uses Wi‑Fi connectivity and the Spotify API to connect to and control your Spotify dashboard.

I made this because I use Spotify a lot and wanted a faster, more tactile way to control my music without always switching back to my computer or phone. I also wanted an excuse to learn more about using the Spotify API, Wi‑Fi connectivity, and hardware like the ESP32 and TFT displays. Finally, I thought it would be a fun Hack Club Stasis project that combines coding, electronics, and 3D design into something I’ll actually use every day.

### Wiring


|TFT pin |Connects to        |Example ESP32 GPIO|Code define |
|----------------------|-------------------|------------------|------------|
|VCC / 3V3             |3.3V               |3V3 pin           |–           |
|GND                   |GND                |GND pin           |–           |
|SCK / SCL             |SPI clock          |GPIO6             |`TFT_SCLK 7`|
|SDA / MOSI            |SPI MOSI           |GPIO2             |`TFT_MOSI 2`|
|CS                    |Chip select        |GPIO4             |`TFT_CS 4`  |
|DC / D/C              |Data/command select|GPIO5             |`TFT_DC 5`  |
|RST / RES             |Reset              |GPIO3             |`TFT_RST 6` |
|LED / BL (backlight)  |3.3V (or through R)|3V3 pin           |–           |

```cpp
#define TFT_CS   4
#define TFT_RST  6
#define TFT_DC   5
#define TFT_SCLK 7
#define TFT_MOSI 2
```

|Button|One leg → ESP32 GPIO|Other leg →|Code name       |
|------|--------------------|-----------|----------------|
|1     |GPIO8               |GND        |`BUTTON1_PIN 8` |
|2     |GPIO7               |GND        |`BUTTON2_PIN 9` |
|3     |GPIO10              |GND        |`BUTTON3_PIN 10`|

```cpp
const int BUTTON1_PIN = 8;
const int BUTTON2_PIN = 9;
const int BUTTON3_PIN = 10;

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
}
```
<img width="2500" height="1484" alt="Untitled drawing" src="https://github.com/user-attachments/assets/dbe3ab95-edc0-425c-a9a5-a7462c22ce3e" />

### Cad Files

[Onshape](https://cad.onshape.com/documents/4ff83c145b5b96ef3f76119b/w/d79d1328c93163e81bf4b3f4/e/3de12e52f07f724cde8d55d7?renderMode=0&uiState=69b222e33f3df62d8fde611d)
[Github](https://github.com/EthanK511/SPOTIFY-DISPLAY/tree/main/cad)

### BOM

| Name                          | Purpose                                  | Cost (USD) | Qty | Total (USD) | Link        | Distributor |
| ----------------------------- | ---------------------------------------- | ---------- | --- | ----------- | ----------- | ----------- |
| ESP32 C3 Mini V2.1.0 - LOLIN | Micromanage everything else              | $0.99      | 1   | $0.99       | [Aliexpress link](https://www.aliexpress.us/item/3256804553736450.html) | Aliexpress  |
| Mechanical Keyboard Switches 10PCS | To control the media (Back Next Play Pause) | $4.69      | 1   | $4.69       | [Amazon link](https://www.amazon.com/BlingKingdom-Replacement-Mechanical-Keyboard-Dustproof/dp/B0DSHTPSL3/ref=sr_1_16?crid=13XS1WUOWKTB9&dib=eyJ2IjoiMSJ9.tLOmj71gGpPUR4MxYp04PVoh02kTJfFbmgv5CYDYx-54DUOUt5Z-rei93Z7nU7x5-XkCSqQthhVOcCO-qbj586SolNQdmalEJREyMtLf3f2a1eVwf0w-zAH9p423VZwrz6PWvy7fYb9jF-qDUgAbOE3yAt0O-t1MUJWXal2GpWfKBMXJ2GTDC_H8asPSOAFotC9pYmx75LmKLhLYEnH_sB8jyL9O0MWMpaAAqWmvpL3gvw0BcyE_pzWl-6qvLQsx-jgLmS_pLBvObjQSLWHtIwnUF7qPcFp1w1aEl4EkFUw.CvSvEZyiqpkg2DQJcjo490EaWdtB4wyohpWtK1dGR2Y&dib_tag=se&keywords=Tactile+switches&qid=1773245718&s=electronics&sprefix=tactile+switches%2Celectronics%2C194&sr=1-16) | Amazon     |
| 1.8" TFT display ST7735       | To display the song info, ect.             | $8.79      | 1   | $8.79       | [Amazon link](https://www.amazon.com/Bewinner-Resolution-Interface-Full-Color-Controller/dp/B083NYBN4Q) | Amazon      |
|                               |                                          |            |     | $14.47      |             |             |

### Photos

<img width="582" height="429" alt="Screenshot 2026-03-12 at 5 18 33 PM" src="https://github.com/user-attachments/assets/24a453d5-7e3a-4de8-9841-025f1fa8370a" />

<img width="582" height="517" alt="Screenshot 2026-03-12 at 5 19 56 PM" src="https://github.com/user-attachments/assets/50f4f02b-2491-4b73-99cc-2ddd593800ae" />

