#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

/**
 * main - Entry point of the Shell program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *input = NULL;
	size_t buffersize = 0;
	ssize_t input_len;
	pid_t pid;
	int status;

	while (1)
	{
		/* Display shell prompt */
		printf("#cisfun$ ");
		fflush(stdout);

		/* Read the input command line */
		input_len = getline(&input, &buffersize, stdin);
		if (input_len == -1) /* Handle end of input (Ctrl+D) */
		{
			printf("\n");
			break;
		}

		/* Remove the newline character at the end */
		if (input_len > 0 && input[input_len - 1] == '\n')
			input[input_len - 1] = '\0';

		/* If the input is empty, continue to the next iteration */
		if (strcmp(input, "") == 0)
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
			/* In Child process: execute the command */
			char *argv[] = {input, NULL};

			if (execve(input, argv, environ) == -1)
			{
				perror("Command execution failed");
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
	free(input);
	return (0);
i}
