#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Arcade.h"
#include "utn.h"
#include "LinkedList.h"
#include "Validaciones.h"


/// \brief Revisa el archivo de información y recupera el primer ID disponible para dar de alta
/// \param IdDisponible:Arrays de char en donde se guardará el primer ID disponible
///
void IdGenerator(char *IdDisponible)
{
	FILE* pArchivoId;

	if(IdDisponible != NULL)
	{
		pArchivoId = fopen("RegistroIdDisponible.txt","r");

		if(pArchivoId != NULL)
		{
			do
			{
				fscanf(pArchivoId,"%s\n",IdDisponible);

			}while(feof(pArchivoId)==0);

			fclose(pArchivoId);
		}
	}
}

/// \brief Actualiza el archivo en el que se registra el nuevo ID disponible para asignar a un arcade
/// \param lastID: Ultimo ID utilizado al cargar un arcade.
/// \return int 0: ID actualizado correctamente.
///		       -1: Error.
///
int IdUpdate(int lastID)
{
	int retorno=-1;
	FILE* pArchivoId;

	pArchivoId = fopen("RegistroIdDisponible.txt","w");

	if(pArchivoId != NULL)
	{
		fprintf(pArchivoId,"%d",lastID+1);
		fclose(pArchivoId);
		retorno=0;
	}

	return retorno;
}

/// \brief Crea el espacio de memoria para almacenar la estructura arcade
/// \return pArcade: Puntero al espacio de memoria en donde se creo la estructura arcade
///
Arcade* arcade_new(void)
{
	Arcade* pArcade= (Arcade*) malloc(sizeof(Arcade));

	return pArcade;
}

/// \brief Crea el espacio de memoria para almacenar la estructura arcade y carga sus campos
/// \param idArcadeStr: ID del arcade
/// \param nacionalidadStr: Nacionalidad del arcade
/// \param tipoDeSonidoStr:Tipo de sonido del arcade
/// \param cantidadDeJugadoresStr:Cantidad de jugadores del arcade
/// \param capacidadMaximaFichasStr:Capacidad maxima de fichas que soporta el arcade
/// \param nombreSalonStr:Nombre del salon en donde esta ubicado el arcade
/// \param nombreJuegoStr:Nombre del juego cargado en el arcade
/// \return pEmployee: Puntero al espacio de memoria en donde se creo la estructura arcade con los datos cargados

Arcade* arcade_newParametros(char* idArcadeStr, char* nacionalidadStr,char* tipoDeSonidoStr, char* cantidadDeJugadoresStr,char* capacidadMaximaFichasStr, char* nombreSalonStr,char* nombreJuegoStr)
{
	Arcade* pArcade;
	int banderaSettersOk=0;

	if(idArcadeStr != NULL && nacionalidadStr != NULL && tipoDeSonidoStr != NULL && cantidadDeJugadoresStr != NULL && capacidadMaximaFichasStr != NULL && nombreSalonStr != NULL && nombreJuegoStr != NULL)
	{
		pArcade = arcade_new();
		if(pArcade!=NULL)
		{
			if(arcade_setIdArcade(pArcade,atoi(idArcadeStr))==0 &&
			   arcade_setNacionalidad(pArcade,nacionalidadStr)==0 &&
			   arcade_setTipoDeSonidoTXT(pArcade,tipoDeSonidoStr)==0 &&
			   arcade_setCantidadDeJugadores(pArcade,atoi(cantidadDeJugadoresStr))==0 &&
			   arcade_setCapacidadMaximaFichas(pArcade,atoi(capacidadMaximaFichasStr))==0 &&
			   arcade_setNombreSalon(pArcade,nombreSalonStr)==0 &&
			   arcade_setNombreJuego(pArcade,nombreJuegoStr)==0)
			{
				IdUpdate(atoi(idArcadeStr));
				banderaSettersOk=1;
			}
			if(banderaSettersOk==0)
			{
				arcade_delete(pArcade);
				pArcade = NULL;
			}
		}
	}
	return pArcade;
}

