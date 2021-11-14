#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/

int main()
{
    setbuf(stdout, NULL);

    int option = 0;
    char respuesta;
    int banderaCargaModoTxt=0;
    int banderaCargaModoBinario=0;
    int banderaGuardadoModoTexto=0;
    int banderaGuardadoModoBinario=0;


    LinkedList* listaEmpleados = ll_newLinkedList();

    controller_registerLastIdFirstTime();
    controller_createBinaryFile();

    do{
    	printf("******************************************************************************\n");
		printf("Bienvenido al Administrador de nómina de empleados\n");
		printf("1) Cargar los datos de los empleados desde el archivo data.csv (modo texto)\n");
		printf("2) Cargar los datos de los empleados desde el archivo data.bin (modo binario)\n");
		printf("3) Alta de empleado\n");
		printf("4) Modificar datos de empleado\n");
		printf("5) Baja de empleado\n");
		printf("6) Listar empleados\n");
		printf("7) Ordenar empleados\n");
		printf("8) Guardar los datos de los empleados en el archivo data.csv (modo texto)\n");
		printf("9) Guardar los datos de los empleados en el archivo data.bin (modo binario)\n");
		printf("10) Salir\n");
		printf("*****************************************************************************\n");

		utn_getNumeroInt(&option,"\nIngrese la opción","\nOpción inválido",1,10,3);

        switch(option)
        {
            case 1:
              	if(banderaCargaModoBinario==0)
              	{
					if(controller_loadFromText("data.csv",listaEmpleados)==0)
					{
						printf("\nLista cargada exitosamente\n");
						banderaCargaModoTxt=1;
					}
					else
					{
						printf("\nNo se pudo cargar la lista. Intentelo nuevamente\n");
					}
              	}
              	else
              	{
					printf("\nLa lista ya fue cargada(en modo binario), no puede cargarla nuevamente\n");
              	}
                break;
            case 2:
            	if(banderaCargaModoTxt==0)
            	{
					if(controller_loadFromBinary("data.bin",listaEmpleados)==0)
					{
						printf("\nLista cargada exitosamente\n");
						banderaCargaModoBinario=1;
					}
					else
					{
						printf("\nNo se pudo cargar la lista. Intentelo nuevamente\n");
					}
            	}
            	else
            	{
            		printf("\nLa lista ya fue cargada(en modo texto), no puede cargarla nuevamente\n");
            	}
                break;
            case 3:
            	if(banderaCargaModoTxt==0 && banderaCargaModoBinario==0)
            	{
            		printf("\nAl momento de realizar esta alta, aún no ha cargado la lista de empleados. Recuerde hacerlo para evitar pérdida de datos\n");
            	}
				if(controller_addEmployee(listaEmpleados)==0)
				{
					printf("\nEmpleado cargado exitosamente\n");
				}
				else
				{
					printf("\nNo se pudo cargar el empleado. Intentelo nuevamente\n");
				}
                break;
            case 4:
              	if(controller_editEmployee(listaEmpleados)==0)
				{
					printf("\nEmpleado modificado exitosamente\n");
				}
				else
				{
					printf("\nNo se pudo modificar el empleado. Intentelo nuevamente\n");
				}
                break;
            case 5:
               	if(controller_removeEmployee(listaEmpleados)==0)
				{
					printf("\nBaja realizada con éxito\n");
				}
				else
				{
					printf("\nNo se pudo dar de baja al empleado. Intentelo nuevamente\n");
				}
                break;
            case 6:
               	if(controller_ListEmployee(listaEmpleados)==0)
				{
					printf("\nLista de empleados imprimida con éxito\n");
				}
				else
				{
					printf("\nNo se pudo imprimir la lista de empleados. Intentelo nuevamente\n");
				}
                break;
            case 7:
               	if(controller_sortEmployee(listaEmpleados)==0)
				{
					printf("\nLista de empleados ordenada con éxito\n");
				}
				else
				{
					printf("\nNo se pudo ordenar la lista de empleados. Intentelo nuevamente\n");
				}
                break;
            case 8:
            	if(banderaCargaModoTxt==0 && banderaCargaModoBinario==0)
            	{
            		printf("\nSi guarda el archivo, va a sobreescribir la información que actualmente posee en ella.\n");
					utn_getChar(&respuesta,"\nEsta seguro que desea continuar?(s=SI n=NO)\n","\nOpción invalida",2,3);
					if(respuesta=='s')
					{
						if(controller_saveAsText("data.csv",listaEmpleados)==0)
						{
							printf("\nDatos guardados en el archivo con éxito\n");
							banderaGuardadoModoTexto=1;
						}
						else
						{
							printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
						}
					}
					else
					{
						printf("\nOperación cancelada.Se recomienda cargar la lista\n");
					}
            	}
            	else
            	{
            		if(banderaCargaModoTxt==1)
            		{
            			if(controller_saveAsText("data.csv",listaEmpleados)==0)
						{
							printf("\nDatos guardados en el archivo con éxito\n");
							banderaGuardadoModoTexto=1;
						}
						else
						{
							printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
						}

            		}
            		if(banderaCargaModoBinario==1)
            		{
            			printf("\nLa carga original se hizo en modo binario. La información podria quedar desactualizada.\n");
						utn_getChar(&respuesta,"\nEsta seguro que desea continuar?(s=SI n=NO)\n","\nOpción invalida",2,3);
						if(respuesta=='s')
						{
							if(controller_saveAsText("data.csv",listaEmpleados)==0)
							{
								printf("\nDatos guardados en el archivo con éxito\n");
								banderaGuardadoModoTexto=1;
							}
							else
							{
								printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
							}
						}
						else
						{
							printf("\nOperación cancelada.Se recomienda guardar la lista en modo binario\n");
						}

            		}
            	}
                break;
            case 9:
            	if(banderaCargaModoTxt==0 && banderaCargaModoBinario==0)
            	{
             		printf("\nSi guarda el archivo, va a sobreescribir la información que actualmente posee en ella.\n");
					utn_getChar(&respuesta,"\nEsta seguro que desea continuar?(s=SI n=NO)\n","\nOpción invalida",2,3);
					if(respuesta=='s')
					{
						if(controller_saveAsBinary("data.bin",listaEmpleados)==0)
						{
							printf("\nDatos guardados en el archivo con éxito\n");
							banderaGuardadoModoBinario=1;
						}
						else
						{
							printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
						}
					}
					else
					{
						printf("\nOperación cancelada.Se recomienda cargar la lista\n");
					}
				}
				else
				{
					if(banderaCargaModoBinario==1)
					{
						if(controller_saveAsBinary("data.bin",listaEmpleados)==0)
						{
							printf("\nDatos guardados en el archivo con éxito\n");
							banderaGuardadoModoBinario=1;
						}
						else
						{
							printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
						}

					}
					if(banderaCargaModoTxt==1)
					{
						printf("\nLa carga original se hizo en modo texto. La información podria quedar desactualizada.\n");
						utn_getChar(&respuesta,"\nEsta seguro que desea continuar?(s=SI n=NO)\n","\nOpción invalida",2,3);
						if(respuesta=='s')
						{
							if(controller_saveAsBinary("data.bin",listaEmpleados)==0)
							{
								printf("\nDatos guardados en el archivo con éxito\n");
								banderaGuardadoModoBinario=1;
							}
							else
							{
								printf("\nNo se pudo guardar los datos en el archivo. Intentelo nuevamente\n");
							}
						}
						else
						{
							printf("\nOperación cancelada.Se recomienda guardar la lista en modo texto\n");
						}

					}
				}
                break;
            case 10:
            	if(banderaGuardadoModoTexto==0 && banderaGuardadoModoBinario==0)
            	{
            		printf("\nNo se guardaron los datos, podría perder información\n");
            		utn_getChar(&respuesta,"\nEsta seguro que desea continuar?(s=SI n=NO)\n","\nOpción invalida",2,3);
					if(respuesta=='s')
					{
						if(controller_exitWarning(listaEmpleados)==0)
						{
							printf("\n¡Gracias por utilizar el Administrador de nómina de empleados!\n");
							option=10;
						}
						else
						{
							printf("\nError. Intentelo nuevamente\n");
						}
					}
					else
					{
						printf("\nOperación cancelada\n");
					}
            	}
            	break;
            default:
            	printf("\nOpción inválida. Elija las opciones 1 a 10, por favor\n");
                break;
        }
    }while(option != 10);
    return 0;
}

