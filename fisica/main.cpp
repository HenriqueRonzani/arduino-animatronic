#include <CapacitiveSensor.h>
#include <pitches.h>

const int SENDER_PIN = 1;
const int BUZZER_PIN = 12;
const int RECEIVER_PINS[] = {2, 3, 4, 5, 6, 7, 8};
const int KEYS_LENGTH = 7;

// Ajustar para aumentar ou diminuir tempo de sensibilidade
const long TOUCH_TIME_LIMIT = 500; 

CapacitiveSensor *capacitiveSensors[KEYS_LENGTH];

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  for (int i = 0; i < KEYS_LENGTH; i++) {
    capacitiveSensors[i] = new CapacitiveSensor(SENDER_PIN, RECEIVER_PINS[i]);
  }
}

// Qualquer coisa botar uma oitava a cima, caso necessario.
int keyNotes[KEYS_LENGTH] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4};

void loop() {
  bool pressedKey = false;

  for (int i = 0; i < KEYS_LENGTH; i++) {

    // Ajustar caso precise de mais "velocidade" ou mais "confiabilidade"
    long capacitiveSensorValue = capacitiveSensors[i]->capacitiveSensor(30);

    if (capacitiveSensorValue > TOUCH_TIME_LIMIT) {
      Serial.print("Tecla ");
      Serial.print(i + 1);
      Serial.print(" tocada. Valor: ");
      Serial.println(capacitiveSensorValue);

      tone(BUZZER_PIN, keyNotes[i]);
      pressedKey = true;
      
      break; 
    }
  }

  if (!pressedKey) {
    noTone(BUZZER_PIN);
  }

  delay(10); 
}