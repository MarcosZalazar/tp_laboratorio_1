
#ifndef JUEGO_H_
#define JUEGO_H_

#define JUEGO_LEN 63
#include "LinkedList.h"

typedef struct {
	char nombreJuego[JUEGO_LEN];
}Juego;

Juego* juego_new(void);
Juego* juego_newParametros(char* nombreJuegoStr);
int juego_setNombreJuego(Juego* this,char* nombreJuego);
int juego_getNombreJuego(Juego* this,char* nombreJuego);
void juego_delete(Juego* this);
int juego_estaElJuegoEnLaLista(LinkedList* pListaJuegosNoRepetidos,char* juegoAEvaluar);
int juego_listarJuego(Juego* this);

#endif /* JUEGO_H_ */
