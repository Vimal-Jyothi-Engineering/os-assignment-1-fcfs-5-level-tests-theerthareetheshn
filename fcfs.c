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

    for(int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    // Sort by arrival time only - no tie-breaking needed
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int completionTime[n];
    float totalWT = 0, totalTAT = 0;

    // First process
    if(p[0].arrival > 0) {
        p[0].waiting = 0;
        completionTime[0] = p[0].arrival + p[0].burst;
    } else {
        p[0].waiting = 0;
        completionTime[0] = p[0].burst;
    }
    p[0].turnaround = completionTime[0] - p[0].arrival;
    totalWT += p[0].waiting;
    totalTAT += p[0].turnaround;

    // Remaining processes
    for(int i = 1; i < n; i++) {
        if(completionTime[i-1] < p[i].arrival) {
            p[i].waiting = 0;
            completionTime[i] = p[i].arrival + p[i].burst;
        } else {
            p[i].waiting = completionTime[i-1] - p[i].arrival;
            completionTime[i] = completionTime[i-1] + p[i].burst;
        }
        p[i].turnaround = completionTime[i] - p[i].arrival;
        
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
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
