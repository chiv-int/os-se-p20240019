/* file_creator_sys.c */
#include <fcntl.h>   // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>  // write(), close()
#include <string.h>  // strlen()
#include <stdio.h>   // perror()

int main() {
    // 1. Open/create file
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // 2. Write to file
    char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));

    // 3. Close file
    close(fd);

    // 4. Print message to terminal (fd = 1 is stdout)
    char *msg = "File created successfully!\n";
    write(1, msg, strlen(msg));

    return 0;
}