#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "example.txt"
#define BUFFER_SIZE 100

int main() {
    int fd;
    ssize_t bytes_written, bytes_read;
    char write_buffer[] = "Hello, this is a test for UNIX system calls!";
    char read_buffer[BUFFER_SIZE];

    // 1. Create and open the file
    fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating/opening the file");
        exit(EXIT_FAILURE);
    }
    printf("File created and opened for writing.\n");

    // 2. Write to the file
    bytes_written = write(fd, write_buffer, sizeof(write_buffer) - 1);
    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Wrote %zd bytes to the file.\n", bytes_written);

    // 3. Close the file
    if (close(fd) == -1) {
        perror("Error closing the file after writing");
        exit(EXIT_FAILURE);
    }
    printf("File closed after writing.\n");

    // 4. Reopen the file for reading
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening the file for reading");
        exit(EXIT_FAILURE);
    }
    printf("File opened for reading.\n");

    // 5. Read from the file
    bytes_read = read(fd, read_buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Error reading from the file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    read_buffer[bytes_read] = '\0'; // Null-terminate the read data
    printf("Read %zd bytes from the file: %s\n", bytes_read, read_buffer);

    // 6. Close the file
    if (close(fd) == -1) {
        perror("Error closing the file after reading");
        exit(EXIT_FAILURE);
    }
    printf("File closed after reading.\n");

    // 7. Delete the file
    if (unlink(FILENAME) == -1) {
        perror("Error deleting the file");
        exit(EXIT_FAILURE);
    }
    printf("File deleted.\n");

    return 0;
}

