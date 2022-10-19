#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
PROGRAMADORES:
Salvà Salvà, Macià
Kosyuk, Arkadiy
Mikhailovskiy, Robert
*/

struct my_stack_node {      // nodo de la pila (elemento)
   void *data;
   struct my_stack_node *next;
};
struct my_stack {   // pila
   int size;       // tamaño de data, nos lo pasarán por parámetro
   struct my_stack_node *first;  // apunta al nodo de la parte superior
};

//DECLARACIONES DE FUNCIONES
size_t my_strlen(const char *str);
int my_strcmp(const char *str1, const char *str2);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t n);
char *my_strcat(char *dest, const char *src);

struct my_stack *my_stack_init(int size);
int my_stack_push(struct my_stack *stack, void *data);
void *my_stack_pop(struct my_stack *stack);
int my_stack_len(struct my_stack *stack);
struct my_stack *my_stack_read(char *filename);
int my_stack_write(struct my_stack *stack, char *filename);
int my_stack_purge(struct my_stack *stack);

//FUNCION MY_STRLEN
//OBJETIVO: Calcula el numero de caracteres de una linea
//DEVUELVE: numero de caracteres
size_t my_strlen(const char *str)
{
    int i;
    for (i=0;str[i]!=0;i++){
    }
    return i;
}

//FUNCION MY_STRCMP
//OBJETIVO: Compara dos lineas apuntadas por str1 y str2
//DEVUELVE: -1,0 o 1 dependiendo del resultado de comparacion
int my_strcmp(const char *str1, const char *str2){
   int len1=strlen(str1);
   int len2=strlen(str2);
   int menor;
   //Necesitamos un valor para la variable "menor"
   if(len1<len2){
       menor=len1;
   } else{
       menor=len2;
   }
int i=0;
//Busqueda de algun caracter diferente
    while(i<menor&str1[i]==str2[i]){
        i++;
    }
    //Los posibles 5 casos que puede haber
    if(str1[i]==str2[i]&len1==len2){
        return 0;
    }else if (len1==len2&str1[i]<str2[i]){
        return -1;
    }else if (len1==len2&str1[i]>str2[i]){
        return 1;
    }else if(len1<len2){
        return -1;
    }else if (len1>len2){
        return 1;
    }
}

//FUNCION MY_STRCPY
//OBJETIVO: Copia los caracteres de una linea a otra
//DEVUELVE: puntero Dest
char *my_strcpy(char *dest, const char *src){
     int i=0;
    while(src[i]){
         dest[i]=src[i];
         i++;
    }
    dest[i]=0;
    return dest;
}

//FUNCION MY_STRNCPY
//OBJETIVO: Copia n caracteres de una linea a otra
//DEVUELVE: puntero Dest
char *my_strncpy(char *dest, const char *src, size_t n){
    int n;
    for (int i = 0; i<n; i++){
        dest[i]=src[i];
}
return dest;
}

//FUNCION MY_STRCAT
//OBJETIVO: Concatena la segunda linea con la primera
//DEVUELVE: puntero Dest
char *my_strcat(char *dest, const char *src) {
    
    char *aux=malloc((1+strlen(dest))*(sizeof(char)));
    int len1=strlen(src);
    int len2=strlen(dest);
    int j=0;

    for (int i=0;i<len2;i++) {
        aux[i]=dest[i];
    }
    
    dest=malloc((len1+len2+1)*sizeof(char));
    
    for (int i=0;i<len2;i++) {
        dest[i]=aux[i];
        
    }
    for (int i=len2;i<len1+len2;i++) {
        dest[i]=src[j];
        j++;
        
    }
    dest[len1+len2]=0;
    return dest;
}

//................PARTE 2................//

//FUNCION MY_STACK_INIT
//OBJETIVO: Inicializa una estructura de tipo pila
//DEVUELVE: direccion de la pila
struct my_stack *my_stack_init(int size) {
    struct my_stack *pila=malloc(size);
    pila->size=size;
    pila->first=NULL;
    return pila;
}
//FUNCION MY_STACK_PUSH
//OBJETIVO: Añade un elemento a la pila
//DEVUELVE: 0
int my_stack_push(struct my_stack *stack,void *data) {
    struct my_stack_node nuevo;
    //Si la pila estaba vacía, el nodo se enlaza con el puntero first
    if(stack->first==NULL) {
        stack->first=&nuevo;
        nuevo.data=data;
        nuevo.next=NULL;
        return 0;
    //Si la pila contenía nodos, se crea un puntero auxiliar que busque 
    //el último nodo creado, y su puntero next se enlaza con nuestro nodo
    } else {
        //Puntero auxiliar
        struct my_stack_node *aux=stack->first;
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
    if(stack->first==NULL) {
        printf("No hay nada que exportar.");
        return NULL;
    //Caso de tener un unico elemento
    } else if (stack->first->next==NULL) {
        void *aux=stack->first;
        free(stack->first);
        return aux;
    //Caso de tener varios elementos
    } else {
        //Puntero auxiliar
        struct my_stack_node *aux=stack->first;
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
    if(stack->first==NULL) {
        numero=0;
    //Caso de tener un unico elemento
    } else if(stack->first->next==NULL) {
            numero=1;
    //Caso de tener varios elementos
    } else {
        struct my_stack_node *aux=stack->first;
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
    if (stack->first==NULL) {
        numero=sizeof(stack);
        free(stack);
        return numero;
    //Caso de tener elementos
    } else {
    //Mientras queden >1 elementos en la pila
    while (stack->first->next!=NULL) {
        numero=1,
        aux=stack->first;
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
    free(stack->first->data);
    free(stack->first->next);
    free(stack->first);
    //Eliminamos la pila
    int bytesPila=sizeof(stack);
    free(stack->first);
    free(stack);
    numero+=bytesPila;
    numero*=stack->size;
    return numero;
    }
}
