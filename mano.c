#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void process_single_tree(char *row, int level, int n)
{
    // printf("process_tree(row: %s, level: %d, n: %d)\n", row, level, n);
    
    int pid;
    int status;

    if (n > level)
    {
        exit(0);
    }
    else
    {
        pid = fork();
        switch (pid)
        {
        case -1:
            printf("fork failed\n");
            break;
        case 0:
            printf("Process %s%d %d, from %d\n", row, n, getpid(), getppid());
            n += 1;
            process_single_tree(row, level, n);
            break;

        default:
            break;
        }
        
        wait(&status);
    }
}

void process_double_tree(int level, int n)
{
    // printf("process_tree_2(level: %d, n: %d)\n", level, n);

    int i;
    int index = 2;
    int pid;
    int status;
    char *row;

    for (i = 1; i <= index; i++)
    {
        row = i == 1 ? "A" : "B";
        if (n > 1)
        {
            // printf("fork exit(0)\n");
            exit(0);
        } else {
            // printf("for(i: %d, index: %d, n: %d, row: %s)\n", i, index, n, row);
        }

        pid = fork();
        switch (pid)
        {
        case -1:
            printf("fork failed\n");
            break;
        case 0:
            // printf("Process %s%d (%d/%d) %d, from %d\n", row, n, level, index, getpid(), getppid());
            printf("Process %s%d %d, from %d\n", row, n, getpid(), getppid());
            n += 1;
            process_single_tree(row, level, n);
            break;

        default:
            break;
        }
    }
    for (i = 0; i < index; i++)
    {
        wait(&status);
    }
}

// based on https://stackoverflow.com/questions/46250145
int main(int argc, char *argv[])
{
    int level = 0;
    int n = 1;

    // TODO: check if "argv"'s exist
    level = atoi(argv[1]);
    // TODO: check if "n" is between MIN and MAX

    printf("Inverted V process tree with n=%d\n", level);
    printf("Process AB has PID=%d\n", getpid());
    
    if(level > 0) {
        process_double_tree(level, n);
    }
}
