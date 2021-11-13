#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Employee.h"
#include "utn.h"
#include "LinkedList.h"
#include "Validaciones.h"

/// \brief Revisa el archivo de información y recupera el primer ID disponible para dar de alta
/// \param IdDisponible:Arrays de char en donde se guardará el primer ID disponible
///
void IdGenerator(char *IdDisponible)
{
	FILE* pArchivoId;

	if(IdDisponible != NULL)
	{
		fflush(stdin);
		pArchivoId = fopen("RegistroIdDisponible.txt","r");

		if(pArchivoId != NULL)
		{
			do
			{
				fscanf(pArchivoId,"%s\n",IdDisponible);

			}while(feof(pArchivoId)==0);

			fclose(pArchivoId);
		}
	}
}

/// \brief Actualiza el archivo en el que se registra el nuevo ID disponible para asignar a un empleado
/// \param lastID: Ultimo ID utilizado al cargar un empleado.
/// \return int 0: ID actualizado correctamente.
///		       -1: Error.
///
int IdUpdate(int lastID)
{
	int retorno=-1;
	FILE* pArchivoId;

	pArchivoId = fopen("RegistroIdDisponible.txt","w");

	if(pArchivoId != NULL)
	{
		fprintf(pArchivoId,"%d",lastID+1);
		fclose(pArchivoId);
		retorno=0;
	}

	return retorno;
}

/// \brief Crea el espacio de memoria para almacenar la estructura empleado
/// \return pEmployee: Puntero al espacio de memoria en donde se creo la estructura empleado
///
Employee* employee_new(void)
{
	Employee* pEmployee= (Employee*) malloc(sizeof(Employee));

	return pEmployee;
}

/// \brief Crea el espacio de memoria para almacenar la estructura empleado y carga sus campos
/// \param idStr: ID del empleado
/// \param nombreStr: Nombre del empleado
/// \param horasTrabajadasStr:Horas trabajadas por el empleado
/// \param sueldoStr:Sueldo del empleado
/// \return pEmployee: Puntero al espacio de memoria en donde se creo la estructura empleado con los datos cargados

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
	Employee* pEmployee;
	int banderaSettersOk=0;

	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
	{
		pEmployee = employee_new();
		if(pEmployee!=NULL)
		{
			if(employee_setId(pEmployee,atoi(idStr))==0 &&
			   employee_setNombre(pEmployee,nombreStr)==0 &&
			   employee_setHorasTrabajadas(pEmployee,atoi(horasTrabajadasStr))==0 &&
			   employee_setSueldo(pEmployee,atoi(sueldoStr))==0)
			{
				IdUpdate(atoi(idStr));
				banderaSettersOk=1;
			}
			if(banderaSettersOk==0)
			{
				employee_delete(pEmployee);
				pEmployee = NULL;
			}
		}
	}
	return pEmployee;
}

/// \brief Borra la estructura empleado de la memoria
/// \param this:Puntero al espacio de memoria en donde se creo la estructura empleado
///
void employee_delete(Employee* this)
{
	if(this != NULL)
	{
		free(this);
	}

}

/// \brief: Carga el ID en la estructura empleados
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param id: ID del empleado
/// \return 0: ID cargado a la estructura correctamente.
///		   -1: Error.
int employee_setId(Employee* this,int id)
{
	int retorno = -1;
	if(this != NULL && id >= 0)
	{
		retorno = 0;
		this->id = id;
	}
	return retorno;
}

/// \brief Devuelve el ID del empleado cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param id: ID del empleado
/// \return 0: ID devuelto correctamente.
///		   -1: Error.
int employee_getId(Employee* this,int* id)
{
	int retorno = -1;
	if(this != NULL && id != NULL)
	{
		retorno = 0;
		*id = this->id;
	}
	return retorno;
}

/// \brief Carga el nombre en la estructura empleados
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param nombre: Nombre del empleado
/// \return 0: Nombre cargado a la estructura correctamente.
///		   -1: Error.
int employee_setNombre(Employee* this,char* nombre)
{
	int retorno = -1;

	if(this != NULL && nombre != NULL)
	{
		if(esNombre(nombre,NOMBRE_LEN))
		{
			strncpy(this->nombre,nombre,NOMBRE_LEN);
			retorno = 0;
		}
	}
	return retorno;
}


/// \brief: Devuelve el nombre del empleado cargado en la estructura
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param nombre: Nombre del empleado
/// \return 0: Nombre devuelto correctamente.
///		   -1: Error.
int employee_getNombre(Employee* this,char* nombre)
{
	int retorno = -1;
	if(this != NULL && nombre != NULL)
	{
		strncpy(nombre,this->nombre,NOMBRE_LEN);
		retorno = 0;
	}
	return retorno;
}

