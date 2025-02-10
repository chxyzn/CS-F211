#include <stdio.h>
#include <stdlib.h>
#include "process_queue.h"

void read(FILE *f, Process *process);

int main()
{
    FILE *f = fopen("fcfs_input.txt", "r");
    if (f == NULL)
        return 0;

    int n;
    fscanf(f, "%d", &n);
    Process process[n];

    read(f, process);

    int i = 0;
    int time = 0, process_executed = 0;
    Queue *q = createQueue();
    Process *executing_process = NULL;

    while (process_executed < n)
    {
        if (i < n && time == process[i].arrival_time)
            enqueue(q, process[i++]);

        if (executing_process == NULL)
        {
            executing_process = front(q);
            if (executing_process != NULL)
            {
                printf("Process %d started at time %d\n", executing_process->pid, time);
                dequeue(q);
            }
        }

        if (executing_process != NULL && --(executing_process->burst_time) == 0)
        {
            printf("Process %d finished at time %d\n", executing_process->pid, time + 1);
            process_executed++;
            executing_process = NULL;
        }

        time++;
    }
    destroyQueue(q);
}

void read(FILE *f, Process *process)
{
    int tpid, tat, tbt, i = 0;
    while (fscanf(f, "%d %d %d", &tpid, &tat, &tbt) == 3)
    {
        process[i].pid = tpid;
        process[i].arrival_time = tat;
        process[i++].burst_time = tbt;
    }
}