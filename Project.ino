#include <SPI.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <GU800_GFX.h>
#include "DFRobotDFPlayerMini.h"

#define DISPLAY_CS 10
#define DISPLAY_DC 9
#define DISPLAY_RESET 7
#define IR_PIN 6
#define DFPLAYER_RX 4
#define DFPLAYER_TX 5

GU800 display(DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);
unsigned long display_time;

IRrecv irrecv(IR_PIN);
decode_results results;
unsigned long ir_key_value = 0;

SoftwareSerial SoftwareSerial1(DFPLAYER_RX, DFPLAYER_TX);
DFRobotDFPlayerMini DFPlayer;

bool flag_power = 0;
bool flag_play = 0;
bool flag_heater = 0;
bool flag_effect = 0;

void setup() {
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
  display.begin();
  display.dim(15);                   // Set display brightness (0=minimum, 15=maximum)
  display.clearDisplay(1);           // Clear framebuffer and blank the display

  SoftwareSerial1.begin(9600);
  DFPlayer.begin(SoftwareSerial1);
  DFPlayer.volume(10);               //Set volume value. From 0 to 30
}

void loop() {

  if (irrecv.decode(&results)){
 
    if (results.value == 0XFFFFFFFF)
      results.value = ir_key_value;

    switch(results.value){
      case 0x807F48B7:
        if (flag_heater == 0){
          displaytext(F("Heater On"));
          flag_heater = 1;
        }
        else {
          displaytext(F("Heater Off"));
          flag_heater = 0;
        }
      break;
      case 0x807F28D7:
        if (flag_power == 0){
          displaytext(F("Power On"));
          flag_power = 1;
        }
        else {
          displaytext(F("Power Off"));
          flag_power = 0;
        }
      break;
      case 0x807F58A7:
        displaytext(F("Vol +"));
        DFPlayer.volumeUp();
      break;
      case 0x807FA05F:
        displaytext(F("Vol -"));
        DFPlayer.volumeDown();
      break;
      case 0x807FB847:
        displaytext(F("Temp +"));
      break;  
      case 0x807F9867:
        displaytext(F("Temp -"));
      break;
      case 0x807F7887:
        if (flag_play == 0){
          displaytext(F("Crackle On"));
          DFPlayer.enableLoopAll();
          flag_play = 1;
        }
        else {
          displaytext(F("Crackle Off"));
          DFPlayer.disableLoopAll();
          flag_play = 0;
        }
      break;
      case 0x807FF807:
        if (flag_effect == 0){
          displaytext(F("Effect On"));
          flag_effect = 1;
        }
        else {
          displaytext(F("Effect Off"));
          flag_effect = 0;
        }
      break;  
    }
    ir_key_value = results.value;
    irrecv.resume(); 
  }

  if (millis() - display_time > 10000){   // 10 seconds
    display_time = millis();
    display.displayOff(1);             // Turn the display off with fade effect (image is preserved)
  }
}

void displaytext(const __FlashStringHelper* text) {
  display.clearDisplay();             // Clear the buffer
  display.setTextSize(3);             // Draw 3X-scale text
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(text);
  display.display();                  // Show the display buffer on the screen.
  display_time = 0;
}

