#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

void calculateTimes(std::vector<Process>& processes) {
    processes[0].completionTime = processes[0].arrivalTime + processes[0].burstTime;
    processes[0].turnaroundTime = processes[0].completionTime - processes[0].arrivalTime;
    processes[0].waitingTime = processes[0].turnaroundTime - processes[0].burstTime;

    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].completionTime = processes[i - 1].completionTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
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

    // Sort processes based on arrival time
    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    // Sort processes based on burst time
    std::sort(processes.begin(), processes.end(), compareBurstTime);

    calculateTimes(processes);
    displayResults(processes);

    return 0;
}
/*the output:
Enter the number of processes: 3
Enter arrival time and burst time for each process:
Process 1:
Arrival Time: 2
Burst Time: 4
Process 2:
Arrival Time: 5
Burst Time: 3
Process 3:
Arrival Time: 1
Burst Time: 3
Process Arrival Time    Burst Time      Completion Time Turnaround Time Waiting Time
3       1               3               4               3               0
2       5               3               7               2               -1
1       2               4               11              9               5
*/
