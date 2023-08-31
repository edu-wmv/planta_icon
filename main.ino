#include <CapacitiveSensor.h>
#include "notes.h"
#include "songs.h"

String id = " ";

void setup() {
  Serial.begin(9600);

  Serial.print("Digite o código da música: ");
  while(Serial.available() == 0) {

  }
  id = Serial.readString();
}

CapacitiveSensor  sensor_4_2 = CapacitiveSensor(4,2);

int time = 120;
int pinBuzzer = 8;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / time;

int divider = 0, noteDuration = 0;

void loop() {

  long freq = sensor_4_2.capacitiveSensor(400);

  Serial.println(id);

  if(id != " ") {
    playSong(id, freq);
  } else {

  }
}

  int playSong(String song, int freq) {
    int notes = sizeof(song) / sizeof(song[0]) / 2;

    if(freq > 400) {
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
        divider = song[thisNote + 1]; // calculates the duration of each note

        if (divider > 0) {
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        tone(pinBuzzer, song[thisNote], noteDuration*0.9);
      
        delay(noteDuration); // Wait for the specief duration before playing the next note.

        noTone(pinBuzzer); // stop the waveform generation before the next note.
      }
    }
  }
