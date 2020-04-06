#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t gera_processo(char* tipo, int i) {
    pid_t pid = fork();

    if (pid < 0) { perror("Erro na funcao fork()"); exit(1); }
    // if (pid > 0) printf("Processo %s%d tem PID=%d e PPID=%d\n", tipo, i, (int)getpid(), (int)getppid());

    return pid;
}

int main(int argc, char *argv[]) {
    pid_t pidA = 0, pidB = 0;
    int n, i, parentIdA, parentIdB, status;

    // TODO: verificar se existem "argv"'s
    n = atoi(argv[1]);
    // TODO: verificar se "n" está compreendido entre MIN e MAX

    parentIdA = parentIdB = (int)getpid();
    printf("\nCadeia de processos em V invertido com n=%d\n", n);
    printf("Processo AB tem PID=%d\n", parentIdA);

    if(n > 0) {
        for (i = 1; i <= n; i += 1) {
            pidA = fork();

            if((int)pidA > 0) {
                // printf("> %d | %d | %d | %d\n", i, (int)pidA, (int)getpid(), (int)getppid());
                // pidB = gera_processo("B", i, parentIdB);
                printf("Processo A%d tem PID=%d e PPID=%d\n", i, (int)pidA, (int)getpid());
                break; // nao deixa imprimir filhos
            } else {
                // printf("> FILHO %d | %d | %d | %d\n", i, (int)pidA, (int)getpid(), (int)getppid);
                waitpid(pidA, &status, 0);
            }
        }
    }

    return 0;
}