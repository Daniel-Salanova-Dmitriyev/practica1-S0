#include "my_lib.h"
#include <assert.h>


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
        }else{
            return str1[i] - str2[i];
        }
    }
    //Si salimos puede ser porque en uno no hay datos o porque son iguales
    if(str1[i] && !str2[i]){ //En el caso de que str1 tenga los primeros caracteres iguales y sea mas grande 
        return str1[i];
    }else if (!str1[i] && str2[i]){ //En el caso de que str2 tenga los primeros caracteres iguales y sea mas grande 
        return str2[i];
    }//else if (cont == my_strlen(str1)){ 
        // En el caso de que sean iguales
    return 0;
   //}
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

//FUNCION MY_STACK_INIT
//OBJETIVO: Inicializa una estructura de tipo pila
//DEVUELVE: direccion de la pila
struct my_stack *my_stack_init(int size) {
    struct my_stack *pila=malloc(size);
    pila->size=size;
    pila->top=NULL;
    return pila;
}
//FUNCION MY_STACK_PUSH
//OBJETIVO: Añade un elemento a la pila
//DEVUELVE: 0
int my_stack_push(struct my_stack *stack,void *data) {
    struct my_stack_node nuevo;
    //Si la pila estaba vacía, el nodo se enlaza con el puntero first
    if(stack->top=NULL) {
        stack->top=&nuevo;
        nuevo.data=data;
        nuevo.next=NULL;
        return 0;
    //Si la pila contenía nodos, se crea un puntero auxiliar que busque 
    //el último nodo creado, y su puntero next se enlaza con nuestro nodo
    } else {
        //Puntero auxiliar
        struct my_stack_node *aux=stack->top;
        //Buscamos el ultimo nodo
        while(aux->next!=NULL) {
            aux=aux->next;
        }
        aux->next=&nuevo;
        nuevo.data=data;
        nuevo.next=NULL;
        return 0;
    }
}

//FUNCION MY_STACK_POP
//OBJETIVO: Saca un elemento de la pila, eliminando el nodo
//DEVUELVE: puntero a los datos del nodo eliminado
void *my_stack_pop (struct my_stack *stack) {
    //BUSCAMOS EL ULTIMO ELEMENTO
    //Caso de no tener elementos
    if(stack->top==NULL) {
        printf("No hay nada que exportar.");
        return NULL;
    //Caso de tener un unico elemento
    } else if (stack->top->next==NULL) {
        void *aux=stack->top;
        free(stack->top);
        return aux;
    //Caso de tener varios elementos
    } else {
        //Puntero auxiliar
        struct my_stack_node *aux=stack->top;
        //Buscamos el ultimo nodo
        while(aux->next->next!=NULL) {
            aux=aux->next;
        }
        return aux->next;
        free(aux->next);
        aux->next=NULL;
        free(aux);
    }
}

//FUNCION MY_STACK_LEN
//OBJETIVO: Calcula la longitud de una pila (numero de elementos)
//DEVUELVE: numero de elementos
int my_stack_len(struct my_stack *stack) {
    int numero;
    //Caso de no tener elementos
    if(stack->top==NULL) {
        numero=0;
    //Caso de tener un unico elemento
    } else if(stack->top->next==NULL) {
            numero=1;
    //Caso de tener varios elementos
    } else {
        struct my_stack_node *aux=stack->top;
        numero=1;
        //Recorremos hasta el ultimo nodo sumando 1 al contador
        while(aux->next!=NULL) {
            numero++;
            aux=aux->next;
        }
        return numero;
    }
}

//FUNCION MY_STACK_PURGE
//OBJETIVO: Elimina la pila y los datos apuntados por ella
//DEVUELVE:  numero de bytes liberados
int my_stack_purge (struct my_stack *stack) {
    int numero;
    struct my_stack_node *aux;
    //Caso de no tener elementos
    if (stack->top==NULL) {
        numero=sizeof(stack);
        free(stack);
        return numero;
    //Caso de tener elementos
    } else {
    //Mientras queden >1 elementos en la pila
    while (stack->top->next!=NULL) {
        numero=1,
        aux=stack->top;
        //Buscamos el ultimo elemento de la pila
        while(aux->next!=NULL) {
            aux=aux->next;
            numero++;
        }
        //Eliminamos los datos del ultimo elemento
        free(aux->data);
        free(aux->next);
        free(aux);
    }
    //Eliminamos el ultimo elemento que nos queda
    free(stack->top->data);
    free(stack->top->next);
    free(stack->top);
    //Eliminamos la pila
    int bytesPila=sizeof(stack);
    free(stack->top);
    free(stack);
    numero+=bytesPila;
    numero*=stack->size;
    return numero;
    }
}

//void main(){
    //char cad1[5] = "apa";
    //char cad2[5] = "apo";
    //int a = my_strcmp(cad1,cad2);
    //printf("Valor de la comparacion: %i", a);
    // char cad1[50] = "Inicio-";
    // char cad2[50] = "Final";
    // my_strcat(cad1,cad2);
    // printf("My frase queda como: %s", cad1);

    
//}
