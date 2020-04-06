#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pidA = 0, pidB = 0;
    int n, i, parentIdA, parentIdB, status;

    // TODO: check if "argv"'s exist
    n = atoi(argv[1]);
    // TODO: check if "n" is between MIN and MAX

    parentIdA = parentIdB = (int)getpid();
    printf("Inverted V process tree with n=%d\n", n);
    printf("Process AB has PID=%d\n", parentIdA);

    if (n > 0)
    {
        for (i = 1; i <= n; i += 1)
        {
            pidA = fork();

            if ((int)pidA > 0)
            {
                // printf("> %d | %d | %d | %d\n", i, (int)pidA, (int)getpid(), (int)getppid());
                printf("Process A%d has PID=%d and PPID=%d\n", i, (int)pidA, (int)getpid());
                break; // don't print child
            }
            else
            {
                //waitpid(pidA, &status, 0);

                pidB = fork();

                if ((int)pidB > 0)
                {
                    // printf("> %d | %d | %d | %d\n", i, (int)pidA, (int)getpid(), (int)getppid());
                    printf("Process B%d has PID=%d and PPID=%d\n", i, (int)pidB, i == 1 ? (int)getppid() : (int)getppid());
                    break; // don't print child
                }
                else
                {
                    // printf("> %d | %d | %d | %d\n", i, (int)pidA, (int)getpid(), (int)getppid);
                    waitpid(pidB, &status, 0);
                }
            }
        }
    }

    return 0;
}
