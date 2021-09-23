/*
 * utn_biblioteca.h
 *
 *  Created on: 23 sep. 2021
 *      Author: Marcos
 */

#ifndef UTN_BIBLIOTECA_H_
#define UTN_BIBLIOTECA_H_


int utn_getNumeroFloat(float* pNumeroIngresado, char* mensaje, char* mensajeError);
float sumar(float num1, float num2);
float restar(float num1, float num2);
float multiplicar(float num1, float num2);
int dividir(float num1, float num2, float* pResultadoDivision);
int calcularFactorial(float num1, int* pResultadoFactorial);

#endif /* UTN_BIBLIOTECA_H_ */
