#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getMaxNoProcess(pid_t pid)
{
	pid_t newPid = fork();
	
	if(newPid < 0)
		return 1;
		
	return getMaxNoProcess(newPid) + 1;
}

int main()
{
	pid_t pid;
	int count = getMaxNoProcess(pid);
	
	printf("O numero de processos maximo eh: %d\n", count);
	exit(0);
}
