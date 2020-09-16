#include "motores.h"
#include <AFMotor.h>
#include <util/delay.h>

/*Establezco constantes*/
static const uint8_t MAX_VELOCITY = 255;
static const uint8_t MIN_VELOCITY = 0;
static const uint8_t REDUCTION_FACTOR = 2;

/*Establezco motores a utilizar*/
AF_DCMotor motores[2] =
{
  AF_DCMotor(1),
  AF_DCMotor(2)
};

void initMotores()
{
  motores[0].setSpeed(MAX_VELOCITY);
  motores[1].setSpeed(MAX_VELOCITY);
  motores[0].run(RELEASE);
  motores[1].run(RELEASE);
}

void avanzar(uint8_t velocity)
{
  motores[0].setSpeed(velocity);
  motores[1].setSpeed(velocity);
  motores[0].run(FORWARD);
  motores[1].run(FORWARD);
}

void retroceder(uint8_t velocity)
{
  motores[0].setSpeed(velocity);
  motores[1].setSpeed(velocity);
  motores[0].run(BACKWARD);
  motores[1].run(BACKWARD);
}

void moverIzq(uint8_t velocity)
{
  motores[0].setSpeed(velocity);
  motores[1].setSpeed(velocity);
  motores[0].run(FORWARD);
  motores[1].run(BACKWARD);
}

void moverDer(uint8_t velocity)
{
  motores[0].setSpeed(velocity);
  motores[1].setSpeed(velocity);
  motores[0].run(BACKWARD);
  motores[1].run(FORWARD);
}

//Este deja los motores que vayan bajando la velocidad
void noMover()
{
  motores[0].setSpeed(MIN_VELOCITY);
  motores[1].setSpeed(MIN_VELOCITY);
  motores[0].run(RELEASE);
  motores[1].run(RELEASE);
}

//Este traba los motores (Quizas....)
void frenar()
{
  motores[0].setSpeed(MIN_VELOCITY);
  motores[1].setSpeed(MIN_VELOCITY);
  motores[0].run(BRAKE);
  motores[1].run(BRAKE);
}
