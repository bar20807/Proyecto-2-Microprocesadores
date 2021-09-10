/*
 * Proyecto 2 - Programación de microprocesadores
 * Temario: Factorial de un número usando Threads
 * Integrantes:
    Rodrigo Barrera 
    Jun Woo Lee
    Roberto Vallecillos
 * Versión del programa: #1
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Definimos la función que permite calcular el factorial del número
long *factorial(long n){
    //Función iterativa que calcula el factorial de un número
    long *r =(long*)malloc(1*sizeof(long));
    long i=1,f=1;
    while(i<=n){
        f=f*i;
        i++;
    }
    r[0]=f;
    printf("El factorial de %ld es %ld\n",n,f);
    return r;
}

//Definimos la misma función, pero utilizando argumentos genericos
void *pasar_factorial(void *args){
    long n = *((long*)args);
    return (void*)factorial(n);
}

int main(int argc, char **argv)
{
    long n;
    printf("Introduzca un numero entero positivo: ");
    scanf("%ld", &n);
    pthread_t thread[1];
    pthread_create(&thread[0],NULL,pasar_factorial,&n);
    pthread_join(thread[0],NULL);

    return 0;
}
