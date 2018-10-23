#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "strutil.h"
#include "pila.h"

//operaciones
bool sumar(pila_t *); //ok
bool restar(pila_t *) //ok
bool multiplicar(pila_t *); //ok
bool log_c(pila_t *); //ok
bool pot(pila_t *);
bool dividir(pila_t *);//ok
bool raiz(pila_t *); //ok
bool ternario (pila_t *); //ok

//wrapper
int _raiz(int,int,int); //ok
int _log_c(int,int); //ok

//ejecuta operaciones
void calcular(pila_t *pila, char *op, bool *ok); //ok

//wrapper destruir pila
void _free_pila(pila_t *pila); //ok


//main
void calculadora_polaca_inversa(char*); //ok

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

bool restar(pila_t *pila){
	if ( pila_esta_vacia(pila)) return false;

	int *v = pila_desapilar(pila);

	if ( pila_esta_vacia(pila)) {
		free(v);
		return false;
	}

	int *v2 = pila_desapilar(pila);

	int *res = malloc(sizeof(int));

	*res = *v - *v2;

	pila_apilar(pila, res);

	free(v);
	free(v2);

	return true;
}

bool sumar(pila_t *pila){
	if (pila_esta_vacia(pila)) return false;

	int *v = pila_desapilar(pila);

	if (pila_esta_vacia(pila)){
		free(v);
		return false;
	}
	int *v2 = (int*)pila_desapilar(pila);

	int *suma = malloc(sizeof(int));

	*suma = *v + *v2;

	pila_apilar(pila, suma);

	free(v);
	free(v2);

	return true;
}

bool dividir(pila_t *pila){
	if ( pila_esta_vacia(pila)) return false;

	int *v = pila_desapilar(pila);

	if ( pila_esta_vacia(pila)){
		free(v);
		return false;
	}

	int *v2 = pila_desapilar(pila);

	if ( *v2 == 0 ) {
		free(v2);
		free(v);
		return false;
	}

	int *divicion = malloc(sizeof(int));

	*divicion = *v / *v2;

	pila_apilar(pila, divicion);

	free(v2);
	free(v);

	return true;
}

bool ternario(pila_t *pila){
	if ( pila_esta_vacia(pila)) return false;

	int *condicion = pila_desapilar(pila);

	if ( pila_esta_vacia(pila) ) {
		free(condicion);
		return false;
	}

	int *verdadero = pila_desapilar(pila);

	if ( pila_esta_vacia(pila)){
		free(condicion);
		free(verdadero);
		return false;
	}

	int *falso = pila_desapilar(pila);

	pila_apilar(pila, *condicion ? verdadero : falso );
	
	//borro el que no guarde
	free( *condicion ? falso : verdadero );

	free( condicion );

	return true;

}

void calcular(pila_t *pila, char *op, bool *ok){
	
	//la funcion suma contempla la resta
	if ( strcmp(op,"+") == 0) *ok = sumar(pila);

	else if ( strcmp(op,"-") == 0) *ok = restar(pila);

	else if ( strcmp(op,"*") == 0) *ok = multiplicar(pila);

	else if ( strcmp(op,"^") == 0) *ok = pot(pila);

	else if ( strcmp(op,"log") == 0) *ok = log_c(pila);

	else if ( strcmp(op,"/") == 0 ) *ok = dividir(pila);
	
	else if ( strcmp(op,"?") == 0 ) *ok = ternario(pila);

	else if ( strcmp(op,"sqrt") == 0) *ok = raiz(pila);

	else *ok = false;
}

bool raiz(pila_t *pila){

	if (pila_esta_vacia(pila)) return false;

	int *numero = pila_desapilar(pila);

	if (*numero <0 ){
		free(numero);
		return false;
	}

	int *r = malloc(sizeof(int));

	*r = _raiz(*numero,0,*numero);

	pila_apilar(pila,r);

	free(numero);

	return true;

}

int _raiz(int numero, int i , int f){
	if ( i > f ) return f;

	int medio = (i + f) / 2;

	if ( ( medio * medio ) == numero ) return medio;

	if ( ( medio * medio ) > numero ) return _raiz(numero, i, medio - 1 );

	return _raiz(numero, medio + 1, f );
}

void _free_pila(pila_t *pila){
	while( !pila_esta_vacia(pila)){
		free(pila_desapilar(pila));
	}
	pila_destruir(pila);
}

bool log_c(pila_t *pila){
	if ( pila_esta_vacia(pila) ) return false;
	
	int *argumento = pila_desapilar(pila);

	if ( pila_esta_vacia(pila) ){
		free(argumento);
		return false;
	}

	int *base = pila_desapilar(pila);

	if ( *base <= 1 ){
		free(argumento);
		free(base);
		return false;
	}
	
	int *logaritmo = malloc(sizeof(int));
	
	*logaritmo = _log_c(*base,*argumento);
	
	pila_apilar(pila, logaritmo);

	free(base);
	free(argumento);

	return true;
}

int _log_c(int base, int argumento){
	
	int medio = argumento / base;
	
	if ( medio == base ) return medio;

	if ( medio > base ) return 2 + _log_c(base, argumento/(base*base));

	if ( medio > 0 && medio < base ) return 1;

	return 0;
}

bool pot(pila_t *pila){
	if ( pila_esta_vacia(pila)) return false;

	return false;
}

bool multiplicar(pila_t *pila){

	if ( pila_esta_vacia(pila) ) return false;

	int *v = pila_desapilar(pila);

	if ( pila_esta_vacia(pila) ){
		free(v);
		return false;
	}

	int *v2 = pila_desapilar(pila);

	int *multiplicacion = malloc(sizeof(int));

	*multiplicacion = *v * *v2;

	pila_apilar(pila, multiplicacion);

	free(v);
	free(v2);

	return true;
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

