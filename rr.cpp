#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <queue>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

bool compareArrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareId(Process p1, Process p2) {
    return p1.id < p2.id;
}

int main() {

    int n;
    int tq;
    struct Process processes[50];
  
    int totalIdleTime = 0;
    int tempBurst[50];
    int index;

    cout << "Enter the number of processes: ";
    cin >> n;
    
    cout << "Enter arrival time of processes " << ": ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].arrivalTime;
    }
    
    cout << "Enter burst time of processes " << ": ";
    for (int i =0; i<n; i++) {
        cin >> processes[i].burstTime;
        tempBurst[i] = processes[i].burstTime;
        processes[i].id = i ;
    }
    cout << endl;
    cout << "Enter time quantum: ";
    cin >> tq;
    sort(processes, processes + n, compareArrival);

    queue<int> q;
    int currentTime = 0;
    q.push(0);
    int completed = 0;
    int check[50];

    for(int i =0;i<50;i++){
        check[i]=0;
    }
    check[0] = 1;

    while (completed != n) {
        index = q.front();
        q.pop();

        if (tempBurst[index] == processes[index].burstTime) {
            processes[index].startTime = max(currentTime, processes[index].arrivalTime);
            totalIdleTime += processes[index].startTime - currentTime;
            currentTime = processes[index].startTime;
        }

        if (tempBurst[index] - tq > 0) {
            tempBurst[index] -= tq;
            currentTime += tq;
        } else {
            currentTime += tempBurst[index];
            tempBurst[index] = 0;
            completed++;

            processes[index].completionTime = currentTime;
            processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
            processes[index].waitingTime = processes[index].turnaroundTime - processes[index].burstTime;
      

           
        }

        for (int i = 1; i < n; i++) {
            if (tempBurst[i] > 0 && processes[i].arrivalTime <= currentTime && check[i] == 0) {
                q.push(i);
                check[i] = 1;
            }
        }

        if (tempBurst[index] > 0) {
            q.push(index);
        }

        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (tempBurst[i] > 0) {
                    q.push(i);
                    check[i] = 1;
                    break;
                }
            }
        }
    }

    sort(processes, processes + n, compareId);
    cout << endl;
    cout << "ProcessNo\t" << "Arrival\t\t" << "Burst\t" << "Completion\t" << "TurnAround\t" << "Waiting\t" << "\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "\t\t\t" << processes[i].arrivalTime << "\t\t\t" << processes[i].burstTime << "\t\t\t"
             << processes[i].completionTime << "\t\t\t" << processes[i].turnaroundTime << "\t\t\t" << processes[i].waitingTime
             << "\t\t" <<  "\n" << endl;
    }
    return 0;
}