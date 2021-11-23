#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Juego.h"
#include "utn.h"
#include "LinkedList.h"
#include "Validaciones.h"

/// \brief Crea el espacio de memoria para almacenar la estructura juego
/// \return pEmployee: Puntero al espacio de memoria en donde se creo la estructura juego
///
Juego* juego_new(void)
{
	Juego* pJuego= (Juego*) malloc(sizeof(Juego));

	return pJuego;
}

/// \brief Crea el espacio de memoria para almacenar la estructura juego y carga su campo
/// \param nombreJuegoStr: Nombre del juego
/// \return pEmployee: Puntero al espacio de memoria en donde se creo la estructura juego con los datos cargados

Juego* juego_newParametros(char* nombreJuegoStr)
{
	Juego* pJuego;
	int banderaSettersOk=0;

	if(nombreJuegoStr != NULL)
	{
		pJuego = juego_new();
		if(pJuego!=NULL)
		{
			if(juego_setNombreJuego(pJuego,nombreJuegoStr)==0)
			{
				banderaSettersOk=1;
			}
			if(banderaSettersOk==0)
			{
				juego_delete(pJuego);
				pJuego = NULL;
			}
		}
	}
	return pJuego;
}

/// \brief Carga el nombre en la estructura juego
/// \param this: Puntero al espacio de memoria en donde se creo la estructura juego
/// \param nombreJuego: Nombre del juego
/// \return 0: Nombre de juego cargado a la estructura correctamente.
///		   -1: Error.
int juego_setNombreJuego(Juego* this,char* nombreJuego)
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
/// \param this: Puntero al espacio de memoria en donde se creo la estructura juego
/// \param nombreJuego: Nombre del juego
/// \return 0: Nombre del juego devuelto correctamente.
///		   -1: Error.
int juego_getNombreJuego(Juego* this,char* nombreJuego)
{
	int retorno = -1;

	if(this != NULL && nombreJuego != NULL)
	{
		strncpy(nombreJuego,this->nombreJuego,JUEGO_LEN);
		retorno = 0;
	}
	return retorno;
}

/// \brief Borra la estructura juego de la memoria
/// \param this:Puntero al espacio de memoria en donde se creo la estructura juego
///
void juego_delete(Juego* this)
{
	if(this != NULL)
	{
		free(this);
	}

}

/// \brief Analiza si un juego está en una lista
/// \param pListaJuegosNoRepetidos:Puntero a la Linkedlist de juegos no repetidos
/// \param juegoAEvaluar: Juego a analizar
/// \return 0: El juego no esta en la lista
///         1: El juego en la lista
int juego_estaElJuegoEnLaLista(LinkedList* pListaJuegosNoRepetidos,char* juegoAEvaluar)
{
	int retorno=0;
	int i;
	Juego* pJuego;
	char auxNombreJuego[JUEGO_LEN];

	if(pListaJuegosNoRepetidos != NULL && juegoAEvaluar!= NULL)
	{
		for(i=0;i<ll_len(pListaJuegosNoRepetidos);i++)
		{
			pJuego=ll_get(pListaJuegosNoRepetidos,i);
			if(pJuego!=NULL)
			{
				juego_getNombreJuego(pJuego,auxNombreJuego);
				if(strncmp(auxNombreJuego,juegoAEvaluar,JUEGO_LEN)==0)
				{
					retorno=1;
					break;
				}
				fflush(stdin);
			}
		}
	}
	return retorno;
}

/// \brief Imprime todos los datos de un juego
/// \param this: Puntero al espacio de memoria en donde se creo la estructura juego
/// \return 0: Impresión realizada correctamente.
///		   -1: Error.
int juego_listarJuego(Juego* this)
{
	int retorno = -1;
	char auxNombreJuego[JUEGO_LEN];

	if(this != NULL)
	{
		if(juego_getNombreJuego(this,auxNombreJuego)==0)
		{
			printf("%s\n",auxNombreJuego);
			retorno = 0;
		}
	}
	return retorno;
}

