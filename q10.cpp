#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime; // Remaining time for execution
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

struct CompareProcesses {
    bool operator()(const Process& a, const Process& b) {
        return a.remainingTime > b.remainingTime;
    }
};

void calculateTimes(std::vector<Process>& processes) {
    std::priority_queue<Process, std::vector<Process>, CompareProcesses> processQueue;

    int currentTime = 0; // Current time of execution

    for (size_t i = 0; i < processes.size(); ++i) {
        while (!processQueue.empty() && processQueue.top().arrivalTime <= currentTime) {
            Process currentProcess = processQueue.top();
            processQueue.pop();

            int executionTime = std::min(currentProcess.remainingTime, processes[i].arrivalTime - currentTime);
            currentTime += executionTime;
            currentProcess.remainingTime -= executionTime;

            if (currentProcess.remainingTime > 0) {
                processQueue.push(currentProcess);
            } else {
                currentProcess.completionTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
            }
        }

        if (i < processes.size()) {
            processes[i].remainingTime = processes[i].burstTime;
            processQueue.push(processes[i]);
        }
    }
}

void displayResults(const std::vector<Process>& processes) {
    std::cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    
    for (const auto& process : processes) {
        std::cout << process.processId << "\t" << process.arrivalTime << "\t\t"
                  << process.burstTime << "\t\t" << process.completionTime << "\t\t"
                  << process.turnaroundTime << "\t\t" << process.waitingTime << "\n";
    }
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    std::cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].processId = i + 1;
        std::cout << "Process " << processes[i].processId << ":\n";
        std::cout << "Arrival Time: ";
        std::cin >> processes[i].arrivalTime;
        std::cout << "Burst Time: ";
        std::cin >> processes[i].burstTime;
    }

    calculateTimes(processes);
    displayResults(processes);

    return 0;
}

/*the output:
Enter the number of processes: 3
Enter arrival time and burst time for each process:
Process 1:
Arrival Time: 3
Burst Time: 5
Process 2:
Arrival Time: 2
Burst Time: 4
Process 3:
Arrival Time: 3
Burst Time: 4
Process Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
1       3               5               0               0               0
2       2               4               0               0               0
3       3               4               0               0               0*/
