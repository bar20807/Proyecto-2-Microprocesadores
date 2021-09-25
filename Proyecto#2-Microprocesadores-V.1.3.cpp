/**
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3056 - Programacion de Microprocesadores
 * Auth: 	JJCelada
 * Date:	2020/08/26
 * Ver:		2.0 - 2021/08/22
 * 
 * naiveparallelPI.cpp
 * Calculo de PI sin protecciÃƒÂ³n a seccion critica
 */
 
#include <iostream>
#include <stdio.h>
#include <cmath>		//pow
#include <pthread.h>	

using namespace std;

//Input para el usuario
long long N = 0;
//---- Cuidar que THREAD_COUNT sea factor de N
const int THREAD_COUNT = 5;
//Instancia del objeto mutex
pthread_mutex_t lock;
//---- Memoria global para almacenar el resultado
long int sum = 1;

void *calc_Factorial(void *thread_rank);

int main()
{
    printf("Introduzca un numero entero positivo: ");
    scanf("%lld", &N);
    long i, rc;
	pthread_t threads[THREAD_COUNT];
	void *retorno;
	
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
	printf("Factorial Obtenido: %ld\n",sum);
	pthread_mutex_destroy(&lock);
	return 0;
}

//------------
// Serie para calculo de PI
//------------
void *calc_Factorial(void *thread_rank)
{
    pthread_mutex_lock(&lock);
    long double my_sum = sum;
	long my_rank = (long)thread_rank;
	long long i;
	//---- Lote de datos de cada thread
	long long my_n = N/THREAD_COUNT; //Implementar que se pueda con nÃºmeros impares o que no sean factores
	

	//---- Rango de datos para cada hilo
	long long my_first_i = my_n * my_rank;
	long long my_last_i = my_first_i + my_n;


	//----Suma parcial de los elementos asignados a cada hilo
	for(i=my_first_i; i<my_last_i; i++)
	{   
	    if(i == 0){
	        my_sum = my_sum * 1;
	    }else{
		    my_sum = my_sum * (i+1);
	    }
	    
	    printf("Factorial: %Lf\n",my_sum);
	}
	sum=my_sum;
	pthread_mutex_unlock(&lock);


	pthread_exit(NULL);
}