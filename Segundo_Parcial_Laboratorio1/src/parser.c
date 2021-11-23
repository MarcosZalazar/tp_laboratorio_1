#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Arcade.h"

/** \brief Parsea los datos de los arcades desde el archivo arcades.csv (modo texto).
 *
 * \param pFile*: Puntero al archivo a parsear
 * \param pListArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Parseo de arcades en modo texto realizado correctamente
 * 		      -1: Error.
 *
 */
int parser_ArcadeFromText(FILE* pFile , LinkedList* pListArcades, int *idMaximo)
{
	int retorno = -1;
	char auxIdArcade[1000];
	char auxNacionalidad[NACIONALIDAD_LEN];
	char auxTipoDeSonido[1000];
	char auxCantidadDeJugadores[1000];
	char auxCapacidadMaximaFichas[1000];
	char auxNombreSalon[SALON_LEN];
	char auxNombreJuego[JUEGO_LEN];
	Arcade* pArcade;
	int flagOnce=0;

	if(pFile != NULL && pListArcades != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxIdArcade,auxNacionalidad,auxTipoDeSonido,auxCantidadDeJugadores,auxCapacidadMaximaFichas,auxNombreSalon,auxNombreJuego);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxIdArcade,auxNacionalidad,auxTipoDeSonido,auxCantidadDeJugadores,auxCapacidadMaximaFichas,auxNombreSalon,auxNombreJuego)== 7)
			{
				pArcade=arcade_newParametros(auxIdArcade,auxNacionalidad,auxTipoDeSonido,auxCantidadDeJugadores,auxCapacidadMaximaFichas,auxNombreSalon,auxNombreJuego);
				if(pArcade!= NULL)
				{
					ll_add(pListArcades, pArcade);
					if(flagOnce==0)
					{
						*idMaximo=atoi(auxIdArcade);
						flagOnce=1;
					}
					else
					{
						if(atoi(auxIdArcade)>*idMaximo)
						{
							*idMaximo=atoi(auxIdArcade);
						}
					}
					retorno = 0;
				}
			}
			else
			{
				arcade_delete(pArcade);
				break;
			}
		}while(feof(pFile)==0);
	}

    return retorno;
}

