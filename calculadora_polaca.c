#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "strutil.h"
#include "pila.h"

//para la pila
void destruir_datos(void*);

//operaciones
bool sumar(pila_t *);
bool restar(pila_t *);
bool multiplicar(pila_t *);
bool log_c(pila_t *);
bool pot(pila_t *);

//ejecuta operaciones
void calcular(pila_t *pila, char *op, bool *ok);

//wrapper destruir pila
void _free_pila(pila_t *pila);

//main
void calculadora_polaca_inversa(char*);

void calculadora_polaca_inversa(char *comandos){
	
	pila_t *pila = pila_crear();
	
	bool ok = true;
	
	char **variables = split( comandos,' ');
	
	for (int i = 0; variables[i] ; i++ ){
	       	int *numero = malloc(sizeof(int));
		*numero = atoi(variables[i]);
		
		if (*numero) pila_apilar(pila,numero);
		else{
			if ( strcmp(variables[i],"0")==0) pila_apilar(pila,numero);
			else{
				free(numero);
				calcular(pila,variables[i],&ok);
				if (!ok) break;
			}
		}
	}
			

	if (!ok) fprintf(stdout,"%s\n","ERROR");
	else{
		int *rta = pila_desapilar(pila);

		if ( pila_esta_vacia(pila)) fprintf(stdout,"%d\n",*rta);
		else fprintf(stdout,"%s","ERROR\n");
		
		free(rta);	
	}

	free_strv(variables);
	_free_pila(pila);
}

void calcular(pila_t *pila, char *op, bool *ok){
	
	if ( strcmp(op,"+") == 0) *ok = sumar(pila);
	
	else if ( strcmp(op,"-") == 0) *ok = restar(pila);

	else if ( strcmp(op,"*") == 0) *ok = multiplicar(pila);

	else if ( strcmp(op,"^") == 0) *ok = pot(pila);

	else if ( strcmp(op,"log") == 0) *ok = log_c(pila);

	else *ok = false;
}

void destruir_datos(void *dato){
	int *d = dato;
	free(d);
}

void _free_pila(pila_t *pila){
	while( !pila_esta_vacia(pila)){
		free(pila_desapilar(pila));
	}
	pila_destruir(pila);
}

bool log_c(pila_t *pila){
	return false;
}

bool pot(pila_t *pila){
	return false;
}

bool sumar(pila_t *pila){
	int error = 2;
	int *suma = malloc(sizeof(int));
	*suma = 0;

	while ( !pila_esta_vacia(pila) && error > 0 ){
		int *numero = pila_desapilar(pila);
		*suma += *numero;
		free(numero);
		error--;
	}
	
	pila_apilar(pila,suma);

	return error == 0;
}

bool restar(pila_t *pila){
	int error = 1;
	int *resta = malloc(sizeof(int));
	*resta = 0;
	if ( !pila_esta_vacia (pila)){ 
		int *n = pila_desapilar(pila);
		*resta += *n;
		free(n);
	}

	while ( !pila_esta_vacia(pila) && error > 0 ){
		int *numero = pila_desapilar(pila);
		*resta -= *numero;
		free(numero);
		error--;
	}
	
	pila_apilar(pila,resta);

	return error == 0;
}

bool multiplicar(pila_t *pila){
	int error = 1;
	int *multiplicacion = malloc(sizeof(int));
	*multiplicacion = 0;
	if ( !pila_esta_vacia (pila)){ 
		int *n = pila_desapilar(pila);
		*multiplicacion += *n;
		free(n);
	}

	while ( !pila_esta_vacia(pila) && error > 0 ){
		int *numero = pila_desapilar(pila);
		*multiplicacion *= *numero;
		free(numero);
		error--;
	}
	
	pila_apilar(pila,multiplicacion);

	return error == 0;
}



int main(){
	size_t cap = 0;
	char *linea = NULL;
	
	while( getline ( &linea, &cap, stdin ) > 0 ){
		char *linea_actual = linea;
		//elimino /n
		linea_actual[strlen(linea_actual)-1] = '\0';
		
		calculadora_polaca_inversa(linea_actual);
	} 
	
	free(linea);

	return 0;
}

