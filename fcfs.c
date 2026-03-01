#include <stdio.h>
#include <string.h>

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

    for(int i = 0; i < n; i++)
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);

    // Sort by arrival
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    float totalWT = 0, totalTAT = 0;

    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;

    totalWT += p[0].waiting;
    totalTAT += p[0].turnaround;

    for(int i = 1; i < n; i++) {
        p[i].waiting = p[i-1].waiting + p[i-1].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;

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
