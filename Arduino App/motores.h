#include <stdint.h>
#ifndef MOTORES_H_
#define MOTORES_H_

/*Inicializa los motores DC*/
void initMotores();

/*Manda la orden a los motores de avanzar a velocidad dada*/
void avanzar(uint8_t velocity);

/*Manda la orden a los motores de retroceder a velocidad dada*/
void retroceder(uint8_t velocity);

/*Manda la orden a los motores de mover a izquierda a velocidad dada*/
void moverIzq(uint8_t velocity);

/*Manda la orden a los motores de mover a derecha a velocidad dada*/
void moverDer(uint8_t velocity);

/*Manda la orden a los motores de frenar. Con este shield funciona igual que noMover()*/
void frenar();

/*Manda la orden a los motores de no mover*/
void noMover();

#endif
