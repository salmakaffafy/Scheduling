//
//  main.cpp
//  round
//
//  Created by Salma Kaffafy on 13/05/2023.
//


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<time.h>

using namespace std;


struct Process {
    int pid;
    double burst_time;
    double arrival_time;
    double time_quantum = 2;
    double waiting_time;
    double turnaround_time;
    double response_time;
    double start_time;
    double completion_time;
    bool isCompleted=false;
    double remaining = burst_time;
    
};

void RoundRobin(vector<Process>& Vector);

int main()
{

    vector<Process> Vector;

    int gen_num;
    cout << "Enter the number of processes you want to generate: ";
    cin >> gen_num;
    cout << endl;
    while (gen_num < 0 || gen_num > 10000)
    {
        cout << "Invalid range. Please reenter : ";
        cin >> gen_num;
        cout << endl;
    }

    Vector.resize(gen_num);
    for (int i = 0; i < gen_num; i++) {
       
        Vector[i].arrival_time = i+1;
        Vector[i].burst_time = i+2;
        Vector[i].remaining = Vector[i].burst_time;
        Vector[i].pid = i + 1;
    }

    cout << "The vector size is : " << Vector.size() << endl;

    RoundRobin(Vector);

    double sum_waiting_time = 0;
    double sum_TAT = 0;
    double sum_RT = 0;

    
    cout << "Process ID\tTurnaround Time\tResponse Time\tWaiting Time" << endl;
    for (int i = 0; i < Vector.size(); i++)
    {
        
        sum_waiting_time += Vector[i].waiting_time;
        sum_TAT += Vector[i].turnaround_time;
        sum_RT += Vector[i].response_time;
      cout << Vector[i].pid << "\t\t" << Vector[i].turnaround_time << "\t\t" << Vector[i].response_time << "\t\t" << Vector[i].waiting_time << endl;

    }

    double average_waiting_time = sum_waiting_time / (double)Vector.size();
    double average_TAT = sum_TAT / (double)Vector.size();
    double average_RT = sum_RT / (double)Vector.size();

    cout << endl;
    cout << "The average waiting time is : " << fixed << setprecision(2) << average_waiting_time << " ns" << endl;
    cout << "The average Turnaround time is : " << fixed << setprecision(2) << average_TAT << " ns" << endl;
    cout << "The average Response time is : " << fixed << setprecision(2) << average_RT << " ns" << endl;

    return 0;
}

void RoundRobin(vector<Process>& Vector)
{
    double time = 0;

    while (true)
    {
        bool flag = true;
        for (int i = 0; i < Vector.size(); i++)
        {
            if (Vector[i].remaining != 0)
            {
                flag = false;
                break;
            }
        }

        if (flag == true)
            break;

        for (int i = 0; i < Vector.size(); i++)
        {
            if (Vector[i].remaining > 0 && Vector[i].arrival_time <= time)
            {
                Vector[i].isCompleted = false;

                if (Vector[i].remaining > Vector[i].time_quantum)
                {
                    if (Vector[i].remaining == Vector[i].burst_time)
                        Vector[i].start_time = time;
                    time += Vector[i].time_quantum;
                    Vector[i].remaining -= Vector[i].time_quantum;
                }
                else
                {
                    if (Vector[i].remaining == Vector[i].burst_time)
                        Vector[i].start_time = time;
                    time += Vector[i].remaining;
                    Vector[i].completion_time = time;
                    Vector[i].remaining -= Vector[i].remaining;
                    Vector[i].isCompleted = true;

                    Vector[i].turnaround_time = time - Vector[i].arrival_time;
                    Vector[i].waiting_time = Vector[i].turnaround_time - Vector[i].burst_time;
                    Vector[i].response_time = Vector[i].start_time - Vector[i].arrival_time;
                }
            }
            else
                time++;
        }
    }
}