/// \brief: Carga la cantidad de horas trabajadas en la estructura empleados
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param horasTrabajadas: Horas trabajadas por el empleado
/// \return 0: Horas trabajadas cargadas correctamente.
///		   -1: Error.
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas >= 0)
	{
		this->horasTrabajadas = horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/// \brief: Devuelve la cantidad de horas trabajadas por el empleado cargado en la estructura
/// \param this:Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param horasTrabajadas: Horas trabajadas por el empleado
/// \return 0: Horas trabajadas devueltas correctamente.
///		   -1: Error.
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
	int retorno = -1;
	if(this != NULL && horasTrabajadas != NULL)
	{
		*horasTrabajadas = this->horasTrabajadas;
		retorno = 0;
	}
	return retorno;
}

/// \brief: Carga el sueldo en la estructura empleados
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param sueldo: Sueldo del empleado
/// \return 0: Sueldo cargado correctamente.
///		   -1: Error.
int employee_setSueldo(Employee* this,int sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo >= 0)
	{
		this->sueldo = sueldo;
		retorno = 0;
	}
	return retorno;
}

/// \brief Devuelve el sueldo del empleado cargado en la estructura
/// \param this:Puntero al espacio de memoria en donde se creo la estructura empleado
/// \param sueldo: Sueldo del empleado
/// \return 0: Sueldo devuelto correctamente.
///		   -1: Error.
int employee_getSueldo(Employee* this,int* sueldo)
{
	int retorno = -1;
	if(this != NULL && sueldo != NULL)
	{
		*sueldo = this->sueldo;
		retorno = 0;
	}
	return retorno;
}

