#include "config.h"

const int buzzer_pin = 3;
const int transmit_pin = 9;
const int receive_pin = 10;
const double sound_speed = 0.034;//in cm_per_microsec
const long height_from_waist = HEIGHT;//in cm
const double allowed_angle = ((float)PI * (float)ALLOWED_ANGLE) / (float)180;//converting to radians


long threshold_distance;

long travel_time;
long distance;

void setup() {
  threshold_distance = height_from_waist * allowed_angle; //Using small angle approximation
  //Initialize pins
  pinMode(buzzer_pin, OUTPUT);
  pinMode(transmit_pin, OUTPUT);
  pinMode(receive_pin, INPUT);
  //Begin Serial
  Serial.begin(9600);
}

void loop() {
  //Reset the transmit_pin
  digitalWrite(transmit_pin, LOW);
  delayMicroseconds(5);

  //Turn on the transmit_pin for 10 microseconds and then reset
  digitalWrite(transmit_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(transmit_pin, LOW);

  //Read the travel time (in microseconds)
  travel_time = pulseIn(receive_pin, HIGH);

  //Since sound had to travel the same path twice, back and forth
  distance = travel_time * sound_speed / 2;

  if(distance >= threshold_distance){
      //produce sound of frequency 1000Hz for 300ms
      tone(buzzer_pin, 2000, 300);
    }
  else {
      // become/remain silent
      noTone(buzzer_pin);
    }

  delayMicroseconds(1000);
}
