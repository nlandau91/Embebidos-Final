#include "sensorDistancia.h"
static const uint8_t TRIGGER_PIN  = 14;
static const uint8_t ECHO_PIN = 15;

long duration;
uint16_t distance;

void initSensor()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

uint8_t readSensor()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2); // Son microsegundos, es despreciable
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
