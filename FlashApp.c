#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        fprintf(stderr, "Flashapp: Usage: %s $DOWNLOAD_LOCATION $UPGRADE_FILE\n", argv[0]);
        return 1;
    }

    // Extract arguments
    const char *download_location = argv[1];
    const char *upgrade_file = argv[2];

    // Construct the command string
    char command[512] = {0};
    if (snprintf(command, sizeof(command), "/usr/bin/mfrUtil -u %s/%s", download_location, upgrade_file) >= sizeof(command)) {
        fprintf(stderr, "Flashapp: Error: Command string too long.\n");
        return 1;
    }

    // Execute the command
    fprintf(stderr, "Flashapp: Command: %s\n", command );
    int ret = system(command);
    if (ret == -1) {
        perror("Flashapp: Error executing command");
        return 1;
    }

    // Check the return status of the executed command
    if (WIFEXITED(ret)) {
        int exit_status = WEXITSTATUS(ret);
        if (exit_status != 0) {
            fprintf(stderr, "Flashapp: Command failed with exit status %d\n", exit_status);
            return exit_status;
        }
    } else {
        fprintf(stderr, "Flashapp: Command terminated abnormally\n");
        return 1;
    }

    printf("Flashapp: Command executed successfully.\n");
    return 0;
}
