#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

int main() {
    int count = 0;
    pid_t pid;
    struct timespec tInicio, tFinal;

    clock_gettime(CLOCK_REALTIME, &tInicio);

    while(1) 
    {
        pid = fork();
        // Erro ao criar um novo processo (número máximo de processos foi atingido)
        if(pid == -1)
        {
            perror("fork");
            printf("O valor de retorno de erro na criação eh: %d\n", errno);
            break;
        }
        // Este é um processo filho
        else if(pid == 0)
            exit(0);
        // Este é o processo pai
        else
            count++;
    }

    clock_gettime(CLOCK_REALTIME, &tFinal);
    float tempo = (tFinal.tv_sec + tFinal.tv_nsec/10e9) - (tInicio.tv_sec + tInicio.tv_nsec/10e9);

    printf("A quantidade máxima de processos é: %d\n", count);
    printf("O tempo de execucao foi de: %lf\n", tempo);

    return 0;
}