/// \brief Borra la estructura arcade de la memoria
/// \param this:Puntero al espacio de memoria en donde se creo la estructura arcade
///
void arcade_delete(Arcade* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

/// \brief: Carga el ID en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param idArcade: ID del arcade
/// \return 0: ID cargado a la estructura correctamente.
///		   -1: Error.
int arcade_setIdArcade(Arcade* this,int idArcade)
{
	int retorno = -1;

	if(this != NULL && idArcade >= 0)
	{
		retorno = 0;
		this->idArcade = idArcade;

	}
	return retorno;
}

/// \brief Devuelve el ID del arcade cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param idArcade: ID del arcade
/// \return 0: ID devuelto correctamente.
///		   -1: Error.
int arcade_getIdArcade(Arcade* this,int* idArcade)
{
	int retorno = -1;

	if(this != NULL && idArcade != NULL)
	{
		retorno = 0;
		*idArcade = this->idArcade;
	}
	return retorno;
}

/// \brief Carga la nacionalidad en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nacionalidad: Nacionalidad del arcade
/// \return 0: Nacionalidad cargada a la estructura correctamente.
///		   -1: Error.
int arcade_setNacionalidad(Arcade* this,char* nacionalidad)
{
	int retorno = -1;

	if(this != NULL && nacionalidad != NULL)
	{
		if(esNombre(nacionalidad,NACIONALIDAD_LEN))
		{
			strncpy(this->nacionalidad,nacionalidad,NACIONALIDAD_LEN);
			retorno = 0;
		}
	}
	return retorno;
}


/// \brief: Devuelve la nacionalidad del arcade cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nacionalidad: Nacionalidad del arcade
/// \return 0: Nacionalidad devuelta correctamente.
///		   -1: Error.
int arcade_getNacionalidad(Arcade* this,char* nacionalidad)
{
	int retorno = -1;

	if(this != NULL && nacionalidad != NULL)
	{
		strncpy(nacionalidad,this->nacionalidad,NACIONALIDAD_LEN);
		retorno = 0;
	}
	return retorno;
}

/// \brief: Carga el tipo de sonido en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param tipoDeSonido: Tipo de sonido del arcade
/// \return 0: Tipo de sonido cargado a la estructura correctamente.
///		   -1: Error.
int arcade_setTipoDeSonido(Arcade* this,int tipoDeSonido)
{
	int retorno = -1;

	if(this != NULL && (tipoDeSonido ==1 || tipoDeSonido ==2 ))
	{
		retorno = 0;
		this->tipoDeSonido = tipoDeSonido;
	}
	return retorno;
}

/// \brief: Carga el tipo de sonido en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param tipoDeSonidoTXT: Tipo de sonido del arcade
/// \return 0: Tipo de sonido cargado a la estructura correctamente.
///		   -1: Error.
int arcade_setTipoDeSonidoTXT(Arcade* this,char* tipoDeSonidoTXT)
{
	int retorno = -1;
	int tipoSonidoInt;

	if(this != NULL && tipoDeSonidoTXT!= NULL)
	{
		if(strncmp("MONO",tipoDeSonidoTXT,10)==0)
		{
			tipoSonidoInt=1;
			this->tipoDeSonido = tipoSonidoInt;
			retorno = 0;
		}
		else
		{
			if(strncmp("STEREO",tipoDeSonidoTXT,10)==0)
			{
				tipoSonidoInt=2;
				this->tipoDeSonido = tipoSonidoInt;
				retorno = 0;
			}
		}
	}
	return retorno;
}

/// \brief Devuelve el tipo de sonido del arcade cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param tipoDeSonido: tipo de sonido del arcade
/// \return 0: tipo de sonido devuelto correctamente.
///		   -1: Error.
int arcade_getTipoDeSonido(Arcade* this,int* tipoDeSonido)
{
	int retorno = -1;

	if(this != NULL && tipoDeSonido != NULL)
	{
		retorno = 0;
		*tipoDeSonido = this->tipoDeSonido;
	}
	return retorno;
}


/// \brief: Carga la cantidad de jugadores en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param cantidadDeJugadores: Cantidad de jugadores del arcade
/// \return 0: Cantidad de jugadores cargada a la estructura correctamente.
///		   -1: Error.
int arcade_setCantidadDeJugadores(Arcade* this,int cantidadDeJugadores)
{
	int retorno = -1;

	if(this != NULL && (cantidadDeJugadores >=1 || cantidadDeJugadores <=4 ))
	{
		retorno = 0;
		this->cantidadDeJugadores = cantidadDeJugadores;
	}
	return retorno;
}

/// \brief Devuelve la cantidad de jugadores del arcade cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param cantidadDeJugadores: Cantidad de jugadores del arcade
/// \return 0: Cantidad de jugadores devuelta correctamente.
///		   -1: Error.
int arcade_getCantidadDeJugadores(Arcade* this,int* cantidadDeJugadores)
{
	int retorno = -1;

	if(this != NULL && cantidadDeJugadores != NULL)
	{
		retorno = 0;
		*cantidadDeJugadores = this->cantidadDeJugadores;
	}
	return retorno;
}

/// \brief: Carga la capacidad maxima de fichas en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param capacidadMaximaFichas: capacidad maxima de fichas del arcade
/// \return 0: capacidad maxima de fichas cargada a la estructura correctamente.
///		   -1: Error.
int arcade_setCapacidadMaximaFichas(Arcade* this,int capacidadMaximaFichas)
{
	int retorno = -1;

	if(this != NULL && (capacidadMaximaFichas >=0 || capacidadMaximaFichas <=100 ))
	{
		retorno = 0;
		this->capacidadMaximaFichas = capacidadMaximaFichas;
	}
	return retorno;
}

/// \brief Devuelve la capacidad maxima de fichas del arcade cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param capacidadMaximaFichas: capacidad maxima de fichas del arcade
/// \return 0: capacidad maxima de fichas devuelta correctamente.
///		   -1: Error.
int arcade_getCapacidadMaximaFichas(Arcade* this,int* capacidadMaximaFichas)
{
	int retorno = -1;

	if(this != NULL && capacidadMaximaFichas != NULL)
	{
		retorno = 0;
		*capacidadMaximaFichas = this->capacidadMaximaFichas;
	}
	return retorno;
}

/// \brief Carga el nombre del salon en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nombreSalon: Nombre del salon en donde esta el arcade
/// \return 0: Nombre del salon cargado a la estructura correctamente.
///		   -1: Error.
int arcade_setNombreSalon(Arcade* this,char* nombreSalon)
{
	int retorno = -1;

	if(this != NULL && nombreSalon != NULL)
	{
		if(esDescripcion(nombreSalon,JUEGO_LEN))
		{
			strncpy(this->nombreSalon,nombreSalon,JUEGO_LEN);
			retorno = 0;
		}
	}
	return retorno;
}


/// \brief: Devuelve el nombre del salon cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nombreSalon: Nombre del salon del arcade
/// \return 0: Nombre del salon devuelto correctamente.
///		   -1: Error.
int arcade_getNombreSalon(Arcade* this,char* nombreSalon)
{
	int retorno = -1;

	if(this != NULL && nombreSalon != NULL)
	{
		strncpy(nombreSalon,this->nombreSalon,SALON_LEN);
		retorno = 0;
	}
	return retorno;
}


/// \brief Carga el nombre del juego en la estructura arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nombreJuego: Nombre del juego del arcade
/// \return 0: Nombre del juego cargado a la estructura correctamente.
///		   -1: Error.
int arcade_setNombreJuego(Arcade* this,char* nombreJuego)
{
	int retorno = -1;

	if(this != NULL && nombreJuego != NULL)
	{
		if(esDescripcion(nombreJuego,JUEGO_LEN))
		{
			strncpy(this->nombreJuego,nombreJuego,JUEGO_LEN);
			retorno = 0;
		}
	}
	return retorno;
}


/// \brief: Devuelve el nombre del juego cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \param nombreJuego: Nombre del juego del arcade
/// \return 0: Nombre del juego devuelto correctamente.
///		   -1: Error.
int arcade_getNombreJuego(Arcade* this,char* nombreJuego)
{
	int retorno = -1;

	if(this != NULL && nombreJuego != NULL)
	{
		strncpy(nombreJuego,this->nombreJuego,JUEGO_LEN);
		retorno = 0;
	}
	return retorno;
}


/// \brief Busca el ID solicitado en la estructura de arcade
/// \param listArcades:Puntero a la Linkedlist de arcade
/// \param idArcadeABuscar: Id del empleado
/// \return 0 o >0: Indice en el que se encuentra el ID solicitado
///		   -1: Error.
int arcade_findById(LinkedList* listArcades,int idArcadeABuscar)
{
	int retorno = -1;
	int i;
	int lenList;
	int auxIdArcade;
	Arcade* pArcade;

	if(listArcades != NULL && idArcadeABuscar >= 0)
	{
		lenList=ll_len(listArcades);
		for(i=0;i<lenList;i++)
		{
			pArcade=ll_get(listArcades,i);
			if(arcade_getIdArcade(pArcade,&auxIdArcade) == 0 && auxIdArcade == idArcadeABuscar)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}


/// \brief Compara dos arcades por nombre
/// \param pArcadeA: Primer arcade a comparar
/// \param pArcadeB: Segundo arcade a comparar
/// \return 1: Nombre del primer arcade mayor a la segunda
///        -1: Nombre del segundo arcade menor a la segunda

int arcade_compareByGameName(void* pArcadeA,void* pArcadeB)
{
	int retorno=0;
	Arcade* pArcadeOne;
	Arcade* pArcadeTwo;
	char auxNombreUnoAComparar[JUEGO_LEN];
	char auxNombreDosAComparar[JUEGO_LEN];

	if(pArcadeA != NULL && pArcadeB != NULL)
	{
		pArcadeOne=(Arcade*) pArcadeA;
		pArcadeTwo=(Arcade*) pArcadeB;

		if(arcade_getNombreJuego(pArcadeOne,auxNombreUnoAComparar)==0 &&
		   arcade_getNombreJuego(pArcadeTwo,auxNombreDosAComparar)==0 )
		{
			if(stricmp(auxNombreUnoAComparar,auxNombreDosAComparar)>0)
			{
				retorno=1;
			}
			else
			{
				if(stricmp(auxNombreUnoAComparar,auxNombreDosAComparar)<0)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/// \brief Analiza si un arcade es multijugador o no lo es.
/// \param pArcade: Arcade a analizar
/// \return 0: Arcade que no es multijugador
///         1: Arcade multijugador

int arcade_EsUnArcadeMultijugador(void* pArcade)
{
	int retorno=0;
	Arcade* pArcadeAEvaluar;
	int auxCantidadDeJugadores;

	if(pArcade != NULL)
	{
		pArcadeAEvaluar=(Arcade*) pArcade;
		if(arcade_getCantidadDeJugadores(pArcadeAEvaluar,&auxCantidadDeJugadores)==0)
		{
			if(auxCantidadDeJugadores>1)
			{
				retorno=1;
			}
		}
	}
	return retorno;
}


/// \brief Actualiza la cantidad de fichas que soporta un arcade
/// \param pArcade: Arcade a actualizar
/// \return 0: Arcade actualizado correctamente
///        -1: ERROR

int arcade_ActualizadorDeFichas(void* pArcade)
{
	int retorno=-1;
	Arcade* pArcadeAActualizar;
	int auxCantidadDeFichas;

	if(pArcade != NULL)
	{
		pArcadeAActualizar=(Arcade*) pArcade;
		if(arcade_getCapacidadMaximaFichas(pArcadeAActualizar,&auxCantidadDeFichas)==0)
		{
			auxCantidadDeFichas=auxCantidadDeFichas*2;
			if(arcade_setCapacidadMaximaFichas(pArcadeAActualizar,auxCantidadDeFichas)==0)
			{
				retorno=0;
			}
		}
	}
	return retorno;
}


/// \brief Imprime todos los datos de un arcade
/// \param this: Puntero al espacio de memoria en donde se creo la estructura arcade
/// \return 0: Impresión realizada correctamente.
///		   -1: Error.

int arcade_printArcade(Arcade* this)
{
	int retorno = -1;
	int auxIdArcade;
	char auxNacionalidad[NACIONALIDAD_LEN];
	int auxTipoSonido;
	int auxCantidadJugadores;
	int auxCapacidadMaximaFichas;
	char auxNombreSalon[SALON_LEN];
	char auxNombreJuego[JUEGO_LEN];

	if(this != NULL)
	{
		if(arcade_getIdArcade(this,&auxIdArcade)==0 &&
		   arcade_getNacionalidad(this,auxNacionalidad)==0 &&
		   arcade_getTipoDeSonido(this,&auxTipoSonido)==0 &&
		   arcade_getCantidadDeJugadores(this,&auxCantidadJugadores)==0 &&
		   arcade_getCapacidadMaximaFichas(this,&auxCapacidadMaximaFichas)==0 &&
		   arcade_getNombreSalon(this,auxNombreSalon)==0 &&
		   arcade_getNombreJuego(this,auxNombreJuego)==0)
		{
			printf("%d - %s - %d - %d  - %d  - %s - %s\n", auxIdArcade,auxNacionalidad,auxTipoSonido,auxCantidadJugadores,auxCapacidadMaximaFichas,auxNombreSalon,auxNombreJuego);
			retorno = 0;
		}
	}
	return retorno;
}



