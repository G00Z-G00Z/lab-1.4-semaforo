#include <Arduino.h>

/*******Pin de los led*****************************/
#define NUMBER_OF_LEDS 14
#define S1P1 3
#define S1P2 4
#define S1P3 5
#define S1P4 6
#define S2P1 7
#define S2P2 8
#define S2P3 9
#define S2P4 10
#define S3P1 11
#define S3P2 12
#define S3P3 13
#define S4P1 14
#define S4P2 15
#define S4P3 16
/**************************************************/
volatile bool peatonWantsToCross = false;

#define INTERRUPBTNPIN 2

void pressedPeatonBtn()
{
  peatonWantsToCross = true;
}

int pinLeds[NUMBER_OF_LEDS] = {
    S1P1,
    S1P2,
    S1P3,
    S1P4,
    S2P1,
    S2P2,
    S2P3,
    S2P4,
    S3P1,
    S3P2,
    S3P3,
    S4P1,
    S4P2,
    S4P3,
};

void initPins()
{
  for (size_t i = 0; i < NUMBER_OF_LEDS; i++)
  {
    pinMode(pinLeds[i], OUTPUT);
  }
}

void setup()
{
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(INTERRUPBTNPIN), pressedPeatonBtn, RISING);
}

void loop()
{

  auto semaforo1 = [](int p1, int p2, int p3, int p4)
  {
    digitalWrite(1, p1);
    digitalWrite(1, p2);
    digitalWrite(1, p3);
    digitalWrite(1, p4);
  };

  while (true)
  {
    semaforo1(1, 0, 0, 1);
  }
}