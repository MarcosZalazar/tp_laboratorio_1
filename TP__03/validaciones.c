#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Validaciones.h"


/// \brief Verifica si la cadena ingresada es numerica
/// \param cadena Cadena de caracteres a ser analizada
/// \return Retorna 1 (verdadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error

int esNumerica(char* cadena, int limite)
{
	int retorno = -1;
	int i;

	if(cadena != NULL && limite > 0)
	{
		retorno=1;
		for(i=0;i<limite && cadena[i]!='\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-' ))
			{
				continue;
			}
			if(cadena[i] > '9' || cadena[i] < '0')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/// \brief Verifica si la cadena ingresada es flotante
/// \param cadena Cadena de caracteres a ser analizada
/// \return Retorna 1 (verdadero) si la cadena es flotante y 0 (falso) si no lo es

int esFlotante(char* cadena)
{
	int i=0;
	int retorno = 1;
	int contadorPuntos=0;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i=0 ; cadena[i] != '\0'; i++)
		{
			if(i==0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

/// \brief Verifica si la cadena ingresada es un nombre valido
/// \param cadena Cadena de caracteres a ser analizada
/// \param longitud Longitud de la cadena recibida
/// \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es.

int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/// \brief Verifica si la cadena ingresada es una descripcion valida, es decir, si la cadena ingresada
///        posee caracteres alfanúmericos, puntos o espacios.
/// \param cadena Cadena de caracteres a ser analizada
/// \param longitud Longitud de la cadena
/// \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es

int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
