#include "Arduino.h"
#include <60ghzbreathheart.h>
#include <SoftwareSerial.h>

// Choose any two digital pins for SoftwareSerial to RX & TX
#define RX_Pin 2
#define TX_Pin 3

SoftwareSerial mySerial(RX_Pin, TX_Pin);

// we'll be using software serial
BreathHeart_60GHz radar = BreathHeart_60GHz(&mySerial);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);

  while (!Serial); // Wait for serial port to connect

  Serial.println("Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  radar.HumanExis_Func(); // Human existence information output

  if (radar.sensor_report != 0x00) {
    switch (radar.sensor_report) {
      case NOONE:
        Serial.println("Nobody here.");
        Serial.println("----------------------------");
        break;
      case SOMEONE:
        Serial.println("Someone is here.");
        Serial.println("----------------------------");
        break;
      case NONEPSE:
        Serial.println("No human activity messages.");
        Serial.println("----------------------------");
        break;
      case STATION:
        Serial.println("Someone stop");
        Serial.println("----------------------------");
        break;
      case MOVE:
        Serial.println("Someone moving");
        Serial.println("----------------------------");
        break;
      case BODYVAL:
        Serial.print("The parameters of human body signs are: ");
        Serial.println(radar.bodysign_val, DEC);
        Serial.println("----------------------------");
        break;
      case DISVAL:
        Serial.print("The sensor judges the distance to the human body to be: ");
        Serial.print(radar.distance, DEC);
        Serial.println(" m");
        Serial.println("----------------------------");
        break;
      case DIREVAL:
        Serial.print("The sensor judges the orientation data with the human body as -- x: ");
        Serial.print(radar.Dir_x);
        Serial.print(" m, y: ");
        Serial.print(radar.Dir_y);
        Serial.print(" m, z: ");
        Serial.print(radar.Dir_z);
        Serial.println(" m");
        Serial.println("----------------------------");
        break;
    }
  }

  delay(200); // Add delay to avoid program jam
}
