#include "main.h"

#define BUFFER_SIZE 1024


/**
 *display_prompt - Displays a custom prompt
 *
 *Description: This function prints a custom prompt "$ " to the standard
 *             output. It ensures that the prompt is immediately visible by
 *             flushing the standard output buffer.
 */
void display_prompt(void)
{
    printf("$ "); /* Custom prompt */
    fflush(stdout);
}

/**
 * read_command - Reads a command from standard input
 *
 * Description: This function reads a command from standard input using fgets
 *              and returns it as a dynamically allocated string.
 *
 * Return: A pointer to the dynamically allocated string containing the command.
 */
char *read_command(void)
{
    char *command = malloc(BUFFER_SIZE);
    fgets(command, BUFFER_SIZE, stdin);
    return command;
}

/**
 *execute_command - Executes a command
 *
 *@command: The command to execute
 *
 *Description: This function executes a command by forking a child process and
 *             using execvp to run the command. If the command is "exit", it
 *             exits the shell with a success message. It waits for the child
 *             process to complete if it is the parent process.
 */
void execute_command(char *command)
{
    pid_t pid;
    command[strcspn(command, "\n")] = '\0'; /* Remove trailing newline character */

    if (strcmp(command, "exit") == 0)
    {
        printf("Exiting shell.\n");
        exit(EXIT_SUCCESS);
    }
    
    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        /* Child process */
        char **args = malloc(2 * sizeof(char *));
        args[0] = strdup(command);
        args[1] = NULL;
        
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

/**
 *main - Entry point of the program
 *
 *@argc: The number of command-line arguments
 *@argv: An array of command-line argument strings
 *
 *Description: The main function serves as the entry point of the program.
 *             It provides two modes of operation: file mode and interactive
 *             mode. In file mode, if a filename is provided as a command-
 *             line argument, the program opens the file, reads each line,
 *             and executes the commands found in the file. In interactive
 *             mode, the program displays a prompt, reads commands from
 *             standard input, and executes them. The program terminates
 *             gracefully on encountering the end of file (Ctrl+D) in
 *             interactive mode. The execution of commands is handled by
 *             the execute_command function. BUFFER_SIZE is defined to
 *             provide a consistent buffer size.
 *
 *Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
    char *filename = NULL;
    char line[BUFFER_SIZE];
    char *command;

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
            
            command = read_command();
            
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
