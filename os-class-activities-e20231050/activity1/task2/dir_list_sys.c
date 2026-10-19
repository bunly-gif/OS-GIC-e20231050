
/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];

    DIR *dir = opendir(".");
    if (dir == NULL) {
        write(2, "Error opening directory\n", 24);
        return 1;
    }

    write(1, "Name                           Size (bytes)\n", 45);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        struct stat st;

        if (stat(entry->d_name, &st) == -1) {
            continue;
        }

        int len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n",
                           entry->d_name, (long)st.st_size);

        if (len > 0) {
            write(1, buffer, strlen(buffer));
        }
    }

    closedir(dir);
    return 0;
}
