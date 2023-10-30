// Nome: Eugênio Akinori Kisi Nishimiya RA: 811598
// Nome: Nataly Cristina da Silva RA: 812719

/*
    O número máximo de threads que podem ser criadas no sistema, segundo
    o comando $ cat /proc/sys/kernel/threads-max é de 62278. Porém o número
    de threads que podem ser criadas segundo o algoritmo é de 32751. O gargalo
    entre o número real do máximo de threads e o número de threads contadas
    pode ser devido a vários fatores, como a memória disponível. 
    O tempo para criar as 32751 threads foi significantemente maior que o tempo
    de criação de processos, chegando a 3.019064 segundos.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_NUMBER_OF_THREADS 62278

void *print_hello_world() {
    // Esta função imprime o identificador do thread e sai. 
    printf("O identificador da thread eh: %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads;
    int cont = 0, i = 1;
    struct timespec tInicio, tFinal;
    
    clock_gettime(CLOCK_REALTIME, &tInicio);

    while(pthread_create(&threads, NULL, print_hello_world, NULL) == 0)
    {
        printf("Criando thread %d\n", i);
        cont++;
        i++;
    }

    clock_gettime(CLOCK_REALTIME, &tFinal);
    double tempo = (tFinal.tv_sec + tFinal.tv_nsec/10e9) - (tInicio.tv_sec + tInicio.tv_nsec/10e9);
    printf("O tempo para criar as ultimas %d threads foi de: %lf\n", cont, tempo);
    printf("O numero de threads que foram criadas eh: %d\n", cont);
    printf("O numero maximo de threads do sistema eh: %d\n", PTHREAD_THREADS_MAX);

    return 0;

}