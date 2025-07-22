#include <Servo.h>
#include "pitches.h"

Servo servo9;
const int buzzerPin = 10;
const int ledPin = 8;

const int ritmo = 2000;

const int toreadorMelody[] = {
  NOTE_C5, NOTE_D5, NOTE_C5, 
  NOTE_A4, NOTE_A4, NOTE_A4, 
  NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_A4, 
  NOTE_AS4, NOTE_G4, NOTE_C5, NOTE_A4,
  NOTE_F4, NOTE_D4, NOTE_G4, NOTE_C4,

  NOTE_G4, 
  NOTE_G4, NOTE_D5, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_A4,
  NOTE_E4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_B4, NOTE_E5,

  NOTE_D5, NOTE_F5, NOTE_D5, NOTE_CS5, NOTE_D5,
  NOTE_G4, NOTE_A4, NOTE_AS4,

  NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_D5, NOTE_C5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_D6, NOTE_C6,
  NOTE_AS4, NOTE_A4, NOTE_G4,

  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, 
  
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_B5,
  NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
  NOTE_F6, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5,

  NOTE_C6, NOTE_D6, NOTE_C6, 
  NOTE_A5, NOTE_A5, NOTE_A5, 
  NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_A5, 
  NOTE_AS5, NOTE_G5, NOTE_C6, NOTE_A5,
  NOTE_F5, NOTE_D5, NOTE_G5, NOTE_C5,

  NOTE_G5, 
  NOTE_G5, NOTE_D6, NOTE_C6, NOTE_AS5,
  NOTE_A5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_A5,
  NOTE_E5, NOTE_A5, NOTE_A5, NOTE_GS5, NOTE_B5, NOTE_E6,

  NOTE_D6, NOTE_F6, NOTE_D6, NOTE_CS6, NOTE_D6,
  NOTE_G5, NOTE_A5, NOTE_AS5,

  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_D6, NOTE_C6,
  NOTE_A6, NOTE_AS6, NOTE_A6, NOTE_F6, NOTE_D7, NOTE_C7,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5
};

const int noteDurations[] = {
  4, 8, 16,
  4, 4, 8,
  16, 8, 16, 2,
  4, 8, 16, 2,
  4, 8, 16, 2,

  2,
  8, 8, 8, 8,
  8, 8, 8, 8, 2,
  4, 4, 4, 8, 8, 1,

  32, 32, 32, 32, 8,
  8, 8, 2,
  
  32, 32, 32, 32, 16, 4,
  32, 32, 32, 32, 16, 4,
  4, 4, 4, 

  16, 16, 16, 16, 16,
  16, 16, 16, 16, 16,

  32, 64, 32, 64, 32,
  64, 32, 64, 32, 64,
  32, 64, 32, 64, 32,
  64, 32, 64, 32, 64,
  32, 64, 32, 32, 32,

  4, 8, 16,
  4, 4, 8,
  16, 8, 16, 2,
  4, 8, 16, 2,
  4, 8, 16, 2,

  2,
  8, 8, 8, 8,
  8, 8, 8, 8, 2,
  4, 4, 4, 8, 8, 1,

  32, 32, 32, 32, 8,
  8, 8, 2,
  
  32, 32, 32, 32, 16, 4,
  32, 32, 32, 32, 16, 4,
  4, 4, 2, 1
};

int numNotes = sizeof(toreadorMelody) / sizeof(toreadorMelody[0]);

void setup() {
  servo9.attach(9);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, HIGH);
  
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    int noteDuration = ritmo / noteDurations[thisNote];
    
    tone(buzzerPin, toreadorMelody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);
    
    if (thisNote % 10 == 0) {
      if (servo9.read() > 90) {
        servo9.write(80);
        digitalWrite(ledPin, HIGH);
      } else {
        servo9.write(100);
        digitalWrite(ledPin, LOW);
      }
    }
    noTone(buzzerPin);
  }

  servo9.write(90);
}

void loop() {
}
