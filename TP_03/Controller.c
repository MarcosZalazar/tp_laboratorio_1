#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#include "validaciones.h"
#include "parser.h"

/** \brief Revisa el archivo de información y registra por primera vez el primer ID disponible.
 *
 */
void controller_registerLastIdFirstTime(void)
{
	FILE* pArchivoData;
	FILE* pArchivoId;
	char auxId[ID_LEN];
	char auxNombre[NOMBRE_LEN];
	char auxHorasTrabajadas[HORASTRABAJADAS_LEN];
	char auxSueldo[SUELDO_LEN];
	int lastID;

	pArchivoData = fopen("data.csv","r");
	if(pArchivoData != NULL)
	{
		fscanf(pArchivoData,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
		do
		{
			fscanf(pArchivoData,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);

		}while(feof(pArchivoData)==0);
		lastID=atoi(auxId);
		lastID=lastID+1;
		fclose(pArchivoData);
	}

	pArchivoId = fopen("RegistroIdDisponible.txt","w");
	if(pArchivoId != NULL)
	{
		fprintf(pArchivoId,"%d",lastID);
		fclose(pArchivoId);
	}
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*:Puntero al archivo desde el que se leen los datos del empleado
 * \param pArrayListEmployee LinkedList*: Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados cargada correctamente.
 * 		      -1: Error.
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pArchivo;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pArchivo = fopen(path,"r");
		if(pArchivo != NULL)
		{
			parser_EmployeeFromText(pArchivo,pArrayListEmployee);
			fclose(pArchivo);
			retorno = 0;
		}

	}
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.bin (modo binario).
 *
 * \param path char*:Puntero al archivo desde el que se leen los datos del empleado
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados cargada correctamente.
 * 		      -1: Error.
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pArchivo;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pArchivo = fopen(path,"r+b");
		if(pArchivo != NULL && parser_EmployeeFromBinary(pArchivo,pArrayListEmployee)==0)
		{
			fclose(pArchivo);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Empleado dado de alta correctamente
 * 		      -1: Error.
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	Employee* pEmployee;
	int retorno = -1;
	char idACargar[ID_LEN];
	char nombreACargar[NOMBRE_LEN];
	char horasTrabajadasACargar[HORASTRABAJADAS_LEN];
	char sueldoACargar[SUELDO_LEN];

	if(pArrayListEmployee != NULL)
	{
		if(utn_getChar(nombreACargar,"\nIngrese el nombre","\nNombre invalido\n",NOMBRE_LEN,3)==0 &&
		   utn_getNumeroEnteroPositivoComoChar(horasTrabajadasACargar,"\nIngrese la cantidad de horas trabajadas","\nCantidad invalida\n",HORASTRABAJADAS_LEN,3)==0 &&
		   utn_getNumeroEnteroPositivoComoChar(sueldoACargar,"\nIngrese el sueldo","\nSueldo invalido\n", SUELDO_LEN,3)==0)
		{
			IdGenerator(idACargar);
			pEmployee=employee_newParametros(idACargar,nombreACargar,horasTrabajadasACargar,sueldoACargar);
			if(pEmployee!=NULL)
			{
				if(ll_add(pArrayListEmployee, pEmployee)==0)
				{
					retorno = 0;
				}
			}
		}

	}
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList* :Puntero a la Linkedlist de empleados
 * \return int 0: Empleado modificado correctamente
 * 		      -1: Error.
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int IdAModificar;
	int auxIndiceAModificar;

	if(controller_ListEmployee(pArrayListEmployee)==0)
	{
		if(utn_getNumeroInt(&IdAModificar,"\nID del empleado a modificar?\n","\nId invalido\n",0,1000000,3)==0)
		{
			auxIndiceAModificar=employee_findById(pArrayListEmployee,IdAModificar);
			if(auxIndiceAModificar >=0)
			{
				if(modifyEmployee(pArrayListEmployee,auxIndiceAModificar)==0)
				{
					retorno = 0;
				}
			}
			else
			{
				printf("\nId no encontrado\n");
			}
		}
	}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList* :Puntero a la Linkedlist de empleados
 * \return int 0: Empleado dado de baja correctamente
 * 		      -1: Error.
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int IdAEliminar;
	int auxIndiceAborrar;
	Employee* pEmployee;

	if(pArrayListEmployee!=NULL)
	{
		if(controller_ListEmployee(pArrayListEmployee)==0)
		{
			if(utn_getNumeroInt(&IdAEliminar,"\nID del empleado a dar de baja? ","\nId invalido",0,1000000,3)==0)
			{
				auxIndiceAborrar=employee_findById(pArrayListEmployee,IdAEliminar);
				if(auxIndiceAborrar>=0)
				{
					pEmployee=ll_get(pArrayListEmployee,auxIndiceAborrar);
					employee_delete(pEmployee);
					ll_remove(pArrayListEmployee,auxIndiceAborrar);
					retorno = 0;
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

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados imprimida correctamente
 * 		      -1: Error.
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	int i;
	int lenList;
	Employee* pEmployee;


	if(pArrayListEmployee != NULL)
	{
		lenList=ll_len(pArrayListEmployee);
		if(lenList>0)
		{
			printf("ID-NOMBRE-HORAS TRABAJADAS-SUELDO\n");
			for(i=0;i<=lenList;i++)
			{
				pEmployee=ll_get(pArrayListEmployee,i);
				if(pEmployee!=NULL)
				{
					employee_printEmployee(pEmployee);
				}
			}
			retorno = 0;
		}
		else
		{
			printf("No hay empleados a listar");
			retorno = -2;
		}
	}
	return retorno;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList* :Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados ordenada correctamente
 * 		      -1: Error.
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int opcionParaOrdenar;
	int retorno=-1;
	int orden;
	int lenList;

	if(pArrayListEmployee!= NULL)
	{
		lenList=ll_len(pArrayListEmployee);
		if(lenList>0)
		{
			do{
					printf("**************************************************\n");
					printf("¿Por cual criterio desea ordenar la lista?\n");
					printf("15) Id\n");
					printf("16) Nombre\n");
					printf("17) Horas trabajadas\n");
					printf("18) Sueldo\n");
					printf("19) Salir\n");
					printf("**************************************************\n");

					if(utn_getNumeroInt(&opcionParaOrdenar,"\nIngrese la opción","\nOpción inválida\n",15,19,3)==0)
					{
						switch(opcionParaOrdenar)
						{
							case 15:
								utn_getNumeroInt(&orden,"\nIngrese el criterio para ordenar el listado de empleados (0-Descendente, 1-Ascendente)","\nCriterio inválido\n",0,1,3);
								ll_sort(pArrayListEmployee, employee_compareById,orden);
								controller_ListEmployee(pArrayListEmployee);
								retorno=0;
								break;
							case 16:
								utn_getNumeroInt(&orden,"\nIngrese el criterio para ordenar el listado de empleados (0-Descendente, 1-Ascendente)","\nCriterio inválido\n",0,1,3);
								ll_sort(pArrayListEmployee, employee_compareByName,orden);
								controller_ListEmployee(pArrayListEmployee);
								retorno=0;
								break;
							case 17:
								utn_getNumeroInt(&orden,"\nIngrese el criterio para ordenar el listado de empleados (0-Descendente, 1-Ascendente)","\nCriterio inválido\n",0,1,3);
								ll_sort(pArrayListEmployee, employee_compareByHoursWorked,orden);
								controller_ListEmployee(pArrayListEmployee);
								retorno=0;
								break;
							case 18:
								utn_getNumeroInt(&orden,"\nIngrese el criterio para ordenar el listado de empleados (0-Descendente, 1-Ascendente)","\nCriterio inválido\n",0,1,3);
								ll_sort(pArrayListEmployee, employee_compareBySalary,orden);
								controller_ListEmployee(pArrayListEmployee);
								retorno=0;
								break;
						}
					}
					else
					{
						break;
					}
				}while(opcionParaOrdenar!=19);
		}
		else
		{
			printf("No hay empleados a listar");
		}
	}
	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*: Puntero al archivo desde en el que se guardan los datos del empleado
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados guardada correctamente (modo texto)
 * 		      -1: Error.
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pArchivo;
	int lenArrayListEmployee;
	int i;
	Employee* pAuxEmployee;
	int auxId;
	char auxNombre[NOMBRE_LEN];
	int auxHorasTrabajadas;
	int auxSueldo;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pArchivo = fopen(path,"w");
		if(pArchivo != NULL)
		{
			lenArrayListEmployee = ll_len(pArrayListEmployee);
			if(lenArrayListEmployee>0)
			{
				fprintf(pArchivo,"%s,%s,%s,%s\n","Id","Nombre","Horas trabajadas","Sueldo");
				for(i=0; i<lenArrayListEmployee; i++)
				{
					pAuxEmployee = (Employee*)ll_get(pArrayListEmployee,i);
					if(pAuxEmployee!=NULL)
					{
						employee_getId(pAuxEmployee,&auxId);
						employee_getNombre(pAuxEmployee,auxNombre);
						employee_getHorasTrabajadas(pAuxEmployee,&auxHorasTrabajadas);
						employee_getSueldo(pAuxEmployee,&auxSueldo);
						fprintf(pArchivo,"%d,%s,%d,%d\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
					}
				}
			}
			fclose(pArchivo);
			retorno = 0;
		}
	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*: Puntero al archivo desde en el que se guardan los datos del empleado
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados guardada correctamente (modo binario)
 * 		      -1: Error.
 */

int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	FILE* pArchivo;
	Employee* pAuxEmployee;
	int retorno = -1;
	int i;
	int lenArrayListEmployee;

	if(path != NULL && pArrayListEmployee != NULL)
	{
		pArchivo = fopen(path,"w+b");
		if(pArchivo != NULL)
		{
			lenArrayListEmployee = ll_len(pArrayListEmployee);
			if(lenArrayListEmployee>0)
			{
				for(i=0; i<=lenArrayListEmployee; i++)
				{
					pAuxEmployee = (Employee*) ll_get(pArrayListEmployee,i);
					if(pAuxEmployee!=NULL)
					{
						fwrite(pAuxEmployee, sizeof(Employee), 1, pArchivo);
					}
				}
				retorno = 0;
			}
			fclose(pArchivo);
		}
	}
    return retorno;
}

/** \brief Borra los datos de la linkedlist de empleados.
 *
 * \param pArrayListEmployee LinkedList*:Puntero a la Linkedlist de empleados
 * \return int 0: Lista de empleados borrada correctamente
 * 		      -1: Error.
 */
int controller_exitWarning(LinkedList* pArrayListEmployee)
{
	int retorno = -1;

	if(pArrayListEmployee != NULL)
	{
		ll_deleteLinkedList(pArrayListEmployee);
		retorno = 0;
	}
	return retorno;
}

/** \brief Crea el archivo binario de empleados al iniciar el sistema.
 *
 */
void controller_createBinaryFile(void)
{
	LinkedList* listaEmpleadosAuxiliar = ll_newLinkedList();

	if(controller_loadFromText("data.csv",listaEmpleadosAuxiliar)==0)
	{
		if(controller_saveAsBinary("data.bin",listaEmpleadosAuxiliar)==0)
		{
			ll_deleteLinkedList(listaEmpleadosAuxiliar);
		}
	}
}
