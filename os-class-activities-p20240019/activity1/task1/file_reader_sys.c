/* file_reader_sys.c */
#include <fcntl.h>   // open()
#include <unistd.h>  // read(), write(), close()
#include <stdio.h>   // perror()

int main() {
    char buffer[256];

    // 1. Open file for reading
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // 2. Read and display content
    int bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead); // 1 = stdout
    }

    // 3. Close file
    close(fd);

    return 0;
}