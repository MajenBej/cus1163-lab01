#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;
    ssize_t bytes_written;

    printf("Creating file %s \n", filename);
    printf("Written Content %s \n", content);

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open failed");
        return -1;
    }

    printf("File Descripter %d \n", fd);

    bytes_written = write(fd, content, strlen(content));

   if (bytes_written == -1) {
        perror("writing failed");
        close(fd);
        return -1;
   }

   printf("Successfully created/wrote file %s with bytes %zd", filename, bytes_written);

   fd = close(fd);

   if (fd == -1) {
        return -1;
   }

    printf("File closed successfully!");

    return 0;
}

int read_file_contents(const char *filename) {

    int fd;
    char buffer[1024];
    ssize_t bytes_read; 

    printf("%s is being read!\n", filename);

    fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open failed!");
        return -1;
    }

    printf("File Descriptor %d \n", fd);
    printf("----- FILE CONTENTS -----\n");


    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; 
        printf("%s", buffer); 
    }

    if (bytes_read == -1) {
        perror("failed to read bytes!");
        return -1;
    }

    printf("\n----- END OF FILE -----\n");

   fd = close(fd);

   if (fd == -1) {
    perror("failed to close file");
    return -1;
   }

   printf("File was clsoed successfully!");
    return 0;
}
