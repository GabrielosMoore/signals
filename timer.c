#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t alarm_triggered = 0; // Flag to indicate alarm triggered
volatile sig_atomic_t running = 1;           // Flag to indicate program running
int alarm_count = 0;                         // Count of alarms triggered

// Signal handler for SIGALRM
void handle_alarm(int signum) {
    printf("Hello World!\n");
    alarm_triggered = 1;  // Set flag indicating alarm has triggered
    alarm_count++;        // Increment alarm count
}

// Signal handler for SIGINT
void handle_sigint(int signum) {
    running = 0;  // Stop the loop when SIGINT is received
}

int main() {
    // Register signal handlers
    signal(SIGALRM, handle_alarm);
    signal(SIGINT, handle_sigint);

    // Set an initial alarm for 1 second to keep track of time
    alarm(1);
    time_t start_time = time(NULL); // Record start time

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

    time_t end_time = time(NULL); // Record end time
    printf("Total time executing: %ld seconds\n", end_time - start_time);
    printf("Total alarms delivered: %d\n", alarm_count);
    return 0;
}
