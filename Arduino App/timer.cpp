#include "timer.h"

void initTimer()
{
  cli(); //Disable global interrupts
  /*Seteo el timer 1*/
// El registro de control A queda todo en 0
  TCCR1A = 0;
  // Activamos el modo CTC en Timer1
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);
  // y nuestro pre-escalador en 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Inicializamos el contador en 0
  TCNT1 = 0;
  // El registro comparador de salida segun nuestra formula deberia ser 15625
  OCR1A = 15625;
  // Inicializamos el comparador para el registro A
  TIMSK1 |= (1 << OCIE1A);
  sei();//Enable global interrupts.
}
