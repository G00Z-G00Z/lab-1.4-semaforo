#include <Arduino.h>

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

/***Pins de los segmentos**************************/

#define DISA 13
#define DISB 12
#define DISC 11
#define DISD 10
#define DISE 9
#define DISF 8
#define DISG 7
/**************************************************/

/**
 * @brief Array with the values of the display
 *
 */
int displayNumArray[10][7] = {{1, 1, 1, 1, 1, 1, 0},  // 0
                              {0, 1, 1, 0, 0, 0, 0},  // 1
                              {1, 1, 0, 1, 1, 0, 1},  // 2
                              {1, 1, 1, 1, 0, 0, 1},  // 3
                              {0, 1, 1, 0, 0, 1, 1},  // 4
                              {1, 0, 1, 1, 0, 1, 1},  // 5
                              {1, 0, 1, 1, 1, 1, 1},  // 6
                              {1, 1, 1, 0, 0, 0, 0},  // 7
                              {1, 1, 1, 1, 1, 1, 1},  // 8
                              {1, 1, 1, 0, 0, 1, 1}}; // 9

/**
 * @brief Array of the pins of the display
 *
 */
int displayPinArray[7] = {
    DISA,
    DISB,
    DISC,
    DISD,
    DISE,
    DISF,
    DISG,
};

/**
 * @brief Set the Number Display object
 *
 * @param n
 */
void setNumberDisplay(int n)
{

  if (n < 0 || n > 9)
  {
    setNumberDisplay(0);
    return;
  }

  for (size_t i = 0; i < 7; i++)
  {
    digitalWrite(displayPinArray[i], displayNumArray[n][i]);
  }
}

/**
 * @brief Variable that registers when a persons clicks the button.
 *
 */
volatile bool peatonWantsToCross = false;

#define INTERRUPBTNPIN 19

/**
 * @brief IRS that handles when user presses the button
 *
 */
void pressedPeatonBtn()
{
  Serial.println("Peaton: true");
  peatonWantsToCross = true;
}

/**
 * @brief Array with all the pins that have leds
 *
 */
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

/**
 * @brief Funcition that initializes the pins.
 *
 */
void initPins()
{
  // Display segments
  for (size_t i = 0; i < 7; i++)
  {
    pinMode(displayPinArray[i], OUTPUT);
  }
  // Leds
  for (size_t i = 0; i < NUMBER_OF_LEDS; i++)
  {
    pinMode(pinLeds[i], OUTPUT);
  }
}

/**
 * @brief Takes the semaforo number and the state of each of its lights
 *
 * @param semaforoNo
 * @param p1 Red
 * @param p2 Yellow
 * @param p3 Turn
 * @param p4 Green
 */
void printSemaforoState(int semaforoNo, int p1, int p2, int p3, int p4)
{
  Serial.print("S");
  Serial.print(semaforoNo);
  Serial.print(": ");
  Serial.print(p1);
  Serial.print(p2);
  Serial.print(p3);
  Serial.print(p4);
  Serial.println();
}

/*******Traffic light functions********************/

/**
 * @brief Sets the state of the traffic light
 *
 * @param p1 Red
 * @param p2 Yellow
 * @param p3 Turn
 * @param p4 Green
 */

void semaforo1(int p1, int p2, int p3, int p4)
{
  digitalWrite(S1P1, p1);
  digitalWrite(S1P2, p2);
  digitalWrite(S1P3, p3);
  digitalWrite(S1P4, p4);
  printSemaforoState(1, p1, p2, p3, p4);
}

void semaforo2(int p1, int p2, int p3, int p4)
{
  digitalWrite(S2P1, p1);
  digitalWrite(S2P2, p2);
  digitalWrite(S2P3, p3);
  digitalWrite(S2P4, p4);
  printSemaforoState(2, p1, p2, p3, p4);
}

void semaforo3(int p1, int p2, int p3, int p4)
{
  digitalWrite(S3P1, p1);
  digitalWrite(S3P2, p2);
  digitalWrite(S3P3, p3);
  printSemaforoState(3, p1, p2, p3, p4);
}

void semaforo4(int p1, int p2, int p3, int p4)
{
  digitalWrite(S4P1, p1);
  digitalWrite(S4P2, p2);
  digitalWrite(S4P3, p3);
  printSemaforoState(4, p1, p2, p3, p4);
}
/**************************************************/

/*****Seven segment display************************/

/**************************************************/

void setup()
{

  Serial.begin(9600);

  // IRS
  attachInterrupt(digitalPinToInterrupt(INTERRUPBTNPIN), pressedPeatonBtn, RISING);

  // Leds
  initPins();

  Serial.println("Trafic lights!");
}

/**
 * @brief Checks if a peaton wants to cross, and if it wants to, it runs a
 * rutine.
 *
 * @param timeDelay_ms
 */
void waitForPeaton(int timeDelay_ms)
{

  if (!peatonWantsToCross)
    return;

  int secs = timeDelay_ms / 1000;

  Serial.println("Peaton cruzando");

  // loop display
  for (int i = secs; i >= 0; i--)
  {
    setNumberDisplay(i);
    Serial.print("Quedan: ");
    Serial.print(secs);
    Serial.println(" segundos");
    delay(1000);
  }

  peatonWantsToCross = false;
}

/**
 * @brief Prints the state of the traffic lights
 *
 * @param stateNo
 */
void printState(int stateNo)
{
  Serial.print("Estado: ");
  Serial.println(stateNo);
  Serial.print("Peaton: ");
  Serial.println(peatonWantsToCross);
}

void loop()
{

  //
  waitForPeaton(8000);

  // Estado 1
  printState(1);
  semaforo1(1, 0, 1, 0);
  semaforo2(1, 0, 1, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(8000);

  waitForPeaton(8000);
  // Estado 2
  printState(2);
  semaforo1(0, 0, 0, 1);
  semaforo2(0, 0, 0, 1);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(19000);

  waitForPeaton(8000);

  // Estado 3
  printState(3);
  semaforo1(0, 1, 0, 0);
  semaforo2(0, 1, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(3000);

  // Estado 4
  printState(4);
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(0, 0, 0, 1);
  semaforo4(1, 0, 0, 0);
  delay(12000);

  // Estado 5
  printState(5);
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(0, 1, 0, 0);
  semaforo4(1, 0, 0, 0);
  delay(3000);

  // Estado 6
  printState(6);
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(0, 0, 0, 1);
  delay(12000);

  // Estado 7
  printState(7);
  semaforo1(1, 0, 0, 0);
  semaforo2(1, 0, 0, 0);
  semaforo3(1, 0, 0, 0);
  semaforo4(0, 1, 0, 0);
  delay(3000);
}