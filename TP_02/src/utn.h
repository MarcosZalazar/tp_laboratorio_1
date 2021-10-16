/*
 * utn.h
 *
 *  Created on: 30 sep. 2021
 *      Author: Marcos
 */

#ifndef UTN_H_
#define UTN_H_

int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, int longitud, int reintentos);

int utn_getDescripcion(char* pResultado,char* mensaje, char* mensajeError, int longitud, int reintentos);
int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);

#endif /* UTN_H_ */
