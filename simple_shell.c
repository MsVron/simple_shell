#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void)
{
    printf("$ "); /* Custom prompt */
    fflush(stdout);
}

char *read_command(void)
{
    char *command = malloc(BUFFER_SIZE);
    fgets(command, BUFFER_SIZE, stdin);
    return command;
}

void execute_command(char *command)
{
    command[strcspn(command, "\n")] = '\0'; /* Remove trailing newline character */
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        /* Child process */
        char *args[] = {command, NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char *argv[])
{
    char *filename = NULL;

    if (argc == 2)
    {
        /* Check if a filename is provided as a command line argument */
        filename = argv[1];
    }

    if (filename != NULL)
    {
        /* File mode: execute commands from the file */
        FILE *file = fopen(filename, "r");

        if (file == NULL)
        {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char line[BUFFER_SIZE];

        while (fgets(line, sizeof(line), file))
        {
            execute_command(line);
        }

        fclose(file);
    }
    else
    {
        /* Interactive mode: read commands from stdin */
        while (1)
        {
            display_prompt();

            char *command = read_command();

            if (feof(stdin))
            {
                /* Handle end of file (Ctrl+D) */
                printf("\n");
                break;
            }

            execute_command(command);

            free(command);
        }
    }

    return 0;
}
