/*
 * utn_biblioteca.c
 *
 *  Created on: 23 sep. 2021
 *      Author: Marcos
 */

#include <stdio.h>
#include <stdlib.h>

/// \fn int utn_getNumeroFloat(float*, char*, char*)
/// \brief Solicita un número del tipo float, y valida que este sea correcto.
/// \param pNumeroIngresado: Puntero al espacio de memoria donde se guardará el número ingresado
/// \param mensaje: Mensaje con el que se solicita el ingreso de un número.
/// \param mensajeError: Mensaje de error con el que se indica que no se ha ingresado un número válido
/// \return  0: Número ingresado correctamente.
/// 		-1: Error.
/// 		-2: Error, indicando que el número es inválido

int utn_getNumeroFloat(float* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	float bufferFloat;
	int retorno=-1;
	int salidaScanf;

	if(pNumeroIngresado != NULL && mensaje != NULL && mensajeError != NULL)
	{
		printf("%s",mensaje);
		salidaScanf=scanf("%f", &bufferFloat);
		if(salidaScanf>0)
		{
			*pNumeroIngresado=bufferFloat;
			retorno = 0;
		}
		else
		{
			retorno = -2;
			printf("%s\n",mensajeError);
		}
	}
	return retorno;
}

/// \fn float sumar(float, float)
/// \brief Suma dos números
/// \param num1: Primer operando ingresado por el usuario
/// \param num2: Segundo operando ingresado por el usuario
/// \return Devuelve la variable "retorno", que contiene el resultado de la suma

float sumar(float num1, float num2)
{

	float retorno;

	retorno=num1+num2;

	return retorno;
}

/// \fn float restar(float, float)
/// \brief Resta dos números
/// \param num1: Primer operando ingresado por el usuario
/// \param num2: Segundo operando ingresado por el usuario
/// \return Devuelve la variable "retorno", que contiene el resultado de la resta

float restar(float num1, float num2)
{

	float retorno;

	retorno=num1-num2;

	return retorno;
}

/// \fn int dividir(float, float, float*)
/// \brief Divide dos números siempre que el segundo número sea distinto de cero
/// \param num1: Primer operando ingresado por el usuario
/// \param num2: Segundo operando ingresado por el usuario
/// \param pResultadoDivision: Puntero al espacio de memoria donde se guardará el resultado de la division
/// \return Devuelve la variable "estadoDivision", que indica si la división se pudo realizar.
/// 		0: División realizada.
/// 	   -1: Error: No se pudo realizar la división

int dividir(float num1, float num2, float* pResultadoDivision)
{

	int estadoDivision=-1;

	if(pResultadoDivision!=NULL && num2!=0)
	{
		*pResultadoDivision=num1/num2;
		estadoDivision=0;
	}
	return estadoDivision;
}

/// \fn float multiplicar(float, float)
/// \brief Multiplica dos números
/// \param num1: Primer operando ingresado por el usuario
/// \param num2: Segundo operando ingresado por el usuario
/// \return Devuelve la variable "retorno", que contiene el resultado de la multiplicación

float multiplicar(float num1, float num2)
{
	float retorno;

	retorno=num1*num2;

	return retorno;
}

/// \fn int calcularFactorial(float, int*)
/// \brief Calcula el factorial de un número ingresado, siempre que sea entero y no negativo
/// \param num1: Operando ingresado por el usuario
/// \param pResultadoFactorial: Puntero al espacio de memoria donde se guardará el resultado del factorial
/// \return Devuelve la variable "estadoFactorial", que indica si se pudo calcular el factorial del número.
/// 		0: Factorial calculado.
/// 	   -1: Error: No se pudo calcular el factorial

int calcularFactorial(float num1, int* pResultadoFactorial)
{
	int estadoFactorial;
	int factorialParcial=1;
	int auxEntero;
	int i;

	auxEntero=(int)num1;

	if(pResultadoFactorial!=NULL)
	{
		if (num1-auxEntero)
		{
			estadoFactorial=-1;
		}
		else
		{
			if (num1>0)
			{
				for(i=num1;i>0;i--)
				{
					factorialParcial=factorialParcial*i;
				}
				*pResultadoFactorial=factorialParcial;
				estadoFactorial=0;
			}
			else
			{
				if(num1==0)
				{
				*pResultadoFactorial=1;
				estadoFactorial=0;
				}
			}
		}
	}
	return estadoFactorial;
}
