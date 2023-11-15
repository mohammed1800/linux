#include <iostream>
#include <fstream>
#include <cstdlib>

void print_separator() {
    std::cout << "----------------------------------------\n";
}

void get_kernel_info() {
    std::cout << "Kernel Version:\n";
    system("uname -a");
    print_separator();
}

void get_memory_info() {
    std::cout << "Memory Information:\n";
    
    // Use popen to capture the output of the free command
    FILE* fp = popen("free -h", "r");
    if (fp == nullptr) {
        std::cerr << "Error executing free command\n";
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        std::cout << buffer;
    }

    pclose(fp);
    print_separator();
}

int main() {
    get_kernel_info();
    get_memory_info();

    return 0;
}
/* the output
Kernel Version:
Linux Check 5.4.0-1093-gcp #102~18.04.1-Ubuntu SMP Sat Oct 29 06:35:49 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
----------------------------------------
Memory Information:
               total        used        free      shared  buff/cache   available
Mem:           7.8Gi       2.1Gi       3.9Gi        17Mi       1.8Gi       5.4Gi
Swap:             0B          0B          0B
----------------------------------------
*/

