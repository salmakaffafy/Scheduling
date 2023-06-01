//
//  main.cpp
//  FCFS
//
//

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool isCompleted;
};



void FCFS_Scheduler(process proc[], int n) {
    int i, j;
    process temp;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
 
    for (i = 0; i < n; i++) {
        if (i == 0) {
            proc[i].start_time = proc[i].arrival_time;
            proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
            proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
            proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
            proc[i].response_time = proc[i].start_time - proc[i].arrival_time;
        } else {
            proc[i].start_time = proc[i - 1].completion_time;
            proc[i].completion_time = proc[i].start_time + proc[i].burst_time;
            proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
            proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
            proc[i].response_time = proc[i].start_time - proc[i].arrival_time;
        }
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (i = 0; i < n; i++) {
        avg_waiting_time += proc[i].waiting_time;
        avg_turnaround_time += proc[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    float avg_response_time = 0;
    for (i = 0; i < n; i++) {
        avg_response_time += proc[i].response_time;
    }
    avg_response_time /= n;

    cout << "First Come First Serve Scheduling" << endl;
    cout << "Process ID\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time" << endl;
    for (i = 0; i < n; i++) {
        cout << proc[i].pid << "\t\t" << proc[i].arrival_time << "\t\t" << proc[i].burst_time << "\t\t" << proc[i].start_time << "\t\t" << proc[i].completion_time << "\t\t" << proc[i].turnaround_time << "\t\t" << proc[i].waiting_time << "\t\t" << proc[i].response_time << endl;
    }
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Response Time: " << avg_response_time << endl;
}


int main() {
    
    int n = 1000, i;
    process proc[n];
    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        proc[i].arrival_time = i+5;
        proc[i].burst_time = i+10;
    }
    FCFS_Scheduler(proc, n);

    return 0;
}
