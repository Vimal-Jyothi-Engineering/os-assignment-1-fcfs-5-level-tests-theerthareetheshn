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

    // Sort by arrival time (stable)
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

    for(int i = 0; i < n; i++) {

        // If CPU is idle, jump to arrival time
        if(currentTime < p[i].arrival) {
            currentTime = p[i].arrival;
        }

        // Waiting time
        p[i].waiting = currentTime - p[i].arrival;

        // Execute process
        currentTime += p[i].burst;

        // Turnaround time
        p[i].turnaround = currentTime - p[i].arrival;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    // EXACT REQUIRED FORMAT

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].turnaround);

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
