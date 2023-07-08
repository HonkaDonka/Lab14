#include "oled-wing-adafruit.h"

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

  // Toggle between interrupts enabled and disabled
  if (digitalRead(BUT2) && !previousState)
  {
    previousState = true;
    if (turnOffInterrupt)
    {
      noInterrupts();
      turnOffInterrupt = false;
    }
    else
    {
      interrupts();
      turnOffInterrupt = true;
    }
  }
  else if (!digitalRead(BUT2))
  {
    previousState = false;
  }
}

void isr()
{
  interruptCount += 1;
}