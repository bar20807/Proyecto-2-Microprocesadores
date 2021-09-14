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

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

const int THREADS = 2;
pthread_t tid[THREADS];
pthread_mutex_t lock;
long resultado;
//Definimos la función que permite calcular el factorial del número
long *factorial(long n){
    //Función iterativa que calcula el factorial de un número
    pthread_mutex_lock(&lock);
    long *r =(long*)malloc(1*sizeof(long));
    long i=1,f=1;
    resultado=0;
    while(i<=n){
        f=f*i;
        i++;
    }
    resultado=f;
    r[0]=resultado;
    pthread_mutex_unlock(&lock);
    return r;
}

//Definimos la misma función, pero utilizando argumentos genericos
void *pasar_factorial(void *args){
    long n = *((long*)args);
    return (void*)factorial(n);
}

int main(int argc, char **argv)
{
    int i = 0;    
    int err;
    long n;
    
    printf("Introduzca un numero entero positivo: ");
    scanf("%ld", &n);
    
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init failed\n");        
        return 1;
    }
    
    while(i < THREADS){
        err = pthread_create(&(tid[i]), NULL, &pasar_factorial, &n);      
        if (err != 0){
            printf("\ncan't create thread");
        }
        i++;
    }
    
    for(i=0;i<THREADS;i++){
        pthread_join(tid[i], NULL);
    }
    printf("El factorial de %ld es %ld\n",n,resultado);
    pthread_mutex_destroy(&lock);
    return 0;
}