#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024  // Max command line length
#define MAX_ARGS 64    // Max arguments

// Function to parse the command line into arguments
void parse_command(char *line, char **args) {
    int i = 0;
    args[i] = strtok(line, " \t\n");  // Split by space, tab, newline
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char cwd[1024];  // For pwd

    while (1) {
        printf("$ ");  // Shell prompt
        fflush(stdout);

        // Read command
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            break;  // EOF (Ctrl+D)
        }

        // Skip empty lines
        if (strlen(line) <= 1) continue;

        // Parse the command
        parse_command(line, args);

        if (args[0] == NULL) continue;

        // Built-in: exit
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        // Built-in: cd
        else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd");
                }
            }
        }
        // Built-in: pwd
        else if (strcmp(args[0], "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("pwd");
            }
        }
        // External commands
        else {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
            } else if (pid == 0) {  // Child
                if (execvp(args[0], args) == -1) {
                    perror("exec");
                }
                exit(EXIT_FAILURE);
            } else {  // Parent
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }

    printf("Shell exiting...\n");
    return 0;
}
