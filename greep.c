#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool buscar(char *exp, char *cadena);

int main(int argc, char *argv[]){
	if ( argc < 3 ){ 
		fprintf(stderr,"%s","Cantidad de parametros erronea\n");
		return 0;
	}
	
	int numero = atoi(argv[2]);

	if( (!numero && strcmp(argv[2],"0") != 0)  || numero < 0) {
		fprintf(stderr,"%s","Cantidad de parametros erronea\n");	
		return 0;
	}

	if ( argc == 4 ){
		FILE *f;
		if ((f = fopen(argv[3],"r")) == NULL ){
			fprintf(stderr,"%s\n","No se pudo leer el archivo indicado");
			return 0;
		}
		
		char *linea = NULL;
		size_t cap = 0;
		while(true){
			if ( getline(&linea,&cap,f) == EOF ) break;
			
			if ( buscar(argv[1],linea) ) printf("%s\n",linea);
		}
		fclose(f);
		free(linea);		
	}
	else{
	
	}

	return 0;
}

bool buscar(char *exp, char *cadena){
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
