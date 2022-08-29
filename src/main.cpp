#include <Arduino.h>

/**
 * @brief Clase que maneja un semaforo
 *
 *
 */
template <int Leds>
class Semaforo
{

private:
  /**
   * @brief Pins of the leds
   *
   */
  int *pins;

public:
  Semaforo(int *pins) : pins(pins) {}

  /**
   * @brief Sets the leds to a certain state
   *
   * @param highPins
   */
  void setState(int highPins[Leds])
  {
    for (size_t i = 0; i < Leds; i++)
    {
      digitalWrite(this->pins[i], highPins[i]);
    }
  }
};

int semaforo1pins[] = {1, 2, 3, 4};
int semaforo2pins[] = {1, 2, 3, 4};
int semaforo3pins[] = {2, 3, 4};
int semaforo4pins[] = {2, 3, 4};

Semaforo<4> S1 = Semaforo<4>(semaforo1pins);
Semaforo<4> S2 = Semaforo<4>(semaforo2pins);
Semaforo<3> S3 = Semaforo<3>(semaforo3pins);
Semaforo<3> S4 = Semaforo<3>(semaforo4pins);

void setup()
{
  // put your setup code here, to run once:
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