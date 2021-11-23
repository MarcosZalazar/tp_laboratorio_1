#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Arcade.h"
#include "utn.h"
#include "validaciones.h"
#include "parser.h"
#include "Juego.h"


/** \brief Carga los datos de los arcades desde el archivo arcades.csv (modo texto).
 *
 * \param path char*:Puntero al archivo desde el que se leen los datos del arcade
 * \param pListArcades LinkedList*: Puntero a la Linkedlist de arcade
 * \return int 0: Lista de arcades cargada correctamente.
 * 		      -1: Error.
 *
 */
int controller_loadFromText(char* path , LinkedList* pListArcades)
{
	int retorno = -1;
	FILE* pArchivo;
	FILE* pArchivoId;
	int primerIdMaximo;

	if(path != NULL && pListArcades != NULL)
	{
		pArchivo = fopen(path,"r");
		if(pArchivo != NULL)
		{
			parser_ArcadeFromText(pArchivo,pListArcades,&primerIdMaximo);
			fclose(pArchivo);
			retorno = 0;
		}
		primerIdMaximo=primerIdMaximo+1;
		pArchivoId = fopen("RegistroIdDisponible.txt","w");
		if(pArchivoId != NULL)
		{
			fprintf(pArchivoId,"%d",primerIdMaximo);
			fclose(pArchivoId);
		}
	}
    return retorno;
}


/** \brief Alta de arcades
 *
 * \param pListArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Arcade dado de alta correctamente
 * 		      -1: Error.
 */
int controller_addArcade(LinkedList* pListArcades)
{
	Arcade* pArcade;
	int retorno = -1;
	char idACargar[100];
	char auxNacionalidadAModificar[NACIONALIDAD_LEN];
	int auxTipoDeSonidoIntAModificar;
	char auxTipoDeSonidoAModificar[100];
	char auxCantidadDeJugadoresAModificar[100];
	char auxCapacidadMaximaFichasAModificar[100];
	char auxNombreSalonAModificar[SALON_LEN];
	char auxNombreJuegoAModificar[JUEGO_LEN];

	if(pListArcades != NULL)
	{
		if(utn_getChar(auxNacionalidadAModificar,"\nIngrese la nacionalidad","\nNacionalidad invalida\n",NACIONALIDAD_LEN,3)==0 &&
		   utn_getNumeroInt(&auxTipoDeSonidoIntAModificar,"\nIngrese el tipo de sonido (MONO:1 STEREO:2)","\nTipo de sonido invalido\n",1,2,3)==0 &&
		   utn_getNumeroEnteroPositivoComoChar(auxCantidadDeJugadoresAModificar,"\nIngrese la cantidad de jugadores","\nCantidad de jugadores invalida\n", 100,3)==0 &&
		   utn_getNumeroEnteroPositivoComoChar(auxCapacidadMaximaFichasAModificar,"\nIngrese la capacidad máxima de fichas","\nCapacidad máxima de fichas invalida\n", 100,3)==0 &&
		   utn_getDescripcion(auxNombreSalonAModificar,"\nIngrese el nombre del salon","\nNombre invalido\n", SALON_LEN,3)==0 &&
		   utn_getDescripcion(auxNombreJuegoAModificar,"\nIngrese el nombre del juego","\nNombre invalido\n",JUEGO_LEN,3)==0)
		{
			IdGenerator(idACargar);
			if(auxTipoDeSonidoIntAModificar==1)
			{
				strncpy(auxTipoDeSonidoAModificar,"MONO",100);
			}
			else
			{
				strncpy(auxTipoDeSonidoAModificar,"STEREO",100);
			}
			pArcade=arcade_newParametros(idACargar,auxNacionalidadAModificar,auxTipoDeSonidoAModificar,auxCantidadDeJugadoresAModificar,auxCapacidadMaximaFichasAModificar,auxNombreSalonAModificar,auxNombreJuegoAModificar);
			if(pArcade!=NULL)
			{
				if(ll_add(pListArcades, pArcade)==0)
				{
					controller_saveAsText("arcades.csv", pListArcades);
					retorno = 0;
				}
			}
		}

	}
    return retorno;
}

/** \brief Modificar datos de arcade
 *
 * \param pListArcades: Puntero a la Linkedlist de arcades
 * \param pListaDeJuegos:Puntero a la Linkedlist de juegos
 * \return int 0: Arcade modificado correctamente
 * 		      -1: Error.
 */
