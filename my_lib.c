#include "my_lib.h"

size_t my_strlen(const char *str) {
   size_t len = 0;
   int i = 0;
 
   while (str[i]) { // o while (str[i]!='\0')
           i++;
           len++;
   }
   return len;
}


int my_strcmp(const char *str1, const char *str2){
    int cont = 0; //Contabiliza cuantas coinciden
    int i = 0; //Utilizado para recorrer a la vez str1 y str2
    for(; str1[i] && str2[i]; i++){
        if(str1[i] - str2[i] == 0){
            cont++;
        }else if(str1[i] - str2[i] > 0){
            return 1;
        }else{
            return -1;
        }
    }
    //Si salimos puede ser porque en uno no hay datos o porque son iguales
    if(str1[i] && !str2[i]){ //En el caso de que str1 tenga los primeros caracteres iguales y sea mas grande 
        return 1;
    }else if (!str1[i] && str2[i]){ //En el caso de que str2 tenga los primeros caracteres iguales y sea mas grande 
        return -1;
    }else if (cont == my_strlen(str1)){ // En el caso de que sean iguales
        return 0;
    }
}

char *my_strcpy(char *dest, const char *src){
	char* str = dest;
	while ((*dest++ = *src++)!= '\0');
	return str;
}

char *my_strncpy(char *dest, const char *src, size_t n){
    char *cp = dest;
	while (n && (*dest++ = *src++))	{
		n--;
	}
	if (n>0){
		while (--n)	{
			*dest++ = '\0';
		}
	}
	return cp;
}

char *my_strcat(char *dest, const char *src){
    int posNull = 0;
    while(dest[posNull]){ //Hayamos el caracter \0
        posNull++;
    }
    printf("Posicion del Null: %i\n", posNull);
    //Ahora sabemos donde esta la posNull, procedemos ha añadir caracteres
    int i = 0;
    for(; src[i];i++ ){
        dest[posNull++] = src[i];
   
    }
    //Colocamos el final de cadena
    dest[posNull] = '\0';
    return dest;
}
char *my_strchr(const char *str, int c){
	assert(str != NULL);//comprobamos que no este vacio
	while (*str)// mientras *str sea distinto de \0 seguira buscando
	{
		if (*str == c) //si la letra de la dirección es igual a la que buscamos
			return (char *)str;//se devuelve la dirección de la letra
		else
			str++;//si no es la letra que buscamos pasamos a la siguiente
	}
	return NULL;//en caso de que no haya la letra devolvemos un valor nulo
}
int main(){
    //char cad1[5] = "apa";
    //char cad2[5] = "apo";
    //int a = my_strcmp(cad1,cad2);
    //printf("Valor de la comparacion: %i", a);
    char cad1[50] = "Inicio-";
    char cad2[50] = "Final";
    my_strcat(cad1,cad2);
    printf("My frase queda como: %s", cad1);
    return 0;
}
