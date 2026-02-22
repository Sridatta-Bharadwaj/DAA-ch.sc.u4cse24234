#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id, profit, deadline;
} Job;

void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void sortByProfit(Job jobs[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (jobs[j].profit < jobs[j + 1].profit)
                swap(&jobs[j], &jobs[j + 1]);
}

void jobSequencing(Job jobs[], int n) {
    sortByProfit(jobs, n);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    int slot[MAX];
    int result[MAX];
    memset(slot, -1, sizeof(slot));

    int totalProfit = 0, count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                result[count++] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Selected Jobs (in slot order):\n");
    printf("Slot\tJob ID\tProfit\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1)
            printf("%d\tJ%d\t%d\n", i + 1, jobs[slot[i]].id, jobs[slot[i]].profit);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
    printf("Number of Jobs Scheduled: %d\n", count);
}

int main() {
    Job jobs[] = {
        {1,  36, 5},
        {2,  21, 8},
        {3,  28, 3},
        {4,  19, 4},
        {5,  21, 4},
        {6,  13, 9},
        {7,  28, 12},
        {8,  25, 14},
        {9,  18, 2},
        {10, 20, 7},
        {11, 27, 5},
        {12, 22, 1},
        {13, 14, 6},
        {14, 26, 3}
    };
    int n = 14;

    printf("Job Sequencing with Deadlines\n");
    printf("==============================\n");
    printf("Job\tProfit\tDeadline\n");
    for (int i = 0; i < n; i++)
        printf("J%d\t%d\t%d\n", jobs[i].id, jobs[i].profit, jobs[i].deadline);
    printf("\n");

    jobSequencing(jobs, n);

    return 0;
}