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
/* the output
Kernel Version:
Linux Check 5.4.0-1093-gcp #102~18.04.1-Ubuntu SMP Sat Oct 29 06:35:49 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
----------------------------------------
CPU Type:
Model name:                      Intel(R) Xeon(R) CPU @ 2.00GHz
----------------------------------------
CPU Information:
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Address sizes:                   46 bits physical, 48 bits virtual
Byte Order:                      Little Endian
CPU(s):                          8
On-line CPU(s) list:             0-7
Vendor ID:                       GenuineIntel
Model name:                      Intel(R) Xeon(R) CPU @ 2.00GHz
CPU family:                      6
Model:                           85
Thread(s) per core:              2
Core(s) per socket:              4
Socket(s):                       1
Stepping:                        3
BogoMIPS:                        3999.99
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx pdpe1gb rdtscp lm constant_tsc rep_good nopl xtopology nonstop_tsc cpuid tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch invpcid_single pti ssbd ibrs ibpb stibp fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm mpx avx512f avx512dq rdseed adx smap clflushopt clwb avx512cd avx512bw avx512vl xsaveopt xsavec xgetbv1 xsaves arat md_clear arch_capabilities
Hypervisor vendor:               KVM
Virtualization type:             full
L1d cache:                       128 KiB (4 instances)
L1i cache:                       128 KiB (4 instances)
L2 cache:                        4 MiB (4 instances)
L3 cache:                        38.5 MiB (1 instance)
NUMA node(s):                    1
NUMA node0 CPU(s):               0-7
Vulnerability Itlb multihit:     Not affected
Vulnerability L1tf:              Mitigation; PTE Inversion
Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT Host state unknown
Vulnerability Meltdown:          Mitigation; PTI
Vulnerability Mmio stale data:   Vulnerable: Clear CPU buffers attempted, no microcode; SMT Host state unknown
Vulnerability Retbleed:          Mitigation; IBRS
Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled via prctl and seccomp
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:        Mitigation; IBRS, IBPB conditional, RSB filling, PBRSB-eIBRS Not affected
Vulnerability Srbds:             Not affected
Vulnerability Tsx async abort:   Mitigation; Clear CPU buffers; SMT Host state unknown
----------------------------------------
*/
