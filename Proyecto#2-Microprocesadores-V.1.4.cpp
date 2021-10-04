/*
 * Proyecto 2 - Programación de microprocesadores
 * Temario: Factorial de un número usando Threads
 * Integrantes:
    Rodrigo Barrera 
    Jun Woo Lee
    Roberto Vallecillos
 * Versión del programa: #1.4
 *
*/
 
#include <iostream>
#include <stdio.h>
#include <cmath>		
#include <pthread.h>	

using namespace std;

//Input para el usuario
long long N = 0;
//---- Cuidar que THREAD_COUNT sea factor de N
const int THREAD_COUNT = 3;
//Instancia del objeto mutex
pthread_mutex_t lock;
pthread_mutex_t lock_1;
//---- Memoria global para almacenar el resultado
long long sum = 1;
int space[THREAD_COUNT];
int res = 0;
int cont = 0;
void *calc_Factorial(void *thread_rank);

int main()
{
    printf("/*/*/*/*/*/*/*/ Realiza tu cálculo factorial con hilos /*/*/*/*/*/*/*/*/*/*/\n");
    printf("Introduzca un numero entero positivo: ");
    scanf("%lld", &N);
    
    long i, rc;
    res = N % THREAD_COUNT;
	pthread_t threads[THREAD_COUNT];
	void *retorno;
	for(i=0; i<THREAD_COUNT; i++){
	    space[i] = N/THREAD_COUNT;
	    if (res > 0){
	        space[i] = (N/THREAD_COUNT) + 1;
	        res--;
	    }
	}
	
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&lock_1, NULL);
	for(i=0;i<THREAD_COUNT;i++)
	{
		rc = pthread_create(&threads[i],NULL,calc_Factorial,(void *)i);
		if(rc)
		{
			cout<<">>>Error creating threads"<<endl;
			exit(-1);
		}
		
	}
	for(i=0;i<THREAD_COUNT;i++){
		rc = pthread_join(threads[i],NULL);
		if(rc){
			cout<<"Error joining threads"<<endl;
			exit(-1);
		}
	}
	printf("Factorial Obtenido: %lld\n",sum);
	pthread_mutex_destroy(&lock);
	pthread_mutex_destroy(&lock_1);
	return 0;
}

//------------
// Serie para calculo del factorial de un número
//------------
void *calc_Factorial(void *thread_rank)
{
    
    
    long my_rank = (long)thread_rank;
    
    pthread_mutex_lock(&lock);
    int temp = cont;
    cont = cont + space[my_rank];
    //---- Rango de datos para cada hilo
    long long my_first_i = temp;
    long long my_last_i = cont;
    pthread_mutex_unlock(&lock);
    
    long long my_sum = sum;
	long long i;
	//---- Lote de datos de cada thread
	long long my_n = N/THREAD_COUNT; //Implementar que se pueda con nÃºmeros impares o que no sean factores
    
    printf("Inicio: %lld\n", my_first_i);
    printf("Final: %lld\n", my_last_i);
    printf("Thread: %ld\n", my_rank);
	//----Suma parcial de los elementos asignados a cada hilo
	for(i=my_first_i; i<my_last_i; i++)
	{   
	    if(i == 0){
	        my_sum = my_sum * 1;
	    }else{
		    my_sum = my_sum * (i+1);
	    }

	}
	
	pthread_mutex_lock(&lock_1);
	sum=my_sum;
	pthread_mutex_unlock(&lock_1);


	pthread_exit(NULL);
}