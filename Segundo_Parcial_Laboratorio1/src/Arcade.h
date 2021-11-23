#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#define NACIONALIDAD_LEN 100
#define TIPO_MONO	1
#define TIPO_ESTEREO 2
#define SALON_LEN 63

#include "Juego.h"
#include "LinkedList.h"

typedef struct {
	int idArcade;
	char nacionalidad[NACIONALIDAD_LEN];
	int tipoDeSonido;
	int cantidadDeJugadores;
	int capacidadMaximaFichas;
	char nombreSalon[SALON_LEN];
	char nombreJuego[JUEGO_LEN];
}Arcade;


void IdGenerator(char *IdDisponible);
int IdUpdate(int lastID);
Arcade* arcade_new(void);
Arcade* arcade_newParametros(char* idArcadeStr, char* nacionalidadStr,char* tipoDeSonidoStr, char* cantidadDeJugadoresStr,char* capacidadMaximaFichasStr, char* nombreSalonStr,char* nombreJuegoStr);
void arcade_delete(Arcade* this);

int arcade_setIdArcade(Arcade* this,int idArcade);
int arcade_getIdArcade(Arcade* this,int* idArcade);
int arcade_setNacionalidad(Arcade* this,char* nacionalidad);
int arcade_getNacionalidad(Arcade* this,char* nacionalidad);
int arcade_setTipoDeSonido(Arcade* this,int tipoDeSonido);
int arcade_setTipoDeSonidoTXT(Arcade* this,char* tipoDeSonidoTXT);
int arcade_getTipoDeSonido(Arcade* this,int* tipoDeSonido);
int arcade_setCantidadDeJugadores(Arcade* this,int cantidadDeJugadores);
int arcade_getCantidadDeJugadores(Arcade* this,int* cantidadDeJugadores);
int arcade_setCapacidadMaximaFichas(Arcade* this,int capacidadMaximaFichas);
int arcade_getCapacidadMaximaFichas(Arcade* this,int* capacidadMaximaFichas);
int arcade_setNombreSalon(Arcade* this,char* nombreSalon);
int arcade_getNombreSalon(Arcade* this,char* nombreSalon);
int arcade_setNombreJuego(Arcade* this,char* nombreJuego);
int arcade_getNombreJuego(Arcade* this,char* nombreJuego);

int arcade_findById(LinkedList* listArcades,int idArcadeABuscar);

int arcade_compareByGameName(void* pArcadeA,void* pArcadeB);
int arcade_EsUnArcadeMultijugador(void* pArcade);
int arcade_ActualizadorDeFichas(void* pArcade);
int arcade_printArcade(Arcade* this);

#endif // employee_H_INCLUDED

