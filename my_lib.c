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

}

char *my_strcpy(char *dest, const char *src){
	while ((*dest++ = *src++)!= '\0');//copia la cadena apuntada por src en la memoria apuntada por dest.
	return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n){
	while (n && (*dest++ = *src++))	{//copia la cadena apuntada por src  en la memoria apuntada por dest.
		n--;
	}
	if (n>0){
		while (--n)	{//copia n caracteres de la cadena(con el carácter de terminación ‘\0’)
			*dest++ = '\0';
		}
	}
	return dest;
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

/**
 * Inicializamos la pila
*/
struct my_stack *my_stack_init(int size) {
    struct my_stack *pila=malloc(sizeof(struct my_stack)); //Guardamos espacio en memoria para la pila
    pila->size=size;    //Esto indicará el tamaño de los datos a colocar
    pila->top=NULL;     //Como no hay nada lo ponemos a NULL
    return pila;
}
/**
 * Función con la que podremos añadir datos a la pila
*/
int my_stack_push(struct my_stack *stack,void *data) {
    if(stack == NULL){ //Si el stack no ha sido inicializado
        return -1;
    }

    if(stack->size <= 0){
        return -1;
    }

    //Creamos el elemento a añadir
    struct my_stack_node *nuevo;
    nuevo = malloc(sizeof(struct my_stack_node)); //Guardamos espacio en memoria para el elemento

    if(!nuevo){ //Si no se le ha podido asignar memoria o ha fallado la asignacion
        return -1;
    }

    struct my_stack_node *antiguoTop = stack->top;
    
    //Asignamos el dato y el siguiente nodo    
    nuevo->data = data;
    nuevo->next = antiguoTop;

    //Actualizamos el top
    stack->top = nuevo;
    return 0;
    
}

/**
 * Función con el que eliminamos el top de la pila
*/
void *my_stack_pop (struct my_stack *stack) {
    if(stack->top == NULL){ //En el caso de que este vacio
        return NULL;
    }else{
        //Nodo a eliminar
        struct my_stack_node *nodo = stack->top;

        //Recogemos el dato
        void *dato = nodo->data;

        //Actualizamos el puntero de top
        stack->top = nodo->next;

        //Liberamos la memoria del top anterior
        free(nodo);

        return dato;
    }
    
}


/**
 * Función que recorre la pila entera, guardando de esta manera cuantos elementos hay
*/
int my_stack_len(struct my_stack *stack) {
    int contador = 0; //Contador

    struct my_stack_node *nodo = stack->top; //Primer dato
    while(nodo != NULL){
        //Actualizamos el contador y el siguiente nodo
        contador++;
        nodo = nodo->next;
    }

    return contador;
    
}

/**
 * Devolvemos la cantidad de memoria liberada
*/
int my_stack_purge (struct my_stack *stack) {
    int liberado = stack->size; //Memoria liberada
    int numero = 0; //Cuenta los nodos que hay
    struct my_stack_node *aux; //Nuestro indice

    while(stack->top){ //Mientras no este vacío
        aux = stack->top;
        stack->top = stack->top->next;
        free(aux); //Liberamos
        numero++;        
    }
    liberado *= numero; //Cuanto han ocupado los datos
    liberado += numero * sizeof(struct my_stack_node) + sizeof(struct my_stack);
    return liberado;
}




int my_stack_write (struct my_stack *stack, char *filename){
    struct my_stack *aux;
    aux = my_stack_init(stack->size);
    struct my_stack_node *nodo = stack->top;
    int result;
    while (nodo!=NULL)
    {
        void *dato= nodo->data;
        my_stack_push(aux,dato);
        nodo=nodo->next;

    }
    int fichero = open(filename, O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);

    if (fichero==-1){
        exit(1);
        return -1;

    }
     
    result = write(fichero,&(aux->size),4);
    if (result==-1){
        close(fichero);
        return -1;
    }

    int contador=0;
    while (aux->top!=NULL)
    {
        void *dato = my_stack_pop(aux);
        result = write(fichero, dato, aux->size);
        if (result==-1){
            close(fichero);
            return -1;
        }
        contador++;
    }
    
    close(fichero);
    return contador;
}
