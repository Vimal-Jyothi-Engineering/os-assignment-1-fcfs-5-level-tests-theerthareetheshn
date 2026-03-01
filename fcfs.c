#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Process {
    char pid[10];
    int pid_num;      // numeric part of PID for sorting
    int arrival;
    int burst;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    scanf("%d", &n);

    struct Process p[n];

    // Read input
    for(int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].pid_num = atoi(p[i].pid + 1);  // extract number from "P1"
    }

    // Sort by arrival time, if tie sort by PID number
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j+1].arrival ||
               (p[j].arrival == p[j+1].arrival &&
                p[j].pid_num > p[j+1].pid_num)) {

                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    for(int i = 0; i < n; i++) {

        if(currentTime < p[i].arrival)
            currentTime = p[i].arrival;

        p[i].waiting = currentTime - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        currentTime += p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].turnaround);

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f", totalTAT / n);

    return 0;
}
