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

    // Sort by arrival time
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j + 1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    float totalWT = 0, totalTAT = 0;
    int burstSum = 0;

    for(int i = 0; i < n; i++) {
        p[i].waiting = burstSum;
        burstSum += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
        
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("Waiting Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].waiting);
    }

    printf("\nTurnaround Time: ");
    for(int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f ", totalWT / n);
    printf("Average Turnaround Time: %.2f", totalTAT / n);

    return 0;
}
