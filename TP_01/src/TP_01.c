/*
 ============================================================================
 Name        : TP1.c
 Author      : Marcos Zalazar
 Version     :
 Copyright   : Your copyright notice
 Description : Hacer una calculadora. Para ello el programa iniciará y contará con un menú de opciones:
				1. Ingresar 1er operando (A=x)
				2. Ingresar 2do operando (B=y)
				3. Calcular todas las operaciones
				a) Calcular la suma (A+B)
				b) Calcular la resta (A-B)
				c) Calcular la division (A/B)
				d) Calcular la multiplicacion (A*B)
				e) Calcular el factorial (A!)
				4. Informar resultados
				a) “El resultado de A+B es: r”
				b) “El resultado de A-B es: r”
				c) “El resultado de A/B es: r” o “No es posible dividir por cero”
				d) “El resultado de A*B es: r”
				e) “El factorial de A es: r1 y El factorial de B es: r2”
				5. Salir
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn_biblioteca.h"


int main(void)
{

	int opcion;
	float numero1;
	float numero2;
	float resultadoSuma;
	float resultadoResta;
	float resultadoMultiplicacion;
	float resultadoDivision;
	int resultadoPrimerFactorial;
	int resultadoSegundoFactorial;
	int banderaPrimerOperandoCargado;
	int banderaSegundoperandoCargado;
	int banderaOperacionesRealizadas;
	int respuestaDivision;
	int respuestaFactorialUno;
	int respuestaFactorialDos;

	numero1=0;
	numero2=0;
	banderaPrimerOperandoCargado=0;
	banderaSegundoperandoCargado=0;
	banderaOperacionesRealizadas=0;

	setbuf(stdout, NULL);

	do{
		printf("*********************************************\n");
		printf("Bienvenido a la calculadora de la UTN\n");
		printf("1) Ingrese el primer operando: %.2f\n",numero1);
		printf("2) Ingrese el segundo operando: %.2f\n",numero2);
		printf("3) Calcular todas las operaciones\n");
		printf("4) Informar los resultados\n");
		printf("5) Salir\n");
		printf("*********************************************\n");
		scanf("%d", &opcion);

		switch(opcion){
			case 1:
				utn_getNumeroFloat(&numero1, "Ingrese el primer operando, por favor", "Número inválido");
				banderaPrimerOperandoCargado=1;
				break;
			case 2:
				utn_getNumeroFloat(&numero2, "Ingrese el segundo operando, por favor", "Número inválido");
				banderaSegundoperandoCargado=1;
				break;
			case 3:
				if(banderaPrimerOperandoCargado==1 && banderaSegundoperandoCargado==1)
				{
					resultadoSuma=sumar(numero1,numero2);
					resultadoResta=restar(numero1,numero2);
					respuestaDivision=dividir(numero1, numero2,&resultadoDivision);
					resultadoMultiplicacion=multiplicar(numero1,numero2);
					respuestaFactorialUno=calcularFactorial(numero1,&resultadoPrimerFactorial);
					respuestaFactorialDos=calcularFactorial(numero2,&resultadoSegundoFactorial);
				}
				else
				{
					printf("Para realizar esta operación, primero debe cargar los dos operandos\n");
				}
				banderaOperacionesRealizadas=1;
				break;
			case 4:
				if(banderaOperacionesRealizadas==1)
				{
					printf("#############################################\n");
					printf("El resultado de la suma es: %.2f\n",resultadoSuma);
					printf("El resultado de resta es: %.2f \n",resultadoResta);
					if (respuestaDivision==0)
					{
						printf("El resultado de la división es: %.2f \n",resultadoDivision);
					}
					else
					{
						printf("No es posible dividir por cero\n");
					}
					printf("El resultado de la multiplicación es: %.2f \n",resultadoMultiplicacion);
					if (respuestaFactorialUno==0)
					{
						printf("El factorial del primer operando es: %d \n",resultadoPrimerFactorial);
					}
					else
					{
						printf("No se puede calcular el factorial de números negativos\n");
					}
					if (respuestaFactorialDos==0)
					{
					printf("El factorial del segundo operando es: %d \n",resultadoSegundoFactorial);
					}
					else
					{
						printf("No se puede calcular el factorial de números negativos");
					}
					printf("#############################################\n\n");
				}
				else
				{
					printf("No hay resultados a informar. Primero debe cargar los dos operandos y la operación que desea realizar\n");
				}
				break;
			case 5:
				printf("¡Gracias por utilizar la calculadora de la UTN!\n\n");
				EXIT_SUCCESS;
				break;
			default:
				printf("Opción inválida. Eliga las opciones 1,2,3,4 o 5, por favor\n");
				break;
		}

	}while(opcion!=5);

	return EXIT_SUCCESS;
}


