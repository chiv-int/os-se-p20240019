/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>   // for snprintf()

int main() {
    char buffer[512];

    // 1. Open current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // 2. Print header
    char *header1 = "Filename                      Size (bytes)\n";
    char *header2 = "-------------------------------- ----------\n";
    write(1, header1, strlen(header1));
    write(1, header2, strlen(header2));

    // 3. Loop through directory
    while ((entry = readdir(dir)) != NULL) {

        // 4. Get file info
        if (stat(entry->d_name, &fileStat) == 0) {

            // 5. Format into buffer
            int len = snprintf(buffer, sizeof(buffer),
                               "%-30s %10ld\n",
                               entry->d_name,
                               fileStat.st_size);

            // 6. Print using write()
            write(1, buffer, len);
        }
    }

    // 7. Close directory
    closedir(dir);

    return 0;
}