#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MIN 0
#define MAX 32

/**
 * Validates if the interaction number is between the acceptable range
 * @param int lines to process
 * @return nothing
 */
void validateInteractions(int interactions)
{
    if (interactions < MIN || interactions > MAX)
    {
        printf("Level must be between %d and %d", MIN, MAX);
        exit(1);
    }
}

/**
 * Validates if there are enough arguments
 * @param int number of arguments (argc)
 * @return nothing
 */
void validateArguments(int arguments) {
    if (arguments < 2)
    {
        printf("A decimal argument must be declared");
        exit(1);
    }
}

/**
 * Processes a single fork() and his child
 * @param char the column Letter that the column belongs
 * @param int the max interactions to process
 * @param int the current row id
 * @return nothing
 */
void process_single_tree(char *colLetter, int maxInteractions, int currentRow)
{
    int pid;
    int status;

    if (currentRow > maxInteractions)
    {
        exit(0);
    }

    pid = fork();
    switch (pid)
    {
    case -1:
        printf("fork failed\n");
        break;
    case 0:
        printf("Process %s%d %d, from %d\n", colLetter, currentRow, getpid(), getppid());
        currentRow += 1;
            // process 1 fork and his child
        process_single_tree(colLetter, maxInteractions, currentRow);
        break;

    default:
        break;
    }

    wait(&status);
}

/**
 * Processes double fork() and their childs
 * @param int the max interactions to process
 * @param int the current row id
 * @return nothing
 */
void process_double_tree(int maxInteractions, int currentRow)
{
    int i;
    int index = 2; // process twice
    int pid;
    int status;
    char *colLetter; // column letter

    for (i = 1; i <= index; i++)
    {
        colLetter = i == 1 ? "A" : "B";
        if (currentRow > 1)
            exit(0);

        pid = fork();
        switch (pid)
        {
        case -1:
            printf("fork failed\n");
            break;
        case 0:
            printf("Process %s%d %d, from %d\n", colLetter, currentRow, getpid(), getppid());
            currentRow += 1;
            // process 1 fork and his child
            process_single_tree(colLetter, maxInteractions, currentRow);
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

int main(int argc, char *argv[])
{
    int interactions;
    int currentRow = 1;

    // check if "argv[1]" is valid
    validateArguments(argc);

    interactions = atoi(argv[1]);

    // check if level is between MIN and MAX
    validateInteractions(interactions);

    printf("Inverted V process tree with n=%d\n", interactions);
    printf("Process AB has PID=%d\n", getpid());

    // there are levels to process
    if (interactions > 0)
    {
        // create 2 forks and process each child
        process_double_tree(interactions, currentRow);
    }
}
