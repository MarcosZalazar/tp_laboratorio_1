/*
 ============================================================================
 Name        : Segundo_Parcial_Laboratorio1.c
 Author      : Marcos Zalazar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"

int main(void)
{
	setbuf(stdout, NULL);

	int opcion = 0;
	int banderaCargaModoTxt=0;

	LinkedList* listaArcades = ll_newLinkedList();
	LinkedList* listaJuegosNoRepetidos = ll_newLinkedList();
	LinkedList* listaMultijugadores = ll_newLinkedList();

	do{
		printf("\n1) Leer arcades desde archivo CSV\n");
		printf("2) Incorporar arcade\n");
		printf("3) Modificar arcade\n");
		printf("4) Eliminar arcade\n");
		printf("5) Imprimir arcades\n");
		printf("6) Generar archivos con juegos\n");
		printf("7) Generar un archivo con arcades Multijugador\n");
		printf("8) Actualizar cantidad de fichas\n");
		printf("9) Salir\n");

		if(utn_getNumeroInt(&opcion,"\nIngrese la opción\n","\nOpción inválida\n",1,9,3)==0)
		{
			switch(opcion)
			{
				case 1:
					if(banderaCargaModoTxt==0)
					{
						if(controller_loadFromText("arcades.csv",listaArcades)==0)
						{
							printf("\nLista cargada exitosamente\n");
							banderaCargaModoTxt=1;
						}
					}
					else
					{
						printf("\nLa lista ya fue cargada\n");
					}
					break;
				case 2:
			    	if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
			    	else
			    	{
						if(controller_addArcade(listaArcades)==0)
						{
							printf("\nArcade cargado exitosamente\n");
						}
						else
						{
							printf("\nNo se pudo cargar el arcade. Intentelo nuevamente\n");
						}
			    	}
			    	break;
				case 3:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						if(controller_editArcade(listaArcades,listaJuegosNoRepetidos)==0)
						{
							printf("\nArcade modificado exitosamente\n");
						}
						else
						{
							printf("\nNo se pudo modificar el arcade. Intentelo nuevamente\n");
						}
					}
					break;
				case 4:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						if(controller_removeArcade(listaArcades)==0)
						{
							printf("\nBaja realizada con éxito\n");
						}
						else
						{
							printf("\nNo se pudo dar de baja al arcade. Intentelo nuevamente\n");
						}
					}
					break;
				case 5:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						if(controller_ListArcade(listaArcades)==0)
						{
							printf("\nLista de arcades imprimida con éxito\n");
						}
						else
						{
							printf("\nNo se pudo imprimir la lista de arcades. Intentelo nuevamente\n");
						}
					}
					break;
				case 6:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						if(controller_createGameList(listaJuegosNoRepetidos, listaArcades)==0)
						{
							controller_ListGames(listaJuegosNoRepetidos);
							controller_saveJuegosAsText("juegos.txt", listaJuegosNoRepetidos);
						}
						else
						{
							printf("\nNo se pudo generar la lista de juegos. Intentelo nuevamente\n");
						}
					}
					break;
				case 7:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						listaMultijugadores=ll_clone(listaArcades);
						if(controller_createMultijugadorList(listaMultijugadores)==0)
						{
							if(controller_saveAsText("multijugador.csv", listaMultijugadores)==0)
							{
								printf("\nArchivo multijugador generado correctamente\n");
							}
						}
						else
						{
							printf("\nNo se pudo generar la lista de arcades multijugadores. Intentelo nuevamente\n");
						}
					}
					break;
				case 8:
					if(banderaCargaModoTxt==0)
					{
						printf("\nPor favor, primero cargue la lista en memoria\n");
					}
					else
					{
						if(controller_updateNumberOfCoins(listaArcades)==0)
						{
							if(controller_saveAsText("arcades.csv", listaArcades)==0)
							{
								printf("\nCantidad de fichas actualizada correctamente\n");
							}
						}
						else
						{
							printf("\nNo se pudo actualizar la cantidad de fichas. Intentelo nuevamente\n");
						}
					}
					break;
				case 9:
					controller_exitDelete(listaArcades);
					controller_exitDelete(listaJuegosNoRepetidos);
					controller_exitDelete(listaMultijugadores);
					printf("\n¡Gracias por utilizar el Administrador de arcades!\n");
					break;
				default:
					printf("\nOpción inválida. Elija las opciones de la 1 a la 9, por favor\n");
					break;
			}
		}

	}while(opcion!=9);

	return EXIT_SUCCESS;
}
