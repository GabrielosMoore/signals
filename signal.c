#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t alarm_triggered = 0;  // Flag to indicate alarm triggered
volatile sig_atomic_t running = 1;            // Flag to indicate program running

// Signal handler for SIGALRM
void handle_alarm(int signum) {
    printf("Hello World!\n");
    alarm_triggered = 1;  // Set flag indicating alarm has triggered
}

// Signal handler for SIGINT
void handle_sigint(int signum) {
    running = 0;  // Stop the loop when SIGINT is received
}

int main() {
    // Register signal handlers
    signal(SIGALRM, handle_alarm);
    signal(SIGINT, handle_sigint);

    // Set an initial alarm for 5 seconds
    alarm(5);

    while (running) {
        // Check if alarm has triggered
        if (alarm_triggered) {
            printf("Turing was right!\n");
            alarm_triggered = 0; // Reset the flag
            alarm(5); // Reset the alarm for the next 5 seconds
        }

        // Wait for signals
        pause();  // Efficiently wait for signals to arrive
    }

    return 0;
}
