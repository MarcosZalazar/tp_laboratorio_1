/*
 * utn_biblioteca.c
 *
 *  Created on: 23 sep. 2021
 *      Author: Marcos
 */

#include <stdio.h>
#include <stdlib.h>

int utn_getNumeroFloat(float* pNumeroIngresado, char* mensaje, char* mensajeError)
{
	float bufferInt;
	int retorno=-1;

	if(pNumeroIngresado != NULL && mensaje != NULL && mensajeError != NULL)
	{
		printf("%s",mensaje);
		scanf("%f", &bufferInt);
		*pNumeroIngresado=bufferInt;
		retorno = 0;
	}
	return retorno;
}

float sumar(float num1, float num2){

	float retorno;

	retorno=num1+num2;

	return retorno;
}

float restar(float num1, float num2){

	float retorno;

	retorno=num1-num2;

	return retorno;
}

int dividir(float num1, float num2, float* pResultadoDivision){

	int estadoDivision=-1;

	if(pResultadoDivision!=NULL && num2!=0)
	{
		*pResultadoDivision=num1/num2;
		estadoDivision=0;
	}
	return estadoDivision;
}

float multiplicar(float num1, float num2){

	float retorno;

	retorno=num1*num2;

	return retorno;
}


int calcularFactorial(float num1, int* pResultadoFactorial){

	int estadoFactorial=-1;
	int factorialParcial=1;
	int i;

	num1=(int)num1;

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
	return estadoFactorial;
}
