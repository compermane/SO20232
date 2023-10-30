// Nome: Eugênio Akinori Kisi Nishimiya RA: 811598
// Nome: Nataly Cristina da Silva RA: 812719

/*
    O valor máximo de processos que podem ser criados no sistema, segundo o comando
    $ ulimit -u é de 31140. A quantidade aferida de processos usando esse algoritmo
    é de 31000. Esse gargalo de 140 processos não contados se deve aos outros 140
    processos que já estavam rodando no momento em que o algoritmo foi executado.
    Essa quantidade de processos foi aferida usando o comando $ ps aux | wc -l, que 
    mostra a quantidade de processos rodando.
    O tempo para criar todos esses processos foi de 1.02629 segundos.
*/

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