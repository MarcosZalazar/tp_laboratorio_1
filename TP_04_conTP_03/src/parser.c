#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param pFile*: Puntero al archivo a parsear
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Parseo de empleados en modo texto realizado correctamente
 * 		      -1: Error.
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	char auxId[1000];
	char auxNombre[1000];
	char auxHorasTrabajadas[1000];
	char auxSueldo[1000];
	Employee* pEmployee;


	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo)== 4)
			{
				pEmployee=employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
				if(pEmployee!= NULL)
				{
					ll_add(pArrayListEmployee, pEmployee);
				}
			}
			else
			{
				employee_delete(pEmployee);
				break;
			}
		}while(feof(pFile)==0);
		retorno = 0;
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param pFile*: Puntero al archivo a parsear
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Parseo de empleados en modo binario realizado correctamente
 * 		      -1: Error.
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	Employee* pEmployee;

	if(pFile != NULL && pArrayListEmployee != NULL)
	{
		do
		{
			pEmployee=employee_new();
			if(pEmployee!= NULL)
			{
				if(fread(pEmployee, sizeof(Employee), 1, pFile) == 1)
				{
					ll_add(pArrayListEmployee, pEmployee);
					retorno = 0;
				}
				else
				{
					employee_delete(pEmployee);
					break;
				}
			}
		}while(feof(pFile)==0);

	}
    return retorno;
}
