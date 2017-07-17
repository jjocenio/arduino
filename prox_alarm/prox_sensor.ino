#include <pitches.h>
#include "SR04.h"

#define PIN_GREEN_1 10
#define PIN_GREEN_2 9
#define PIN_YELLOW_1 8
#define PIN_YELLOW_2 7
#define PIN_RED_1 6
#define PIN_RED_2 5

#define PIN_BEEP 4

#define PIN_ECHO 11
#define PIN_TRIG 12

#define DISTANCE_GREEN_1 75
#define DISTANCE_GREEN_2 60
#define DISTANCE_YELLOW_1 45
#define DISTANCE_YELLOW_2 30
#define DISTANCE_RED_1 20
#define DISTANCE_RED_2 10

#define DURATION 50
#define CICLE 1000

SR04 sr04 = SR04(PIN_ECHO, PIN_TRIG);

long distance;

void setup() {
  Serial.begin(9600);
 
	pinMode(PIN_GREEN_1, OUTPUT);
	pinMode(PIN_GREEN_2, OUTPUT);
	pinMode(PIN_YELLOW_1, OUTPUT);
	pinMode(PIN_YELLOW_2, OUTPUT);
	pinMode(PIN_RED_1, OUTPUT);
	pinMode(PIN_RED_2, OUTPUT);
	pinMode(PIN_BEEP, OUTPUT);

  delay(1000);
  Serial.print("Ready\n");
}

void loop() {
	distance = sr04.Distance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("\n");

	checkDistance(PIN_GREEN_1, distance, DISTANCE_GREEN_1);
	checkDistance(PIN_GREEN_2, distance, DISTANCE_GREEN_2);
	checkDistance(PIN_YELLOW_1, distance, DISTANCE_YELLOW_1);
	checkDistance(PIN_YELLOW_2, distance, DISTANCE_YELLOW_2);
	checkDistance(PIN_RED_1, distance, DISTANCE_RED_1);
	checkDistance(PIN_RED_2, distance, DISTANCE_RED_2);

	beep(distance);
}

void checkDistance(int pin, long currentDistance, long maxDistance) {
	if (currentDistance <= maxDistance) {
		digitalWrite(pin, HIGH);
	} else {
		digitalWrite(pin, LOW);
	}
}

void beep(long distance) {
	int times = 1;

  if (distance <= DISTANCE_GREEN_1) {
    if (distance <= DISTANCE_RED_2) {
      times = 9;
    } else if (distance <= DISTANCE_RED_1) {
      times = 7;          
    } else if (distance <= DISTANCE_YELLOW_2) {
      times = 5;      
    } else if (distance <= DISTANCE_YELLOW_1) {
      times = 3;      
    } else if (distance <= DISTANCE_GREEN_2) {
      times = 2;
    }    

    int interval = (CICLE - (times * DURATION)) / times;
    for (int i = 0; i < times; i++) {
      tone(PIN_BEEP, NOTE_F5, DURATION);
      delay(interval);
    }    
  } else {
    delay(CICLE);
  }
}
