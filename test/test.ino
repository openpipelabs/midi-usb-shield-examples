/**
 * Copyright (c) 2013 Xulio Coira <xulioc@gmail.com>. All rights reserved.
 *
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 /******************************************************************************
OPENPIPE MIDI-USB SHIELD TEST
This Arduino sketch is used for testing OpenPipe MIDI-USB-SHIELD[1].

For more electronics bagpipes info please visit openpipe.cc
Happy OpenPiping!!!

[1] http://openpipe.cc/products/midi-usb-shield/

******************************************************************************/
 

#include <MIDI.h>

#define POT_A0 A0
#define POT_A1 A1
#define PUSH_D2 2
#define PUSH_D3 3
#define PUSH_D4 4
#define LED_D6 6
#define LED_D7 7


void setup() {
  
  pinMode(PUSH_D2, INPUT);
  digitalWrite(PUSH_D2, HIGH); 
  pinMode(PUSH_D3, INPUT);
  digitalWrite(PUSH_D3, HIGH); 
  pinMode(PUSH_D4, INPUT);
  
  digitalWrite(PUSH_D4, HIGH); 
  
  pinMode(LED_D6, OUTPUT);
  pinMode(LED_D7, OUTPUT);
  
  
  MIDI.begin(4);
  
  MIDI.sendControlChange(120,127,1);
  MIDI.sendControlChange(123,127,1);
}

void loop() {
  
  uint8_t note;
  int16_t pitch;
  
  if (digitalRead(PUSH_D2)==LOW){
    note=map(analogRead(POT_A1), 0, 1023, 1, 127);
    digitalWrite(LED_D6, HIGH); 
    MIDI.sendNoteOn(note,127,1);
    while (digitalRead(PUSH_D2)==LOW);
    //MIDI.sendNoteOff(note,127,1);
    digitalWrite(LED_D6, LOW); 
  }
  
  if (digitalRead(PUSH_D3)==LOW){
    
    digitalWrite(LED_D7, HIGH); 
   
    while (digitalRead(PUSH_D3)==LOW){
      pitch=map(analogRead(POT_A0), 0, 1023, -8000, 8000);
      MIDI.sendPitchBend(pitch, 1);
      delay(50);
    }
    MIDI.sendNoteOff(note,127,1);
    digitalWrite(LED_D7, LOW); 
  }
  
  if (digitalRead(PUSH_D4)==LOW){
    
    digitalWrite(LED_D7, HIGH);
    digitalWrite(LED_D6, HIGH); 
    
    for (int i=0; i<128; i++){
    
    MIDI.sendControlChange(120,127,i);
    MIDI.sendControlChange(123,127,i);
    }
    
   
    while (digitalRead(PUSH_D4)==LOW);

    digitalWrite(LED_D7, LOW);
    digitalWrite(LED_D6, LOW); 
  }
}
