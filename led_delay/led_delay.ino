#include <stdlib.h>
#include <SevSeg.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

SevSeg sevseg;

int LED_PIN = 13;
int POT_PIN = 0;
int MIN_DELAY = 1;
int MAX_DELAY = 5000;
int ONE_SECOND = 1000;

int delayMillis = 1;
int lastInput = -100;
int currentDelay = 0;

unsigned long lastChange = 0;
unsigned long lastRead = -100000;

byte ledStatus = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12};

  bool resistorsOnSegments = false;
  bool updateWithDelaysIn = false;
  bool leadingZeros = false;
  bool disableDecPoint = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelaysIn, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  Serial.begin(115200);
}

int readDelayMillis() {
  int input = analogRead(POT_PIN);
  if (millis() - lastRead < ONE_SECOND && abs(input - lastInput) < 5) {
    return delayMillis;
  }

  lastRead = millis();
  lastInput = input;

  switch (input) {
    case 0 ... 40: return MIN_DELAY;
    case 50 ... 90: return 5;
    case 100 ... 140: return 15;
    case 150 ... 190: return 30;
    case 200 ... 240: return 60;
    case 250 ... 290: return 120;
    case 300 ... 340: return 240;
    case 350 ... 390: return 480;
    case 400 ... 440: return 720;
    case 450 ... 490: return 960;
    case 500 ... 540: return 1500;
    case 550 ... 640: return 2000;
    case 650 ... 740: return 2500;
    case 750 ... 840: return 3000;
    case 850 ... 940: return 3500;
    case 950 ... 1500: return MAX_DELAY;
    default: return delayMillis;
  }
}

void loop() {
  delayMillis = readDelayMillis();
  sevseg.setNumber(delayMillis, 0);
  sevseg.refreshDisplay();  
  
  digitalWrite(LED_PIN, ledStatus);

  long currentDelay = millis() - lastChange;
  if (currentDelay >= delayMillis) {
    ledStatus = ledStatus == LOW ? HIGH : LOW;
    lastChange = millis();
  }
}
