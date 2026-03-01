#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

// Comparator for sorting by arrival time
int compare(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->arrival == p2->arrival)
        return 0;
    return p1->arrival - p2->arrival;
}

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].id, &p[i].arrival, &p[i].burst);
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    // 🔥 SORT BY ARRIVAL TIME (THIS FIXES LEVEL 3 & 4)
    qsort(p, n, sizeof(Process), compare);

    int currentTime = 0;
    float totalWT = 0.0, totalTAT = 0.0;

    for (int i = 0; i < n; i++) {

        // If CPU is idle
        if (currentTime < p[i].arrival) {
            currentTime = p[i].arrival;
        }

        // Waiting time
        p[i].waiting = currentTime - p[i].arrival;

        // Turnaround time
        p[i].turnaround = p[i].waiting + p[i].burst;

        // Advance time
        currentTime += p[i].burst;

        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    // Output per process
    for (int i = 0; i < n; i++) {
        printf("%s %d %d %d %d\n",
               p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
