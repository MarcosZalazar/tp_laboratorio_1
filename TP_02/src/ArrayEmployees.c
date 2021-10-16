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

int removeEmployee(Empleado* list, int len, int id)
{
	int retorno=-1;
	int indiceADarDeBaja;

	if(list!= NULL && len >=0 && id >=0)
	{
		indiceADarDeBaja=findEmployeeById(list,len,id);
		if(indiceADarDeBaja<=0)
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


int sortEmployee(Empleado* list, int len, int order) //1 DE MENOR A MAYOR //2 DE MAYOR A MENOR
{
	int retorno=-1;
	int flagSwap;
	int i;
	Empleado bufferEmpleado;
	int auxiliarCmp;

	if(list!=NULL && len>=0 && (order==1 ||order==2 ))
	{
		switch(order)
		{
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
			case 2:
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
		}
	}
	return retorno;
}

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

int idGenerator(void)
{
	static int contadorId=0;

	return contadorId++;
}

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
