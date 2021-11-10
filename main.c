#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define LOG "signal_log.txt"

static void sighandler(int signo) {
    // SIGINT Case
    if (signo == SIGINT) {
        // Opening File
        int fd = open(LOG, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd == -1) {
            printf("Error opening %s\n", LOG);
            return;
        }

        // Writing To File
        char msg[] = "Program exited due to SIGINT\n";
        int err = write(fd, msg, sizeof(msg));
        if (err == -1) {
            printf("Error writing to %s\n", LOG);
        }

        // Closing File And Exiting
        close(fd);
        exit(0);
    }

    // SIGUSR1 Case
    if (signo == SIGUSR1) {
        printf("ppid: %d\n", getppid());
        return;
    }
}

int main() {
    // Signal Catching
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    // Forever Loop
    while (1) {
        printf("pid: %d\n", getpid());
        sleep(1);
    }

    // End Of Function
    return 0;
}
