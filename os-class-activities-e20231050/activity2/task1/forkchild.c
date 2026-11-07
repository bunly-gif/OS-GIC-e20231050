#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        fflush(stdout);

        sleep(30);

        printf("Child: executing ls -la...\n");
        fflush(stdout);

        execlp("ls", "ls", "-la", (char *)NULL);

        // This runs only if execlp fails
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }

        printf("Parent: child process finished. Done.\n");
    }

    return 0;
}
