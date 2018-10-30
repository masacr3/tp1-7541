#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cola.h"

bool buscar_expresion(char *exp, char *cadena);
void mostrar_lineas(cola_t *);
void grep(int argc, char *argv[]);

int main(int argc, char *argv[]){
	grep(argc, argv);
	return 0;
}

void grep(int argc, char *argv[]){
	if ( argc < 3 ){ 
		fprintf(stderr,"%s","Cantidad de parametros erronea\n");
		return;
	}
	
	int n = atoi(argv[2]);

	if( (!n && strcmp(argv[2],"0") != 0)  || n < 0) {
		fprintf(stderr,"%s","Cantidad de parametros erronea\n");	
		return;
	}
	
	cola_t *cola = cola_crear();

	if ( argc == 4 ){
		FILE *f;
		char *archivo = argv[3];
		if ((f = fopen(archivo,"r")) == NULL ){
			fprintf(stderr,"%s\n","No se pudo leer el archivo indicado");
			cola_destruir(cola,NULL);
			return;
		}
		
		char *linea = NULL;
		size_t cap = 0;
		int i = 0;
		char *expresion = argv[1];
			
		while(true){
			if ( getline(&linea,&cap,f) == EOF ) break;
			
			char *nueva_linea = malloc(sizeof(char) * ( strlen(linea) + 1) );
			strcpy(nueva_linea,linea);
			cola_encolar(cola,nueva_linea);

			if ( i > n ){
				char *borrar_linea = cola_desencolar(cola);
				free(borrar_linea);
			}
			
			i++;

			if ( buscar_expresion(expresion, linea) ) {
				mostrar_lineas(cola);
				i = 0;
			}
			
			
		}
		cola_destruir(cola,free);
		fclose(f);
		free(linea);		
	}
	else{
		char *linea = NULL;
		size_t cap = 0;
		int i = 0;
		char *expresion = argv[1];
		
		while(true){
			if ( getline(&linea,&cap,stdin) == EOF ) break;

			char*nueva_linea = malloc( sizeof(char) * ( strlen(linea) + 1) );
			strcpy(nueva_linea,linea);
			cola_encolar(cola, nueva_linea);

			if ( i > n ) {
				char *borrar_linea = cola_desencolar(cola);
				free(borrar_linea);
			}
			
			i++;

			if ( buscar_expresion(expresion, linea)) {
				mostrar_lineas(cola);
				i = 0;
			}
		}
		cola_destruir(cola,free);
		free(linea);
	}

	return;
}

bool buscar_expresion(char *exp, char *cadena){
	size_t le = strlen(exp);
	size_t lc = strlen(cadena);

	if ( le > lc ) return false;
	
	int match;
	int i = 0;

	while( i < lc - le ){
		if ( cadena[i] == exp[0] ) {
			int j = 0;
			match = 0;
			while( j < le && i < lc ){
				if ( cadena[i] == exp[j] ){
					match++;
					i += 1;
					j++;
					if ( match == le ) return true;
				}
				else break;
			}
		}
		i += 1 ;
	}
	return false;
}

void mostrar_lineas(cola_t *cola){
	while (!cola_esta_vacia(cola)){
		char *linea = cola_desencolar(cola);
		fprintf(stdout,"%s",linea);
		free(linea);
	}

}
