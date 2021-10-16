/*
 * utn.c
 *
 *  Created on: 30 sep. 2021
 *      Author: Marcos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int getInt(int* pResultado);
static int getFloat(float* pResultado);
static int getNombre(char* pResultado, int longitud);
static int getString(char* cadena, int longitud);
static int esNumerica(char* cadena, int limite);
static int esFlotante(char* cadena);
static int esNombre(char* cadena,int longitud);
static int getDescripcion(char* pResultado, int longitud);
static int esDescripcion(char* cadena,int longitud);
static int getDni(char* pResultado, int longitud);

/// \brief Solicita un numero INT al usuario, luego de verificarlo devuelve el resultado
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param minimo Es el numero mínimo a ser aceptado
/// \param maximo Es el minimo máximo a ser aceptado
/// \param reintentos Es el número de reintentos que tendrá el usuario
/// \return Retorna 0 si se obtuvo el numero y -1 si no

int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int bufferInt;
	int retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo<maximo && reintentos >=0)
	{
		while(reintentos>=0)
		{
			printf("%s",mensaje);
			if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
			{
					*pResultado = bufferInt;
					retorno = 0;
					break;
			}
			printf("%s",mensajeError);
			reintentos--;
		}
	}
	return retorno;
}

/// \brief Solicita un numero FLOAT al usuario, luego de verificarlo devuelve el resultado
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param minimo Es el numero mínimo a ser aceptado
/// \param maximo Es el minimo máximo a ser aceptado
/// \param reintentos Es el número de reintentos que tendrá el usuario
/// \return Retorna 0 si se obtuvo el numero y -1 si no lo obtuvo

int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int retorno=-1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo<maximo && reintentos >=0)
	{
		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getFloat(&bufferFloat) == 0)
			{
				if(bufferFloat >= minimo && bufferFloat <= maximo)
				{
					*pResultado = bufferFloat;
					retorno = 0;
					break;
				}
			}
			printf("%s",mensajeError);
		}
	}
	return retorno;
}

/// \brief Solicita un char al usuario, luego de verificarlo devuelve el resultado
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param minimo Es el numero mínimo a ser aceptado
/// \param maximo Es el minimo máximo a ser aceptado
/// \param reintentos Es el número de reintentos que tendrá el usuario
/// \return Retorna 0 si se obtuvo el numero y -1 no lo obtuvo
/// TAMBIEN LLAMADA utn_getNombre

int utn_getChar(char* pResultado, char* mensaje, char* mensajeError, int longitud, int reintentos)
{
	char bufferString[4096];
	int retorno=-1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && longitud>=0 && reintentos >=0 )
	{
		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getNombre(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
			{
				strncpy(pResultado,bufferString,longitud);
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
		}
	}
	return retorno;
}

/// \brief  Verifica si la cadena ingresada es numérica
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no.

static int getInt(int* pResultado)
{
	int retorno=-1;
	char bufferString[64];

	if(pResultado != NULL && getString(bufferString,sizeof(bufferString)) == 0 && esNumerica(bufferString,sizeof(bufferString)))
	{
			*pResultado = atoi(bufferString);
			retorno = 0;
	}
	return retorno;
}

/// \brief  Verifica si la cadena ingresada es flotante
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no.

static int getFloat(float* pResultado)
{
	int retorno=-1;
	char bufferString[64];

	if(pResultado != NULL)
	{
		if(getString(bufferString,sizeof(bufferString))==0 && esFlotante(bufferString))
		{
			*pResultado = atof(bufferString);
			retorno = 0;
		}
	}
	return retorno;
}


/// \brief Obtiene un string válido como nombre
/// \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// \param longitud Longitud de la cadena recibida
/// \return Retorna 0 (EXITO) si se pudo copiar la cadena y -1 (ERROR) si no

static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}



/// \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
///        un máximo de 'longitud - 1' caracteres.
/// \param cadena Puntero al espacio de memoria donde se copiará la cadena obtenida
/// \param longitud Define el tamaño de cadena
/// \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no.

static int getString(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);

		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}

/// \brief Verifica si la cadena ingresada es numerica
/// \param cadena Cadena de caracteres a ser analizada
/// \return Retorna 1 (vardadero) si la cadena es numerica, 0 (falso) si no lo es y -1 en caso de error

static int esNumerica(char* cadena, int limite)
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

static int esFlotante(char* cadena)
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

static int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/// \brief Solicita una descripcion al usuario, luego de verificarlo devuelve el resultado
/// \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// \param longitud Es la longitud del array resultado
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param reintentos Cantidad de reintentos
/// \return Retorna 0 si se obtuvo el numero flotante y -1 si no

int utn_getDescripcion(char* pResultado,char* mensaje, char* mensajeError, int longitud, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && longitud>=0 && reintentos >=0)
	{
		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
			{
				strncpy(pResultado,bufferString,longitud);
				retorno = 0;
				break;
			}
			printf("%s",mensajeError);
		}
	}
	return retorno;
}


/// \brief Obtiene un string válido como descripcion
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la función
/// \param longitud Longitud de la cadena recibida
/// \return Retorna 0 (EXITO) si se pudo copiar la cadena y -1 (ERROR) si no

static int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

/// \brief Verifica si la cadena ingresada es una descripcion valida, es decir, si la cadena ingresada
///        posee caracteres alfanúmericos, puntos o espacios.
/// \param cadena Cadena de caracteres a ser analizada
/// \param longitud Longitud de la cadena
/// \return Retorna 1 (verdadero) si la cadena es valida y 0 (falso) si no lo es

static int esDescripcion(char* cadena,int longitud)
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


/// \brief Solicita un DNI al usuario, luego de verificarlo devuelve el resultado
/// \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// \param longitud Es la longitud del array resultado
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param reintentos Cantidad de reintentos
/// \return Retorna 0 si se obtuvo un DNI válido y -1 si no

int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;

	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDni(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}


/// \brief Obtiene un string valido como DNI
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la funcion
/// \param longitud Longitud de la cadena
/// \return Retorna 0 (EXITO) si se obtiene un numero flotante y -1 (ERROR) si no

static int getDni(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNumerica(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}
