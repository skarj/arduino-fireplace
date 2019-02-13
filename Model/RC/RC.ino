#include <IRremote.h>

IRsend irsend;
const int button1 = 4;  // Heater
const int button2 = 5;  // Power
const int button3 = 6;  // Volume +
const int button4 = 7;  // Volume -
const int button5 = 10; // Temp +
const int button6 = 11; // Temp -
const int button7 = 12; // Crackle
const int button8 = 13; // Effect

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);
  pinMode(button7, INPUT);
  pinMode(button8, INPUT);
}

void loop() {
  if (digitalRead(button1) == HIGH){
    delay(50);
    irsend.sendNEC(0x807F48B7, 32); // Heater
  }

  if (digitalRead(button2) == HIGH){
    delay(50);
    irsend.sendNEC(0x807F28D7, 32); // Power
  }

  if (digitalRead(button3) == HIGH){
    delay(50);
    irsend.sendNEC(0x807F58A7, 32); // Volume +
  }

  if (digitalRead(button4) == HIGH){
    delay(50);
    irsend.sendNEC(0x807FA05F, 32); // Volume -
  }

  if (digitalRead(button5) == HIGH){
    delay(50);
    irsend.sendNEC(0x807FB847, 32); // Temp +
  }

  if (digitalRead(button6) == HIGH){
    delay(50);
    irsend.sendNEC(0x807F9867, 32); // Temp -
  }

  if (digitalRead(button7) == HIGH){
    delay(50);
    irsend.sendNEC(0x807F7887, 32); // Crackle
  }

  if (digitalRead(button8) == HIGH){
    delay(50);
    irsend.sendNEC(0x807FF807, 32); // Effect
  }
}
