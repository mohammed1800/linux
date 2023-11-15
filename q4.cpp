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

void get_cpu_type() {
    std::cout << "CPU Type:\n";
    
    // Use popen to capture the output of the lscpu command
    FILE* fp = popen("lscpu | grep 'Model name'", "r");
    if (fp == nullptr) {
        std::cerr << "Error executing lscpu command\n";
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
        std::cout << buffer;
    }

    pclose(fp);
    print_separator();
}

void get_cpu_info() {
    std::cout << "CPU Information:\n";

    // Use popen to capture the output of the lscpu command
    FILE* fp = popen("lscpu", "r");
    if (fp == nullptr) {
        std::cerr << "Error executing lscpu command\n";
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
    get_cpu_type();
    get_cpu_info();

    return 0;
}
