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

/*******Semaforos**********************************/
void semaforo1(int p1, int p2, int p3, int p4)
{
  digitalWrite(S1P1, p1);
  digitalWrite(S1P2, p2);
  digitalWrite(S1P3, p3);
  digitalWrite(S1P4, p4);
}

void semaforo2(int p1, int p2, int p3, int p4)
{
  digitalWrite(S2P1, p1);
  digitalWrite(S2P2, p2);
  digitalWrite(S2P3, p3);
  digitalWrite(S2P4, p4);
}

void semaforo3(int p1, int p2, int p3, int p4)
{
  digitalWrite(S3P1, p1);
  digitalWrite(S3P2, p2);
  digitalWrite(S3P3, p3);
}

void semaforo4(int p1, int p2, int p3, int p4)
{
  digitalWrite(S4P1, p1);
  digitalWrite(S4P2, p2);
  digitalWrite(S4P3, p3);
}
/**************************************************/

void setup()
{
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(INTERRUPBTNPIN), pressedPeatonBtn, RISING);
}

void waitForPeaton(int timeDelay)
{
  if (peatonWantsToCross)
  {
    // Semaforos afectados

    // Display

    delay(timeDelay);
    peatonWantsToCross = false;
  }
}

void loop()
{

  //
  waitForPeaton(900);

  // Estado 1
  semaforo1(1, 0, 1, 0);
  semaforo2(1, 0, 1, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(800);

  waitForPeaton(1900);
  // Estado 2
  semaforo1(0, 0, 0, 1);
  semaforo2(0, 0, 0, 1);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(1900);

  waitForPeaton(300);
  // Estado 3
  semaforo1(0, 1, 0, 0);
  semaforo2(0, 1, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(300);

  // Estado 4
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(0, 0, 0, 1);
  semaforo4(1, 0, 0, 0);
  delay(1200);

  // Estado 5
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(0, 1, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(300);

  // Estado 6
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(0, 0, 0, 1);
  delay(1200);

  // Estado 7
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(0, 1, 0, 0);
  delay(300);
}