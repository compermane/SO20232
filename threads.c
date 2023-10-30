#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_THREADS 62000

void *print_hello_world() {
    /* Esta função imprime o identificador do thread e sai. */
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
        if(cont % 100 == 0)
        {
            clock_gettime(CLOCK_REALTIME, &tFinal);
            double tempo = (tFinal.tv_sec + tFinal.tv_nsec/10e9) - (tInicio.tv_sec + tInicio.tv_nsec/10e9);
            printf("O tempo para criar as ultimas 100 threads foi de: %lf\n", tempo);
        }
    }

    clock_gettime(CLOCK_REALTIME, &tFinal);

    printf("O numero de threads que foram criadas eh: %d\n", cont);

    return 0;

}