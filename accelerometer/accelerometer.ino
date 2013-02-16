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
OPENPIPE MIDI-USB SHIELD ACCELEROMETER EXAMPLE
This Arduino sketch is used as an usage example for the OpenPipe MIDI-USB-SHIELD[1].

For more electronics bagpipes info please visit openpipe.cc
Happy OpenPiping!!!

[1] http://openpipe.cc/products/midi-usb-shield/

******************************************************************************/

#include <SignalFilter.h>
#include <MIDI.h>

#define ZEROG  338

SignalFilter xFilter,yFilter,zFilter;
int value;
int filtered;

int note,previous_note;
int x,y,z;

void setup() {
  MIDI.begin(4); 
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  
  xFilter.begin();
  xFilter.setFilter('b');
  xFilter.setOrder(2);
  
  yFilter.begin();
  yFilter.setFilter('b');
  yFilter.setOrder(2);
  
  zFilter.begin();
  zFilter.setFilter('b');
  zFilter.setOrder(2);

}

void loop() {
  
  int tmp,tmp2;
    
     while(digitalRead(2)==LOW){
       tmp=analogRead(A4);
       x= xFilter.run(tmp);
       note=((x-ZEROG)/10+60);
       if (note!=previous_note){
         MIDI.sendNoteOff(previous_note,127,1);
         MIDI.sendPitchBend(0,1);
         MIDI.sendNoteOn(note,127,1);
         previous_note=note;
         delay(100);
       }
    }
    
    if (digitalRead(3)==LOW){
      tmp2=analogRead(A5);
      while(digitalRead(3)==LOW){
         tmp=analogRead(A5);
         z= zFilter.run(tmp);
         MIDI.sendPitchBend((tmp2-z)*20,1);
         delay(10);
      }
       MIDI.sendPitchBend(0,1);
    }
  
  if (digitalRead(4)==LOW){
  }
  
  delay(5);                     
}
