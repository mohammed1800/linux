#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void copyFile(const char* sourceFile, const char* destinationFile) {
    // Open the source file for reading
    int sourceFileDescriptor = open(sourceFile, O_RDONLY);
    if (sourceFileDescriptor == -1) {
        perror("Error opening source file");
        return;
    }

    // Open or create the destination file for writing
    int destinationFileDescriptor = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (destinationFileDescriptor == -1) {
        perror("Error opening destination file");
        close(sourceFileDescriptor);
        return;
    }

    // Buffer to read and write data
    char buffer[4096];
    ssize_t bytesRead, bytesWritten;

    // Read from the source and write to the destination
    while ((bytesRead = read(sourceFileDescriptor, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(destinationFileDescriptor, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFileDescriptor);
            close(destinationFileDescriptor);
            return;
        }
    }

    // Close the file descriptors
    close(sourceFileDescriptor);
    close(destinationFileDescriptor);

    std::cout << "File copy successful\n";
}

int main() {
    const char* sourceFile = "source.txt"; // Change this to your source file
    const char* destinationFile = "destination.txt"; // Change this to your destination file

    // Fork a child process
    pid_t childPid = fork();

    if (childPid == -1) {
        perror("Error forking process");
        return 1;
    }

    if (childPid == 0) {
        // This is the child process
        copyFile(sourceFile, destinationFile);
    } else {
        // This is the parent process
        // Wait for the child process to finish
        waitpid(childPid, nullptr, 0);
    }

    return 0;
}
