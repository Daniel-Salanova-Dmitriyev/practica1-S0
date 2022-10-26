#include <stdio.h>
#include <string.h>


struct Vehiculo{
    int id;
    char marca[20];
};

struct Vehiculo vehiculo;

int main(){
    struct Vehiculo *veh_ptr; //Objeto tipo Vehiculo
    veh_ptr = &vehiculo; //relacionamos el puntero creado con el vehiculo definido

    vehiculo.id = 1;
    strcpy(vehiculo.marca, "Opel");

    printf("Su id: %d\n", veh_ptr->id);
    printf("Su marca: %s\n", veh_ptr->marca);

    
    return 0;
}