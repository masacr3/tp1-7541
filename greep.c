#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool buscar(char *exp, char *cadena, int *i);
void lookposition(int p,char *e, char *c);
void msj(char *s);

int main(){
	char *e = "od";
	char *e2 = "o r";
	char *cad = "hola como estas todo bien leo";
	char *cad2 = "la verdad la otra vez el gordo rata me choreo la garrafa";
	int j = 0;
	int i = 0;
	msj("¬¬ test ¬¬\n");

	if ( buscar ( e, cad, &i) ) lookposition(i,e,cad);
	else printf("\n\nno se encontro nada\n\n");

	if ( buscar( e2, cad2, &j) ) lookposition(j,e2,cad2);
	else printf("\n\nno se encontro nada\n\n");
	
	j=0;

	if ( buscar( e, cad2, &j) ) lookposition(j,e,cad2);
	else printf("\n\nno se encontro nada\n\n");	
	
	return 0;
}

void msj(char *s){
	printf("%s\n",s);
}

bool buscar(char *exp, char *cadena, int *i){
	size_t le = strlen(exp);
	size_t lc = strlen(cadena);

	if ( le > lc ) return false;
	
	int match;

	while( *i < lc - le ){
		if ( cadena[*i] == exp[0] ) {
			int j = 0;
			match = 0;
			while( j < le && *i < lc ){
				if ( cadena[*i] == exp[j] ){
					match++;
					*i += 1;
					j++;
					if ( match == le ) return true;
				}
				else break;
			}
		}
		*i += 1 ;
	}
	return false;
}

void lookposition(int p,char *e, char *c){
	printf("texto->");
	msj(c);
	printf("exp--->");
	for (int i=0; i<p-strlen(e); i++){
		printf(" ");
	}
	msj(e);
	printf("\n");
}
