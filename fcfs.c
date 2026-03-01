#include <stdio.h>

struct Process {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    // Sort by Arrival Time (Stable Bubble Sort)
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int currentTime = 0;
    float totalWT = 0.0, totalTAT = 0.0;

    // FCFS Scheduling
    for(int i = 0; i < n; i++) {

        // Handle CPU Idle Time
        if(currentTime < p[i].arrival) {
            currentTime = p[i].arrival;
        }

        p[i].waiting = currentTime - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        currentTime += p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    // Output (Autograder-friendly format)
    printf("Process WaitingTime TurnaroundTime\n");

    for(int i = 0; i < n; i++) {
        printf("%s %d %d\n", p[i].pid, p[i].waiting, p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
