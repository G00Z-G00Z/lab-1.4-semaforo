#include <Arduino.h>
#include <SevSeg.h>

/*******Pin de los led*****************************/
#define NUMBER_OF_LEDS 14
#define S1P1 23
#define S1P2 25
#define S1P3 27
#define S1P4 29
#define S2P1 49
#define S2P2 47
#define S2P3 45
#define S2P4 43
#define S3P1 31
#define S3P2 33
#define S3P3 35
#define S4P1 37
#define S4P2 39
#define S4P3 41
/**************************************************/
volatile bool peatonWantsToCross = false;

#define INTERRUPBTNPIN 19

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

/*****Seven segment display************************/

SevSeg sevseg;

/**************************************************/

void setup()
{

  Serial.begin(9600);
  byte numDigits = 1;
  // todo: checar digit pins
  byte digitPins[] = {3};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false;   // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false;      // Default 'false' is Recommended
  bool leadingZeros = false;          // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true;        // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);

  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(INTERRUPBTNPIN), pressedPeatonBtn, RISING);

  Serial.println("Comenzando el semaforo!!");
}

void counterDisplay(SevSeg &sevseg, int delay_ms)
{
  long timer = millis();

  // Delay millis
  int deciSeconds = delay_ms / 1000;

  sevseg.setNumber(deciSeconds, 0);

  do
  {
    if (millis() - timer >= 1000)
    {
      timer += 1000;
      deciSeconds--; // Substract deciseconds
      sevseg.setNumber(deciSeconds, 0);
    }

    sevseg.refreshDisplay(); // Must run repeatedly

  } while (deciSeconds != 0);

  // Stop the sequence after
  sevseg.blank();
  sevseg.refreshDisplay();
  return;
}

void waitForPeaton(int timeDelay)
{
  if (peatonWantsToCross)
  {
    // Semaforos afectados

    // Display
    counterDisplay(sevseg, timeDelay);

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