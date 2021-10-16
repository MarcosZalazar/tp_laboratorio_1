/*
 * Empleados.h
 *
 *  Created on: 1 oct. 2021
 *      Author: Marcos
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

#define NOMBRE_LEN 51
#define APELLIDO_LEN 51

typedef struct
{
	int id;
	char nombre[NOMBRE_LEN];
	char apellido [APELLIDO_LEN];
	float salario;
	int sector;
	int isEmpty;
}Empleado;

int initEmployees(Empleado* list, int len);
int addEmployee(Empleado* list, int len, int id, char name [], char lastName[], float salary, int sector);
int findEmployeeById(Empleado* list, int len, int id);
int removeEmployee(Empleado* list, int len, int id);
int idGenerator(void);
int modifyEmployee(Empleado* list, int len, int id);
int sortEmployee(Empleado* list, int len, int order);
int printEmployee(Empleado* list, int lenght);
int getEmptyIndex(Empleado* list, int len);
int infoSalaries(Empleado* list, int len,float* pTotalSalaries, float* pAverageSalary,int* employeesAboveAverageSalary);

#endif /* ARRAYEMPLOYEES_H_ */
