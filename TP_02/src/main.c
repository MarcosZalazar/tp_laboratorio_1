/*
 ============================================================================
 Name        : TP_02.c
 Author      : Marcos Zalazar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

#define CANT_EMPLEADOS 1000
#define ORDEN_ASCENDENTE 1
#define ORDEN_DESCENDENTE 0

int main(void)
{
	Empleado arrayEmpleados[CANT_EMPLEADOS];
	int opcion;
	int auxId;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[APELLIDO_LEN];
	float auxSalario;
	int auxSector;
	int idABuscar;
	int orden;
	float totalSalarios;
	float salarioPromedio;
	int cantSalariosArribaDelPromedio;
	int banderaAltas;

	setbuf(stdout, NULL);

	initEmployees(arrayEmpleados, CANT_EMPLEADOS);
	banderaAltas=0;

	do{
		printf("**************************************************\n");
		printf("Bienvenido al Administrador de nómina de empleados\n");
		printf("1) Altas de empleados\n");
		printf("2) Modificar legajos de empleados\n");
		printf("3) Baja de empleados\n");
		printf("4) Informes\n");
		printf("5) Salir\n");
		printf("**************************************************\n");

		utn_getNumeroInt(&opcion,"\nIngrese la opción","\nOpción inválido",1,5,3);

		switch(opcion)
		{
			case 1:
				auxId=idGenerator();
				if( utn_getChar(auxNombre,"\nIngrese el nombre","\nNombre inválido\n",NOMBRE_LEN,3)==0 &&
				    utn_getChar(auxApellido,"\nIngrese el apellido","\nApellido inválido\n",APELLIDO_LEN,3)==0 &&
				    utn_getNumeroFlotante(&auxSalario,"\nIngrese el salario","\nSalario inválido\n",1,100000000,3)==0 &&
				    utn_getNumeroInt(&auxSector,"\nIngrese el sector","\nSector inválido\n",1,100000000,3)==0)
				{
					if(addEmployee(arrayEmpleados, CANT_EMPLEADOS, auxId,auxNombre, auxApellido,auxSalario, auxSector)==0)
					{
						printf("\nCarga de cliente exitosa\n\n");
						banderaAltas++;
					}
					else
					{
						if(addEmployee(arrayEmpleados, CANT_EMPLEADOS, auxId,auxNombre, auxApellido,auxSalario, auxSector)==-2)
						{
							printf("\nNo hay más lugares en la nómina de empleados\n\n");
						}
						else
						{
							printf("\nError! Revise los valores ingresados\n\n");
						}
					}
				}
				break;
			case 2:
				if(banderaAltas>0)
				{
					utn_getNumeroInt(&orden,"\nIngrese el criterio para odenar el listado de empleados (1-Ascendente, 2-Descendente)","\nCriterio inválido\n",1,2,3);
					if(sortEmployee(arrayEmpleados,CANT_EMPLEADOS,orden)==0)
					{
						printEmployee(arrayEmpleados,CANT_EMPLEADOS);
					}
					if(utn_getNumeroInt(&idABuscar,"\n\nIngrese el ID del empleado","\nId inválido\n",0,100000000,3)==0)
					{
						if(modifyEmployee(arrayEmpleados, CANT_EMPLEADOS,idABuscar)==0)
						{
							printf("\nModificación de cliente exitosa\n\n");
						}
						else
						{
							if(modifyEmployee(arrayEmpleados, CANT_EMPLEADOS,idABuscar)==-2)
							{
								printf("\nNo se encontró el Id solicitado. Inténtelo nuevamente\n\n");
							}
							else
							{
								printf("\nError!No se pudo modificar al empleado\n\n");
							}
						}
					}
					else
					{
						printf("\nError!Revise los datos ingresados\n\n");
					}
				}
				else
				{
					printf("\nNo existen empleados a modificar en el sistema.\n\n");
				}
				break;
			case 3:
				if(banderaAltas>0)
				{
					if(utn_getNumeroInt(&idABuscar,"\nIngrese el ID del empleado","\nId inválido\n",0,100000000,3)==0)
					{
						if(removeEmployee(arrayEmpleados,CANT_EMPLEADOS,idABuscar)==0)
						{
							printf("\nEmpleado dado de baja exitosamente\n\n");
						}
						else
						{
							if(removeEmployee(arrayEmpleados,CANT_EMPLEADOS,idABuscar)==-2)
									{
										printf("\nNo se encontró el Id solicitado. Inténtelo nuevamente\n\n");
									}
									else
									{
										printf("\nError!No se pudo modificar al empleado\n\n");
									}
						}
					}
					else
					{
						printf("\nError!Revise los datos ingresados\n\n");
					}
				}
				else
				{
					printf("\nNo existen empleados a dar de baja en el sistema.\n\n");
				}
				break;
			case 4:
				if(banderaAltas>0)
				{
					utn_getNumeroInt(&orden,"\nIngrese el criterio para odenar el listado de empleados (1-Ascendente, 2-Descendente)","\nCriterio inválido\n",1,2,3);
					if(sortEmployee(arrayEmpleados,CANT_EMPLEADOS,orden)==0)
					{
						printEmployee(arrayEmpleados,CANT_EMPLEADOS);
						infoSalaries(arrayEmpleados, CANT_EMPLEADOS,&totalSalarios, &salarioPromedio,&cantSalariosArribaDelPromedio);
						printf("\n\nTotal de Salarios     Salario Promedio     Cantidad de empleados arriba del salario promedio");
						printf("\n%-10.2f 	      %-10.2f 	   %-10d\n\n",totalSalarios,salarioPromedio,cantSalariosArribaDelPromedio);
					}
					else
					{
						printf("\nNo se pudo imprimir el informe\n\n");
					}
				}
				else
				{
					printf("\nNo hay empleados cargados en el sistema a informar\n\n");
				}
				break;
			case 5:
				printf("¡Gracias por utilizar el Administrador de nómina de empleados!\n\n");
				break;
			default:
				printf("Opción inválida. Elija las opciones 1,2,3,4 o 5, por favor\n");
				break;
		}

	}while(opcion!=5);

	return EXIT_SUCCESS;
}
