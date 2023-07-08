/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/vinso/Documents/CTDIoT2023/Lab14/src/Lab14.ino"
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 3 "c:/Users/vinso/Documents/CTDIoT2023/Lab14/src/Lab14.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#define BUT1 D5
#define BUT2 D6

void isr();
volatile int interruptCount = 0;
bool previousState = false;
bool turnOffInterrupt = false;

OledWingAdafruit display;

void setup()
{
  Serial.begin(9600);

  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();

  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);

  attachInterrupt(BUT1, isr, FALLING);
}

void loop()
{
  display.loop();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Interrupt Count: ");
  display.println(interruptCount);
  display.display();

  if (digitalRead(BUT2) && !previousState)
  {
    previousState = true;
    if (turnOffInterrupt) {
      noInterrupts();
      turnOffInterrupt = false;
    } else {
      interrupts();
      turnOffInterrupt = true;
    }
  } else if (!digitalRead(BUT2)) {
    previousState = false;
  }
  
}

void isr()
{
  interruptCount += 1;
}