/*
 * Empleados.c
 *
 *  Created on: 1 oct. 2021
 *      Author: Marcos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

/// \fn int initEmployees(Empleado*, int)
/// \brief Para indicar que todas las posiciones en el array estan vacias, esta función pone la bandera (isEmpty) en
///        TRUE en todas las posiciones del array.
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \return  0: Array inicializado correctamente.
/// 		-1: Error.

int initEmployees(Empleado* list, int len)
{
	int retorno=-1;
	int i;

	if(list!= NULL && len >=0)
	{
		for(i=0;i<len;i++)
		{
			list[i].isEmpty=1;
		}
		retorno=0;
	}
	return retorno;
}

/// \fn int addEmployee(Empleado*, int, int, char[], char[], float, int)
/// \brief Agrega en un array de empleados existente los valores recibidos como parametro en la primer posicion
///        libre.
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param id: Id del empleado
/// \param name: Nombre del empleado
/// \param lastName: Apellido del empleado
/// \param salary: Salario del empleado
/// \param sector: Sector en el que trabaja el empleado
/// \return  0: Empleado agregado correctamente.
/// 		-1: Error.
/// 		-2: Error, no se encontro un lugar vacio en la nomina

int addEmployee(Empleado* list, int len, int id, char name [], char lastName[], float salary, int sector)
{
	int retorno=-1;
	int indiceVacio;

	if(list!= NULL && len >=0 && id >=0 && name!= NULL && lastName!= NULL && salary >=1 && sector >=1)
	{
		indiceVacio=getEmptyIndex(list, len);
		if(indiceVacio>=0)
		{
			list[indiceVacio].id=id;
			strncpy(list[indiceVacio].nombre,name,sizeof(list->nombre));
			strncpy(list[indiceVacio].apellido,lastName,sizeof(list->apellido));
			list[indiceVacio].salario=salary;
			list[indiceVacio].sector=sector;
			list[indiceVacio].isEmpty=0;
			retorno=0;
		}
		else
		{
			if(indiceVacio==-2)
			{
				retorno=-2;
			}
		}
	}
	return retorno;
}

/// \fn int findEmployeeById(Empleado*, int, int)
/// \brief Busca un empleado recibiendo como parametro de busqueda su Id
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param id: Id del empleado
/// \return: 0 o numeros positivos: indice del array en que se encontro el id de empleado buscado.
/// 		-1: Error.
/// 		-2: Error, no se encontro el id solicitado en la nomina

int findEmployeeById(Empleado* list, int len, int id)
{
	int retorno=-1;
	int i;

	if(list!= NULL && len >=0 && id >=0)
	{
		retorno=-2;
		for(i=0;i<len;i++)
		{
			if(list[i].id==id)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

/// \fn int removeEmployee(Empleado*, int, int)
/// \brief Elimina de manera lógica (isEmpty FLag en 1) un empleado recibiendo como parametr su Id.
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param id: Id del empleado
/// \return  0: Empleado dado de baja exitosamente
/// 		-1: Error.
/// 		-2: Error, no se encontro el id solicitado en la nomina

int removeEmployee(Empleado* list, int len, int id)
{
	int retorno=-1;
	int indiceADarDeBaja;

	if(list!= NULL && len >=0 && id >=0)
	{
		indiceADarDeBaja=findEmployeeById(list,len,id);
		if(indiceADarDeBaja>=0)
		{
			list[indiceADarDeBaja].isEmpty=1;
			retorno=0;
		}
		else
		{
			if(indiceADarDeBaja==-2)
			{
				retorno=-2;
			}
		}
	}
	return retorno;
}

/// \fn int sortEmployee(Empleado*, int, int)
/// \brief Ordena el array de empleados por apellido y sector de manera ascendente o descendente
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param order: Orden de ordenamieto (0:descendente, 1:ascendente)
/// \return  0: Array ordenado exitosamente
/// 		-1: Error.

int sortEmployee(Empleado* list, int len, int order)
{
	int retorno=-1;
	int flagSwap;
	int i;
	Empleado bufferEmpleado;
	int auxiliarCmp;

	if(list!=NULL && len>=0 && (order==0 ||order==1 ))
	{
		switch(order)
		{
			case 0:
				do
				{
					flagSwap=0;
					for(i=0;i<len-1;i++)
					{
						if(list[i].isEmpty==1||list[i+1].isEmpty==1)
						{
							continue;
						}
						auxiliarCmp=strncmp(list[i].apellido,list[i+1].apellido,len);
						if(auxiliarCmp<0 ||(auxiliarCmp==0 && list[i].sector<list[i+1].sector))
						{
							flagSwap=1;
							bufferEmpleado=list[i];
							list[i]=list[i+1];
							list[i+1]=bufferEmpleado;
						}
					}
					len--;
				}while(flagSwap==1);

				retorno=0;
				break;

				case 1:
					do
					{
						flagSwap=0;
						for(i=0;i<len-1;i++)
						{
							if(list[i].isEmpty==1||list[i+1].isEmpty==1)
							{
								continue;
							}
							auxiliarCmp=strncmp(list[i].apellido,list[i+1].apellido,len);
							if(auxiliarCmp>0 ||(auxiliarCmp==0 && list[i].sector>list[i+1].sector))
							{
								flagSwap=1;
								bufferEmpleado=list[i];
								list[i]=list[i+1];
								list[i+1]=bufferEmpleado;
							}
						}
						len--;
					}while(flagSwap==1);

					retorno=0;
					break;
		}
	}
	return retorno;
}

/// \fn int printEmployee(Empleado*, int)
/// \brief Imprime el array de empleados de forma encolumnada
/// \param list: Puntero al array de empleados
/// \param lenght: Tamaño del array de empleados
/// \return  0: Array imprimido exitosamente
/// 		-1: Error.

int printEmployee(Empleado* list, int lenght)
{
	int retorno=-1;
	int i;

	if(list!=NULL && lenght>=0)
	{
		printf("\nId  Nombre     		     Apellido     	      Salario        Sector");
		for(i=0;i<lenght;i++)
		{
			if(list[i].isEmpty==0)
			{
				printf("\n%-3d %-20s     %-20s     %-10.2f     %-10d",list[i].id, list[i].nombre,list[i].apellido,list[i].salario,list[i].sector);
			}
		}
		retorno=0;
	}
	return retorno;
}

/// \fn int getEmptyIndex(Empleado*, int)
/// \brief: Obtiene un espacio vacio en el array de empleados y devuelve el indice de su ubicacion
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \return  0 o numeros positivos: indice del array en que se encontro un indice vacio
/// 		-1: Error.
/// 		-2: Error, no se encontro un indice vacio en la nomina

int getEmptyIndex(Empleado* list, int len)
{
	int retorno=-1;
	int i;

	if(list!= NULL && len >=0)
	{
		retorno=-2;
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty==1)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}

/// \fn int idGenerator(void)
/// \brief Genera un id de empleados automaticamente
/// \return Devuelve el numero de Id generado

int idGenerator(void)
{
	static int contadorId=0;

	return contadorId++;
}

/// \fn int modifyEmployee(Empleado*, int, int)
/// \brief Modifica los datos del empleado en el array de acuerdo al id recibido
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param id: Id del empleado
/// \return  0: Empleado modificado exitosamente
/// 		-1: Error.
/// 		-2: Error, no se encontro el id solicitado en la nomina

int modifyEmployee(Empleado* list, int len, int id)
{
	int retorno=-1;
	int indiceAModificar;
	Empleado bufferEmpleado;
	int opcionCampoAModificar;

	if(list!= NULL && len >=0 && id >=0)
	{
		indiceAModificar=findEmployeeById(list,len,id);
		if(indiceAModificar>=0 && list[indiceAModificar].isEmpty==0)
		{
			do{
				printf("**************************************************\n");
				printf("¿Cual campo desea modificar?\n");
				printf("1) Nombre\n");
				printf("2) Apellido\n");
				printf("3) Salario\n");
				printf("4) Sector\n");
				printf("5) Ninguno, volver al menu principal\n");
				printf("**************************************************\n");
				utn_getNumeroInt(&opcionCampoAModificar,"\nIngrese la opción","\nOpción inválido",1,5,3);

				switch(opcionCampoAModificar)
				{
					case 1:
						if(utn_getChar(bufferEmpleado.nombre,"\nIngrese el nombre a modificar","\nNombre inválido",NOMBRE_LEN,3)==0)
						{
							strncpy(list[indiceAModificar].nombre,bufferEmpleado.nombre,sizeof(list[indiceAModificar].nombre));
							retorno=0;
						}
						break;
					case 2:
						if(utn_getChar(bufferEmpleado.apellido,"\nIngrese el apellido a modificar","\nApellido inválido",APELLIDO_LEN,3)==0)
						{
							strncpy(list[indiceAModificar].apellido,bufferEmpleado.apellido,sizeof(list[indiceAModificar].apellido));
							retorno=0;
						}
						break;
					case 3:
						if(utn_getNumeroFlotante(&bufferEmpleado.salario,"\nIngrese el salario a modificar","\nSalario inválido",1,100000000,3)==0)
						{
							list[indiceAModificar].salario=bufferEmpleado.salario;
							retorno=0;
						}
						break;
					case 4:
						if(utn_getNumeroInt(&bufferEmpleado.sector,"\nIngrese el sector a modificar","\nSector inválido",1,100000000,3)==0)
						{
							list[indiceAModificar].sector=bufferEmpleado.sector;
							retorno=0;
						}
						break;
				}
			}while(opcionCampoAModificar!=5);
		}
		else
		{
			if(indiceAModificar==-2)
			{
				retorno=-2;
			}
		}
	}
	return retorno;
}

/// \fn int infoSalaries(Empleado*, int, float*, float*, int*)
/// \brief Calcula cuanto es el total de los salarios, el salario promedio y cuantos empleados superan el salario
///        promedio
/// \param list: Puntero al array de empleados
/// \param len: Tamaño del array de empleados
/// \param pTotalSalaries: Total de salarios
/// \param pAverageSalary: Promedio de los salarios
/// \param employeesAboveAverageSalary: Cantidad de empleados cuyo salario está por encima del promedio de salarios
/// \return  0: Informacion provista exitosamente
/// 		-1: Error.

int infoSalaries(Empleado* list, int len,float* pTotalSalaries, float* pAverageSalary,int* employeesAboveAverageSalary)
{
	int retorno=-1;
	int i;
	float acumuladorSalarios=0;
	float promedioDeSalarios;
	int contadorSalarios=0;
	int contadorSalariosArribaDelPromedio=0;

	if(list!=NULL && len>=0)
	{
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty==1)
			{
				continue;
			}
			else
			{
				acumuladorSalarios=acumuladorSalarios+list[i].salario;
				contadorSalarios++;
			}
		}
		*pTotalSalaries=acumuladorSalarios;
		promedioDeSalarios=acumuladorSalarios/contadorSalarios;
		*pAverageSalary=promedioDeSalarios;

		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty==1)
			{
				continue;
			}
			else
			{
				if(list[i].salario>promedioDeSalarios)
				{
					contadorSalariosArribaDelPromedio++;
				}
			}
		}
		*employeesAboveAverageSalary=contadorSalariosArribaDelPromedio;
		retorno=0;
	}
	return retorno;
}
