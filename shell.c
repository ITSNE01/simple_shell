#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point of the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        /* Display the prompt */
        printf("#cisfun$ ");
        fflush(stdout);

        /* Read the input command line */
        nread = getline(&line, &len, stdin);
        if (nread == -1) /* Handle EOF (Ctrl+D) */
        {
            printf("\n");
            break;
        }

        /* Remove the newline character at the end */
        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* If the input is empty, continue to the next iteration */
        if (strcmp(line, "") == 0)
            continue;

        /* Fork a new process */
        pid = fork();
        if (pid < 0)
        {
            /* Fork failed */
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            /* Child process: execute the command */
            char *argv[] = {line, NULL};
            if (execve(line, argv, environ) == -1)
            {
                perror(line);
                exit(1);
            }
        }
        else
        {
            /* Parent process: wait for the child to finish */
            waitpid(pid, &status, 0);
        }
    }

    /* Free allocated memory and exit */
    free(line);
    return (0);
}

