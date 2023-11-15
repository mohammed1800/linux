#include <iostream>
#include <vector>
#include <algorithm>

struct MemoryBlock {
    int blockId;
    int size;
    bool allocated;
};

void firstFit(std::vector<MemoryBlock>& memory, int processId, int processSize) {
    for (auto& block : memory) {
        if (!block.allocated && block.size >= processSize) {
            block.allocated = true;
            std::cout << "Process " << processId << " allocated to Memory Block " << block.blockId << " using First-Fit\n";
            return;
        }
    }
    std::cout << "Process " << processId << " cannot be allocated using First-Fit\n";
}

void bestFit(std::vector<MemoryBlock>& memory, int processId, int processSize) {
    auto bestFitBlock = memory.end();

    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if (!it->allocated && it->size >= processSize) {
            if (bestFitBlock == memory.end() || it->size < bestFitBlock->size) {
                bestFitBlock = it;
            }
        }
    }

    if (bestFitBlock != memory.end()) {
        bestFitBlock->allocated = true;
        std::cout << "Process " << processId << " allocated to Memory Block " << bestFitBlock->blockId << " using Best-Fit\n";
    } else {
        std::cout << "Process " << processId << " cannot be allocated using Best-Fit\n";
    }
}

void worstFit(std::vector<MemoryBlock>& memory, int processId, int processSize) {
    auto worstFitBlock = memory.end();

    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if (!it->allocated && it->size >= processSize) {
            if (worstFitBlock == memory.end() || it->size > worstFitBlock->size) {
                worstFitBlock = it;
            }
        }
    }

    if (worstFitBlock != memory.end()) {
        worstFitBlock->allocated = true;
        std::cout << "Process " << processId << " allocated to Memory Block " << worstFitBlock->blockId << " using Worst-Fit\n";
    } else {
        std::cout << "Process " << processId << " cannot be allocated using Worst-Fit\n";
    }
}

int main() {
    int numBlocks, numProcesses;

    std::cout << "Enter the number of memory blocks: ";
    std::cin >> numBlocks;

    std::vector<MemoryBlock> memory(numBlocks);

    for (int i = 0; i < numBlocks; ++i) {
        memory[i].blockId = i + 1;
        std::cout << "Enter size for Memory Block " << memory[i].blockId << ": ";
        std::cin >> memory[i].size;
        memory[i].allocated = false;
    }

    std::cout << "Enter the number of processes: ";
    std::cin >> numProcesses;

    for (int i = 0; i < numProcesses; ++i) {
        int processSize;
        std::cout << "Enter size for Process " << i + 1 << ": ";
        std::cin >> processSize;

        // Use the three allocation strategies
        firstFit(memory, i + 1, processSize);
        bestFit(memory, i + 1, processSize);
        worstFit(memory, i + 1, processSize);
    }

    return 0;
}

/*the output:
Enter the number of memory blocks: 3
Enter size for Memory Block 1: 128
Enter size for Memory Block 2: 64
Enter size for Memory Block 3: 8
Enter the number of processes: 3
Enter size for Process 1: 2
Process 1 allocated to Memory Block 1 using First-Fit
Process 1 allocated to Memory Block 3 using Best-Fit
Process 1 allocated to Memory Block 2 using Worst-Fit
Enter size for Process 2: 4
Process 2 cannot be allocated using First-Fit
Process 2 cannot be allocated using Best-Fit
Process 2 cannot be allocated using Worst-Fit
Enter size for Process 3: 8
Process 3 cannot be allocated using First-Fit
Process 3 cannot be allocated using Best-Fit
Process 3 cannot be allocated using Worst-Fit
*/
