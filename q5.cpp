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
