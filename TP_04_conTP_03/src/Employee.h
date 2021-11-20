#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED

#define ID_LEN 128
#define NOMBRE_LEN 128
#define HORASTRABAJADAS_LEN 128
#define SUELDO_LEN 128

#include "LinkedList.h"

typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    int horasTrabajadas;
    int sueldo;
}Employee;

void IdGenerator(char *IdDisponible);
int IdUpdate(int lastID);
Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr);
void employee_delete(Employee* this);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);
int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);
int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

int employee_findById(LinkedList* listEmployees,int id);
int modifyEmployee(LinkedList* listEmployees, int indiceAModificar);
int employee_compareByName(void* pPersonA,void* pPersonB);
int employee_compareById(void* pPersonA,void* pPersonB);
int employee_compareBySalary(void* pPersonA,void* pPersonB);
int employee_compareByHoursWorked(void* pPersonA,void* pPersonB);
int employee_printEmployee(Employee* this);

#endif // employee_H_INCLUDED
