
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Validaciones.h"

static int getInt(int* pResultado);
static int getFloat(float* pResultado);
static int getNombre(char* pResultado, int longitud);
static int getString(char* cadena, int longitud);
static int getDescripcion(char* pResultado, int longitud);
static int getDni(char* pResultado, int longitud);
static int getNumeroEnteroPositivoComoChar(char* pResultado, int longitud);

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
/// \return Retorna 0 (EXITO) si se obtiene un DNI y -1 (ERROR) si no

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

/// \brief Solicita un número entero positivo al usuario, luego de verificarlo devuelve el resultado del tipo Char
/// \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
/// \param longitud Es la longitud del array resultado
/// \param mensaje Es el mensaje a ser mostrado
/// \param mensajeError Es el mensaje de Error a ser mostrado
/// \param reintentos Cantidad de reintentos
/// \return Retorna 0 si se obtuvo un numero entero positivo válido y -1 si no

int utn_getNumeroEnteroPositivoComoChar(char* pResultado,char* mensaje, char* mensajeError, int longitud, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && longitud >=0 && reintentos >=0)
	{
		while(reintentos>=0)
		{
			reintentos--;
			printf("%s",mensaje);
			if(getNumeroEnteroPositivoComoChar(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
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

/// \brief Obtiene un string valido como numero entero positivo
/// \param pResultado Puntero al espacio de memoria donde se dejará el resultado de la funcion
/// \param longitud Longitud de la cadena
/// \return Retorna 0 (EXITO) si se obtiene un numero numero entero positivo y -1 (ERROR) si no

static int getNumeroEnteroPositivoComoChar(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL && longitud >=0)
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
