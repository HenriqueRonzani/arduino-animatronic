#include <Servo.h>
#include "pitches.h"

// --- PINAGEM ---
const int PIN_BTN_MUSICA = 2;
const int PIN_BTN_SENSOR = 3;
const int PIN_BTN_PARAR  = 4;
const int PIN_LEDS       = 5;
const int PIN_SERVO      = 9;
const int PIN_BUZZER     = 10;
const int PIN_TRIG       = 11;
const int PIN_ECHO       = 12;

// --- CONFIGURAÇÕES ---
const int RITMO = 2000; 
const int DISTANCIA_ALVO_CM = 15;

// --- VARIÁVEIS GLOBAIS ---
Servo servo9;
int estadoAtual = 0; // 0=Parado, 1=Tocando Musica, 2=Sensor

// MELODIA COMPLETA
const int toreadorMelody[] = {
  NOTE_C5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, 
  NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_G4, NOTE_C5, NOTE_A4,
  NOTE_F4, NOTE_D4, NOTE_G4, NOTE_C4, NOTE_G4, 
  NOTE_G4, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_A4,
  NOTE_E4, NOTE_A4, NOTE_A4, NOTE_GS4, NOTE_B4, NOTE_E5,
  NOTE_D5, NOTE_F5, NOTE_D5, NOTE_CS5, NOTE_D5, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_D5, NOTE_C5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_D6, NOTE_C6,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_AS4, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, 
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_B5,
  NOTE_AS5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6,
  NOTE_F6, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5,
  NOTE_C6, NOTE_D6, NOTE_C6, NOTE_A5, NOTE_A5, NOTE_A5, 
  NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C6, NOTE_A5,
  NOTE_F5, NOTE_D5, NOTE_G5, NOTE_C5, NOTE_G5, 
  NOTE_G5, NOTE_D6, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_A5,
  NOTE_E5, NOTE_A5, NOTE_A5, NOTE_GS5, NOTE_B5, NOTE_E6,
  NOTE_D6, NOTE_F6, NOTE_D6, NOTE_CS6, NOTE_D6, NOTE_G5, NOTE_A5, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_D6, NOTE_C6,
  NOTE_A6, NOTE_AS6, NOTE_A6, NOTE_F6, NOTE_D7, NOTE_C7,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5
};

const int noteDurations[] = {
  4, 8, 16, 4, 4, 8, 16, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16, 2, 2,
  8, 8, 8, 8, 8, 8, 8, 8, 2, 4, 4, 4, 8, 8, 1,
  32, 32, 32, 32, 8, 8, 8, 2, 
  32, 32, 32, 32, 16, 4, 32, 32, 32, 32, 16, 4, 4, 4, 4, 
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
  32, 64, 32, 64, 32, 64, 32, 64, 32, 64,
  32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 64, 32, 32, 32,
  4, 8, 16, 4, 4, 8, 16, 8, 16, 2, 4, 8, 16, 2, 4, 8, 16, 2, 2,
  8, 8, 8, 8, 8, 8, 8, 8, 2, 4, 4, 4, 8, 8, 1,
  32, 32, 32, 32, 8, 8, 8, 2,
  32, 32, 32, 32, 16, 4, 32, 32, 32, 32, 16, 4, 4, 4, 2, 1
};

int numNotes = sizeof(toreadorMelody) / sizeof(toreadorMelody[0]);
bool ladoServo = false; 

void setup() {
  pinMode(PIN_BTN_MUSICA, INPUT_PULLUP);
  pinMode(PIN_BTN_SENSOR, INPUT_PULLUP);
  pinMode(PIN_BTN_PARAR, INPUT_PULLUP);
  pinMode(PIN_LEDS, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  servo9.attach(PIN_SERVO);
  servo9.write(90); // PARADO IMEDIATAMENTE
}

void loop() {
  if (digitalRead(PIN_BTN_MUSICA) == LOW) estadoAtual = 1;
  if (digitalRead(PIN_BTN_SENSOR) == LOW) estadoAtual = 2;
  if (digitalRead(PIN_BTN_PARAR)  == LOW) estadoAtual = 0;

  if (estadoAtual == 0) {
    servo9.write(90); // GARANTE PARADO
    noTone(PIN_BUZZER);
    digitalWrite(PIN_LEDS, LOW);
  }
  else if (estadoAtual == 1) {
    tocarMusicaComSeguranca();
  }
  else if (estadoAtual == 2) {
    servo9.write(90); // GARANTE PARADO
    noTone(PIN_BUZZER);
    funcaoSensor();
  }
}

void tocarMusicaComSeguranca() {
  digitalWrite(PIN_LEDS, HIGH); 
  
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    
    // Check de Emergência
    if (digitalRead(PIN_BTN_PARAR) == LOW) { estadoAtual = 0; servo9.write(90); return; }
    if (digitalRead(PIN_BTN_SENSOR) == LOW) { estadoAtual = 2; servo9.write(90); return; }

    int noteDuration = RITMO / noteDurations[thisNote];
    tone(PIN_BUZZER, toreadorMelody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);
    
    // --- LÓGICA DE SEGURANÇA DO SERVO ---
    if (thisNote % 10 == 0) {
       // 1. Dá um "tranco" pequeno
       if (ladoServo) {
         servo9.write(80); // Gira devagar pra um lado
       } else {
         servo9.write(100); // Gira devagar pro outro
       }
       
       // 2. Espera um pouquinho pro servo andar (150ms)
       delay(150);

       // 3. PARA TUDO IMEDIATAMENTE ANTES DE CONTINUAR A MÚSICA
       servo9.write(90); 
       
       // Inverte o lado pra próxima vez
       ladoServo = !ladoServo;
    }
    noTone(PIN_BUZZER);
  }
  estadoAtual = 0; 
}

void funcaoSensor() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long duration = pulseIn(PIN_ECHO, HIGH, 30000); 
  int distancia = duration * 0.034 / 2;

  if (duration == 0) distancia = 999; 

  if (distancia < DISTANCIA_ALVO_CM) {
    digitalWrite(PIN_LEDS, HIGH);
  } else {
    digitalWrite(PIN_LEDS, LOW);
  }
  delay(100); 
}