int controller_editArcade(LinkedList* pListArcades,LinkedList* pListaDeJuegos)
{
	int retorno = -1;
	int IdAModificar;
	int auxIndiceAModificar;
	int opcionCampoAModificar;
	Arcade* pArcade;
	char auxCantidadDeJugadoresAModificar[1000];
	char auxNombreJuegoAModificar[JUEGO_LEN];

	if(controller_ListArcade(pListArcades)==0)
	{
		if(utn_getNumeroInt(&IdAModificar,"\nID del arcade a modificar?\n","\nId invalido\n",0,1000000,3)==0)
		{
			auxIndiceAModificar=arcade_findById(pListArcades,IdAModificar);
			if(auxIndiceAModificar >=0)
			{
				pArcade=ll_get(pListArcades,auxIndiceAModificar);
				do{
						printf("**************************************************\n");
						printf("¿Cual campo desea modificar?\n");
						printf("10) Cantidad de jugadores\n");
						printf("11) Nombre del juego\n");
						printf("12) Salir\n");
						printf("**************************************************\n");

						utn_getNumeroInt(&opcionCampoAModificar,"\nIngrese la opción","\nOpción inválida",10,12,3);

						switch(opcionCampoAModificar)
						{
							case 10:
								if(utn_getNumeroEnteroPositivoComoChar(auxCantidadDeJugadoresAModificar,"\nIngrese la nueva cantidad de jugadores","\nCantidad de jugadores invalida\n", 2,3)==0)
								{
									arcade_setCantidadDeJugadores(pArcade,atoi(auxCantidadDeJugadoresAModificar));
									retorno = 0;
								}
								break;
							case 11:
								controller_createGameList(pListaDeJuegos, pListArcades);
								controller_ListGames(pListaDeJuegos);
								if(utn_getDescripcion(auxNombreJuegoAModificar,"\nIngrese el nuevo nombre del juego","\nNombre invalido\n",JUEGO_LEN,3)==0)
								{
									arcade_setNombreJuego(pArcade,auxNombreJuegoAModificar);
									retorno = 0;
								}
								break;
							case 12:
								break;
							}
				}while(opcionCampoAModificar!=12);

				controller_saveAsText("arcades.csv", pListArcades);
			}
			else
			{
				printf("\nId no encontrado\n");
			}
		}
	}
    return retorno;
}

/** \brief Baja de arcade
 *
 * \param pListArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Arcade dado de baja correctamente
 * 		      -1: Error.
 * 		      -2: Id no encontrado.
 */
int controller_removeArcade(LinkedList* pListArcades)
{
	int retorno = -1;
	int IdAEliminar;
	int auxIndiceAborrar;
	Arcade* pArcade;
	char respuesta;

	if(pListArcades!=NULL)
	{
		if(controller_ListArcade(pListArcades)==0)
		{
			if(utn_getNumeroInt(&IdAEliminar,"\nID del arcade a dar de baja? ","\nId invalido",0,1000000,3)==0)
			{
				auxIndiceAborrar=arcade_findById(pListArcades,IdAEliminar);
				if(auxIndiceAborrar>=0)
				{
					pArcade=ll_get(pListArcades,auxIndiceAborrar);
					printf("Este es el arcade a eliminar:");
					if(arcade_printArcade(pArcade)==0)
					{
						utn_getChar(&respuesta,"\nEsta seguro que desea eliminar el arcade?(s=SI n=NO)\n","\nOpción invalida",2,3);
						if(respuesta=='s')
						{
							arcade_delete(pArcade);
							ll_remove(pListArcades,auxIndiceAborrar);
							controller_saveAsText("arcades.csv", pListArcades);
							retorno = 0;
							printf("\nBaja realizada con éxito\n");
						}
						else
						{
							printf("\nBaja cancelada\n");
						}
					}
				}
				else
				{
					if(auxIndiceAborrar==-2)
					{
						printf("\nId no encontrado\n");
					}
					else
					{
						printf("\nError\n");
					}
				}
			}
		}
	}
    return retorno;
}

/** \brief Listar arcades
 *
 * \param pListArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Lista de arcades imprimida correctamente
 * 		      -1: Error.
 * 		      -2: No hay arcades a listar.
 */
int controller_ListArcade(LinkedList* pListArcades)
{
	int retorno = -1;
	int i;
	int lenList;
	Arcade* pArcade;

	if(pListArcades != NULL)
	{
		lenList=ll_len(pListArcades);
		if(lenList>0)
		{
			if(ll_sort(pListArcades, arcade_compareByGameName,1)==0)
			{
				printf("id,nacionalidad,tipo_sonido,cant_jug,fichas_max,salon,game\n");
				for(i=0;i<=lenList;i++)
				{
					pArcade=ll_get(pListArcades,i);
					if(pArcade!=NULL)
					{
						arcade_printArcade(pArcade);
					}
				}
				retorno = 0;
			}
		}
		else
		{
			printf("No hay arcades a listar");
			retorno = -2;
		}
	}
	return retorno;
}