/// \brief Busca el ID solicitado en la estructura de empleados
/// \param listEmployees:Puntero a la Linkedlist de empleados
/// \param id: Id del empleado
/// \return 0 o >0: Indice en el que se encuentra el ID solicitado
///		   -1: Error.
int employee_findById(LinkedList* listEmployees,int id)
{
	int retorno = -1;
	int i;
	int lenList;
	int auxId;
	Employee* pEmployee;

	if(listEmployees != NULL && id >= 0)
	{
		lenList=ll_len(listEmployees);
		for(i=0;i<=lenList;i++)
		{
			pEmployee=ll_get(listEmployees,i);
			if(employee_getId(pEmployee,&auxId) == 0 && auxId == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/// \brief: Modifica los campos de la estructura de un empleado determinado
/// \param listEmployees:Puntero a la Linkedlist de empleados
/// \param indiceAModificar: Indice de la linkedlist del empleado que se desea modificar
/// \return:0: Empleado modificado correctamente.
///		   -1: Error.

int modifyEmployee(LinkedList* listEmployees, int indiceAModificar)
{
	int retorno=-1;
	Employee* pEmployee;
	int opcionCampoAModificar;
	char auxNombreAModificar[NOMBRE_LEN];
	char auxHorasTrabajadasAModificar[HORASTRABAJADAS_LEN];
	char auxSueldoAModificar[SUELDO_LEN];

	if(listEmployees!= NULL && indiceAModificar >=0)
	{
		pEmployee=ll_get(listEmployees,indiceAModificar);

		do{
			printf("**************************************************\n");
			printf("¿Cual campo desea modificar?\n");
			printf("11) Nombre\n");
			printf("12) Horas trabajadas\n");
			printf("13) Sueldo\n");
			printf("14) Salir\n");
			printf("**************************************************\n");

			utn_getNumeroInt(&opcionCampoAModificar,"\nIngrese la opción","\nOpción inválida",11,14,3);

			switch(opcionCampoAModificar)
			{
				case 11:
					if(utn_getChar(auxNombreAModificar,"\nIngrese el nuevo nombre","\nNombre invalido\n",NOMBRE_LEN,3)==0)
					{
						employee_setNombre(pEmployee,auxNombreAModificar);
						retorno = 0;
					}
					break;
				case 12:
					if(utn_getNumeroEnteroPositivoComoChar(auxHorasTrabajadasAModificar,"\nIngrese la nueva cantidad de horas trabajadas","\nCantidad invalida\n",HORASTRABAJADAS_LEN,3)==0)
					{
						employee_setHorasTrabajadas(pEmployee,atoi(auxHorasTrabajadasAModificar));
						retorno = 0;
					}
					break;
				case 13:
					if(utn_getNumeroEnteroPositivoComoChar(auxSueldoAModificar,"\nIngrese el sueldo","\nSueldo invalido\n", SUELDO_LEN,3)==0)
					{
						employee_setSueldo(pEmployee,atoi(auxSueldoAModificar));
						retorno = 0;
					}
					break;
				case 14:
					break;
			}
		}while(opcionCampoAModificar!=14);
	}
	return retorno;
}

/// \brief Compara dos personas por nombre
/// \param pPersonA: Primera persona a comparar
/// \param pPersonB: Segunda persona a compara
/// \return 1: Nombre de la primera persona mayor a la segunda
///        -1: Nombre de la segunda persona menor a la segunda

int employee_compareByName(void* pPersonA,void* pPersonB)
{
	int retorno=0;
	Employee* pEmployeeOne;
	Employee* pEmployeeTwo;
	char auxNombreUnoAComparar[NOMBRE_LEN];
	char auxNombreDosAComparar[NOMBRE_LEN];

	if(pPersonA != NULL && pPersonB != NULL)
	{
		pEmployeeOne=(Employee*) pPersonA;
		pEmployeeTwo=(Employee*) pPersonB;

		if(employee_getNombre(pEmployeeOne,auxNombreUnoAComparar)==0 &&
		   employee_getNombre(pEmployeeTwo,auxNombreDosAComparar)==0 )
		{
			if(strncmp(auxNombreUnoAComparar,auxNombreDosAComparar,NOMBRE_LEN)>0)
			{
				retorno=1;
			}
			else
			{
				if(strncmp(auxNombreUnoAComparar,auxNombreDosAComparar,NOMBRE_LEN)<0)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/// \brief Compara dos personas por ID
/// \param pPersonA: Primera persona a comparar
/// \param pPersonB: Segunda persona a compara
/// \return 1: ID de la primera persona mayor a la segunda
///        -1: ID de la segunda persona menor a la segunda
int employee_compareById(void* pPersonA,void* pPersonB)
{
	int retorno=0;
	Employee* pEmployeeOne;
	Employee* pEmployeeTwo;
	int auxIdUnoAComparar;
	int auxIdDosAComparar;

	if(pPersonA != NULL && pPersonB != NULL)
	{
		pEmployeeOne=(Employee*) pPersonA;
		pEmployeeTwo=(Employee*) pPersonB;

		if(employee_getId(pEmployeeOne,&auxIdUnoAComparar)==0 &&
		   employee_getId(pEmployeeTwo,&auxIdDosAComparar)==0 )
		{
			if(auxIdUnoAComparar > auxIdDosAComparar)
			{
				retorno=1;
			}
			else
			{
				if(auxIdUnoAComparar < auxIdDosAComparar)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/// \brief Compara dos personas por salario
/// \param pPersonA: Primera persona a comparar
/// \param pPersonB: Segunda persona a compara
/// \return 1: Salario de la primera persona mayor a la segunda
///        -1: Salario de la segunda persona menor a la segunda
int employee_compareBySalary(void* pPersonA,void* pPersonB)
{
	int retorno=0;
	Employee* pEmployeeOne;
	Employee* pEmployeeTwo;
	int auxSalarioUnoAComparar;
	int auxSalarioDosAComparar;

	if(pPersonA != NULL && pPersonB != NULL)
	{
		pEmployeeOne=(Employee*) pPersonA;
		pEmployeeTwo=(Employee*) pPersonB;

		if(employee_getSueldo(pEmployeeOne,&auxSalarioUnoAComparar)==0 &&
		   employee_getSueldo(pEmployeeTwo,&auxSalarioDosAComparar)==0 )
		{
			if(auxSalarioUnoAComparar > auxSalarioDosAComparar)
			{
				retorno=1;
			}
			else
			{
				if(auxSalarioUnoAComparar < auxSalarioDosAComparar)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/// \brief Compara dos personas por horas trabajadas
/// \param pPersonA: Primera persona a comparar
/// \param pPersonB: Segunda persona a compara
/// \return 1: Horas trabajadas por la primera persona mayor a la segunda
///        -1: Horas trabajadas por la segunda persona menor a la segunda
int employee_compareByHoursWorked(void* pPersonA,void* pPersonB)
{
	int retorno=0;
	Employee* pEmployeeOne;
	Employee* pEmployeeTwo;
	int auxHorasTUnoAComparar;
	int auxHorasTDosAComparar;

	if(pPersonA != NULL && pPersonB != NULL)
	{
		pEmployeeOne=(Employee*) pPersonA;
		pEmployeeTwo=(Employee*) pPersonB;

		if(employee_getHorasTrabajadas(pEmployeeOne,&auxHorasTUnoAComparar)==0 &&
		   employee_getHorasTrabajadas(pEmployeeTwo,&auxHorasTDosAComparar)==0 )
		{
			if(auxHorasTUnoAComparar > auxHorasTDosAComparar)
			{
				retorno=1;
			}
			else
			{
				if(auxHorasTUnoAComparar < auxHorasTDosAComparar)
				{
					retorno=-1;
				}
			}
		}
	}
	return retorno;
}

/// \brief Imprime todos los datos de un empleado
/// \param this: Puntero al espacio de memoria en donde se creo la estructura empleado
/// \return 0: Impresión realizada correctamente.
///		   -1: Error.

int employee_printEmployee(Employee* this)
{
	int retorno = -1;
	int auxId;
	char auxNombre[NOMBRE_LEN];
	int auxHorasTrabajadas;
	int auxSueldo;

	if(this != NULL)
	{
		if(employee_getId(this,&auxId)==0 &&
		   employee_getNombre(this,auxNombre)==0 &&
		   employee_getHorasTrabajadas(this,&auxHorasTrabajadas)==0 &&
		   employee_getSueldo(this,&auxSueldo)==0)
		{
			printf("%d - %s - %d - %d\n", auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
			retorno = 0;
		}
	}
	return retorno;
}
