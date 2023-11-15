#include <iostream>
#include <vector>
#include <pthread.h>

// Structure to hold data for each thread
struct ThreadData {
    std::vector<int> numbers;
    int sum;
};

// Function to be executed by each thread
void* sumThread(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    data->sum = 0;

    // Calculate the sum of the numbers in the sub-list
    for (int num : data->numbers) {
        data->sum += num;
    }

    return nullptr;
}

int main() {
    int n;

    // Get the number of elements in the list
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    // Create the list of numbers
    std::vector<int> numbers(n);
    std::cout << "Enter " << n << " numbers:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    // Divide the list into two sub-lists
    int mid = n / 2;
    std::vector<int> firstHalf(numbers.begin(), numbers.begin() + mid);
    std::vector<int> secondHalf(numbers.begin() + mid, numbers.end());

    // Create thread data structures
    ThreadData data1{firstHalf, 0};
    ThreadData data2{secondHalf, 0};

    // Create thread handles
    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, nullptr, sumThread, &data1);
    pthread_create(&thread2, nullptr, sumThread, &data2);

    // Wait for threads to finish
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    // Calculate the total sum
    int totalSum = data1.sum + data2.sum;

    // Display the result
    std::cout << "Sum of the numbers: " << totalSum << std::endl;

    return 0;
}

/*the output:
Enter the number of elements: 3
Enter 3 numbers:
4
3
6
Sum of the numbers: 13
*/
