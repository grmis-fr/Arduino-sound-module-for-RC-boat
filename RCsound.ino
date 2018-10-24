//==============================================================
// Sound module for RC vehicles
// GrMis @ RCGroups
// version 1.0 - September 2018
//==============================================================

#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm audio;   // create an object for use in this sketch

#define PWM_PIN 5 // Connected to the RC channel
#define SPEAKER_PIN  9 //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc


int pwm_min = 945; // These are min/max values of the RC channel, in micro-seconds
int pwm_max = 2025;
bool SD_OK;
int c_playing = 0;
//==============================================================
void setup() {
  pinMode(PWM_PIN, INPUT);

  audio.speakerPin = SPEAKER_PIN;
  audio.setVolume(2);
  audio.quality(1);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    SD_OK = false;
  } else {
    SD_OK = true;
  }
}
//==============================================================
void loop() {
  //delay(200);
  if (SD_OK) {
    int ch = pulseIn(PWM_PIN, HIGH, 25000);
    if (ch < 2200 && ch > 800) { // the pwm value is ignored if outside of this range ("glitch")
      int c = map(ch, pwm_min, pwm_max, 0, 9);
      if (!(audio.isPlaying())) {
        switch (c) {
          case 0: ; break; //no sound
          case 1: audio.play("a.wav"); break;
          case 2: audio.play("b.wav"); break;
          case 3: audio.play("c.wav"); break;
          case 4: audio.play("d.wav"); break;
          case 5: audio.play("e.wav"); break;
          case 6: audio.play("f.wav"); break;
          case 7: audio.play("g.wav"); break;
          case 8: audio.play("h.wav"); break;
          case 9: audio.play("i.wav"); break;
        }
      }
      // else {
      // if (c == 0) audio.stopPlayback();// does not work... why ?
      //}
    }
  }
}