/** \brief Listar juegos
 *
 * \param pListaDeJuegos:Puntero a la Linkedlist de juegos
 * \return int 0: Lista de arcades imprimida correctamente
 * 		      -1: Error.
 */
int controller_ListGames(LinkedList* pListaDeJuegos)
{
	int retorno = -1;
	int i;
	int lenList;
	Juego* pJuego;


	if(pListaDeJuegos != NULL)
	{
		lenList=ll_len(pListaDeJuegos);
		if(lenList>0)
		{
			for(i=0;i<=lenList;i++)
			{
				pJuego=ll_get(pListaDeJuegos,i);
				if(pJuego!=NULL)
				{
					juego_listarJuego(pJuego);
				}
			}
			retorno = 0;
		}
		else
		{
			printf("No hay juegos a listar");
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Crea la lista de juegos
 *
 * \param pListaDeJuegos:Puntero a la Linkedlist de juegos
 * \param pListaDeArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Lista de juegos creada correctamente
 * 		      -1: Error.
 * 		      -2: No hay juegos.
 */
int controller_createGameList(LinkedList* pListaDeJuegos, LinkedList* pListaDeArcades)
{
	int retorno = -1;
	int lenListaArcades;
	int i;
	Arcade* pArcade;
	Juego* pJuego;
	char auxJuegoAAgregar[JUEGO_LEN];

	controller_UpdateListGames(pListaDeJuegos);

	if(pListaDeJuegos != NULL && pListaDeArcades != NULL)
	{
		lenListaArcades=ll_len(pListaDeArcades);
		if(lenListaArcades>0)
		{
			if(ll_sort(pListaDeArcades, arcade_compareByGameName,1)==0)
			{
				for(i=0;i<lenListaArcades;i++)
				{
					pArcade=ll_get(pListaDeArcades,i);
					if(pArcade!=NULL)
					{
						if(arcade_getNombreJuego(pArcade,auxJuegoAAgregar)==0 && juego_estaElJuegoEnLaLista(pListaDeJuegos,auxJuegoAAgregar)==0)
						{
							pJuego=juego_newParametros(auxJuegoAAgregar);
							if(pJuego!=NULL)
							{
								ll_add(pListaDeJuegos, pJuego);
							}

						}
					}
				}
				retorno = 0;
			}
		}
		else
		{
			printf("No hay juegos a listar");
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo arcades.csv (modo texto).
 *
 * \param path: Puntero al archivo desde en el que se guardan los datos del empleado
 * \param pListArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Lista de arcades guardada correctamente (modo texto)
 * 		      -1: Error.
 */
int controller_saveAsText(char* path , LinkedList* pListArcades)
{
	int retorno = -1;
	FILE* pArchivo;
	Arcade* pAuxArcade;
	int lenArrayListArcade;
	int i;
	int auxIdArcade;
	char auxNacionalidad[NACIONALIDAD_LEN];
	int auxTipoDeSonidoInt;
	char auxTipoDeSonidoChar[100];
	int auxCantidadDeJugadores;
	int auxCapacidadMaximaFichas;
	char auxNombreSalon[SALON_LEN];
	char auxNombreJuego[JUEGO_LEN];

	if(path != NULL && pListArcades != NULL)
	{
		pArchivo = fopen(path,"w");
		if(pArchivo != NULL)
		{
			lenArrayListArcade = ll_len(pListArcades);
			if(lenArrayListArcade>0)
			{
				fprintf(pArchivo,"%s,%s,%s,%s,%s,%s,%s\n","Id del arcade","Nacionalidad","Tipo de sonido","Cantidad maxima de jugadores","Capacidad máxima de fichas","Nombre del salon","Nombre de juego");
				for(i=0; i<lenArrayListArcade; i++)
				{
					pAuxArcade = (Arcade*)ll_get(pListArcades,i);
					if(pAuxArcade!=NULL)
					{
						arcade_getIdArcade(pAuxArcade,&auxIdArcade);
						arcade_getNacionalidad(pAuxArcade,auxNacionalidad);
						arcade_getTipoDeSonido(pAuxArcade,&auxTipoDeSonidoInt);
						if(auxTipoDeSonidoInt==1)
						{
							strncpy(auxTipoDeSonidoChar,"MONO",100);
						}
						else
						{
							strncpy(auxTipoDeSonidoChar,"STEREO",100);
						}
						arcade_getCantidadDeJugadores(pAuxArcade,&auxCantidadDeJugadores);
						arcade_getCapacidadMaximaFichas(pAuxArcade,&auxCapacidadMaximaFichas);
						arcade_getNombreSalon(pAuxArcade,auxNombreSalon);
						arcade_getNombreJuego(pAuxArcade,auxNombreJuego);
						fprintf(pArchivo,"%d,%s,%s,%d,%d,%s,%s\n",auxIdArcade,auxNacionalidad,auxTipoDeSonidoChar,auxCantidadDeJugadores,auxCapacidadMaximaFichas,auxNombreSalon,auxNombreJuego);
					}
				}
			}
			fclose(pArchivo);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los juegos en el archivo juegos.txt (modo texto).
 *
 * \param path char*: Puntero al archivo desde en el que se guardan los datos de los juegos
 * \param pListaDeJuegos:Puntero a la Linkedlist de juegos
 * \return int 0: Lista de juegos guardada correctamente (modo texto)
 * 		      -1: Error.
 */

int controller_saveJuegosAsText(char* path , LinkedList* pListaDeJuegos)
{
	int retorno = -1;
	FILE* pArchivo;
	Juego* pAuxJuego;
	int lenArrayListaJuego;
	int i;
	char auxNombreJuego[JUEGO_LEN];

	if(path != NULL && pListaDeJuegos != NULL)
	{
		pArchivo = fopen(path,"w");
		if(pArchivo != NULL)
		{
			lenArrayListaJuego = ll_len(pListaDeJuegos);
			if(lenArrayListaJuego>0)
			{
				rewind(pArchivo);
				fprintf(pArchivo,"%s\n","Nombre de juego\n");
				for(i=0; i<lenArrayListaJuego; i++)
				{
					pAuxJuego = (Juego*)ll_get(pListaDeJuegos,i);
					if(pAuxJuego!=NULL)
					{
						juego_getNombreJuego(pAuxJuego,auxNombreJuego);
						fprintf(pArchivo,"%s\n",auxNombreJuego);
					}
				}
			}
			fclose(pArchivo);
			retorno = 0;
		}
	}
    return retorno;
}


/** \brief Actualiza la lista de juegos
 * \param pListaDeJuegos:Puntero a la Linkedlist de juegos
 */
void controller_UpdateListGames(LinkedList* pListaDeJuegos)
{
	int i;
	int lenList;
	Juego* pJuego;

	if(pListaDeJuegos != NULL)
	{
		lenList=ll_len(pListaDeJuegos);
		if(lenList>0)
		{
			for(i=0;i<lenList;i++)
			{
				pJuego=ll_get(pListaDeJuegos,i);
				if(pJuego!=NULL)
				{
					juego_delete(pJuego);
				}
				ll_remove(pListaDeJuegos,i);
			}
		}
	}
}




/** \brief Crea la lista de arcades multijugadores
 *
 * \param listaMultijugadores:Puntero a la Linkedlist de arcades multijugadores
 * \return int 0: Lista de arcades multijugadores imprimida correctamente
 * 		      -1: Error.
 * 		      -2: No hay arcades multijugadores
 */
int controller_createMultijugadorList(LinkedList* listaMultijugadores)
{
	int retorno = -1;
	int lenListaMultiJugadores;

	if(listaMultijugadores != NULL)
	{
		lenListaMultiJugadores=ll_len(listaMultijugadores);
		if(lenListaMultiJugadores>0)
		{
			ll_filter(listaMultijugadores,arcade_EsUnArcadeMultijugador);
			retorno = 0;
		}
		else
		{
			printf("No hay juegos a listar");
			retorno = -2;
		}
	}
	return retorno;
}


/** \brief Actualizar el numero de fichas de cada arcade de la lista
 *
 * \param pListaDeArcades:Puntero a la Linkedlist de arcades
 * \return int 0: Lista de arcades actualizada correctamente
 * 		      -1: Error.
 * 		      -2: No hay arcades a actualizar.
 */
int controller_updateNumberOfCoins(LinkedList* pListaDeArcades)
{
	int retorno = -1;
	int lenListaArcades;

	if(pListaDeArcades != NULL)
	{
		lenListaArcades=ll_len(pListaDeArcades);
		if(lenListaArcades>0)
		{
			if(ll_map(pListaDeArcades,arcade_ActualizadorDeFichas)==0)
			{
				retorno = 0;
			}
		}
		else
		{
			printf("No hay arcades a actualizar");
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Borra los datos de la linkedlist al salir.
 *
 * \param pListArcades LinkedList*:Puntero a la Linkedlist proporcionada
 * \return int 0: Lista borrada correctamente
 * 		      -1: Error.
 */
int controller_exitDelete(LinkedList* pListArcades)
{
	int retorno = -1;

	if(pListArcades != NULL)
	{
		ll_deleteLinkedList(pListArcades);
		retorno = 0;
	}
	return retorno;
}


