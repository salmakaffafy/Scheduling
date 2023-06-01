//
//  main.cpp
//  MLFQ
//
//  Created by Salma Kaffafy on 14/05/2023.
//


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct process {
    double burst_time;
    double arrival_time;
    double time_quantum = 2;
    double waiting_time;
    double TAT;
    double response_time;
    double start_time;
    double end_time;
    bool status_done = false;
    double remaining = burst_time;
};

vector<process> MLFQ(vector<process> p);
vector<process> sort_arrival(vector<process> proc);

int main()
{
    srand(time(nullptr));

    vector<process> processes;
    int num_processes;
    cout << "Enter the number of processes to generate: ";
    cin >> num_processes;

    // Generate random arrival times and burst times for each process
    for (int i = 0; i < num_processes; i++) {
        process proc{};
        proc.arrival_time = rand() % 100; // Generate random arrival time between 0 and 99
        proc.burst_time = rand() % 20 + 1; // Generate random burst time between 1 and 20
        proc.remaining = proc.burst_time;
        processes.push_back(proc);
    }

    processes = MLFQ(processes);

    double waitingTime = 0;
    double responseTime = 0;
    double turnaroundTime = 0;

    cout << "Process Table:" << endl;
    cout << setw(10) << left << "Process" << setw(15) << "Turnaround Time" << setw(15) << "Response Time" << setw(15) << "Wait Time" << endl;

    for (int i = 0; i < processes.size(); i++) {
        cout << setw(10) << left << i << setw(15) << processes[i].TAT << setw(15) << processes[i].response_time << setw(15) << processes[i].waiting_time << endl;
        waitingTime += processes[i].waiting_time;
        responseTime += processes[i].response_time;
        turnaroundTime += processes[i].TAT;
    }

    cout << "Average waiting time: " << waitingTime / processes.size() << endl;
    cout << "Average response time: " << responseTime / processes.size() << endl;
    cout << "Average turnaround time: " << turnaroundTime / processes.size() << endl;

    return 0;
}

vector<process> MLFQ(vector<process> p)
{

    //q1 --> RR, n = 8 - Highest Priority
    //q2 --> RR, n = 16 - Medium Priority
    //q3 --> FCFS - Lowest Priority
    
    vector <process> q1, q2, q3;
    vector <process> Finished_Processes;
    int clock = 0;

 

    for (int i = 0; i < p.size(); i++)
    {
        q1.push_back(p[i]);
    }

    q1 = sort_arrival(q1);
    clock = q1[0].arrival_time;
    while ((!q1.empty()) || (!q2.empty()) || (!q3.empty()))
    {
        while (!q1.empty())
        {
            
            if (q1[0].arrival_time <= clock) {
                if (q1[0].remaining <= 8)
                {
                    if (q1[0].remaining == q1[0].burst_time)
                        q1[0].start_time = clock;

                    q1[0].end_time = clock + q1[0].remaining;
                    clock += q1[0].remaining;
                    q1[0].remaining = 0;
                    q1[0].TAT = q1[0].end_time - q1[0].arrival_time;
                    q1[0].waiting_time = q1[0].TAT - q1[0].burst_time;
                    q1[0].response_time = q1[0].start_time - q1[0].arrival_time;
                    Finished_Processes.push_back(q1[0]);
                    q1.erase(q1.begin() + 0);

                }
                else if (q1[0].remaining > 8)
                {
                    q1[0].start_time = clock;
                    clock += 8;
                    q1[0].remaining -= 8;
                    q1[0].response_time = q1[0].start_time - q1[0].arrival_time;

                    q2.push_back(q1[0]);
                    q1.erase(q1.begin() + 0);
                }
            }
            else
                clock++;
        }

        while (!q2.empty())
        {

            if (q2[0].remaining <= 16)
            {
                q2[0].end_time = clock + q2[0].remaining;
                clock += q2[0].remaining;
                q2[0].remaining = 0;
                q2[0].TAT = q2[0].end_time - q2[0].arrival_time;
                q2[0].waiting_time = q2[0].TAT - q2[0].burst_time;
                Finished_Processes.push_back(q2[0]);
                q2.erase(q2.begin() + 0);
            }
            else if (q2[0].remaining > 16)
            {
                clock += 16;
                q2[0].remaining -= 16;

                q3.push_back(q2[0]);
                q2.erase(q2.begin() + 0);
            }

        }

        while (!q3.empty())
        {
            q3[0].end_time = clock + q3[0].remaining;
            clock += q3[0].remaining;

            q3[0].TAT = q3[0].end_time - q3[0].arrival_time;
            q3[0].waiting_time = q3[0].TAT - q3[0].burst_time;

            Finished_Processes.push_back(q3[0]);
            q3.erase(q3.begin() + 0);
        }
    }
    return Finished_Processes;
}


vector<process> sort_arrival(vector<process> proc) {

    vector<process> result;
    int index = 0;
    int smallest = 1000;
    process chosen;
    for (int i = 0; i < proc.size(); i++)
    {

        for (int j = 0; j < proc.size(); j++)
        {
            if ((proc[j].arrival_time < smallest) && (proc[j].status_done == false)) {
                smallest = proc[j].arrival_time;
                chosen = proc[j];
                index = j;

            }
        }
        result.push_back(chosen);
        proc[index].status_done = true;
        smallest = 1000;
    }
    return result;
}
