#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {

        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }

        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;

        current_time += p[i].burst;

        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    printf("Waiting Time: ");
    for (int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].waiting);
    }

    printf("\nTurnaround Time: ");
    for (int i = 0; i < n; i++) {
        printf("%s %d ", p[i].pid, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f ", total_wt / n);
    printf("Average Turnaround Time: %.2f", total_tat / n);

    return 0;
}
