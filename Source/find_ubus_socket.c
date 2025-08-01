#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>  // for PATH_MAX

#define TOP_DIR             "../"
#define UBUS_SOCKET_DIR     TOP_DIR "Scripts/"

int ends_with_sock(const char *filename) {
    const char *ext = ".sock";
    size_t len = strlen(filename);
    size_t ext_len = strlen(ext);
    return len >= ext_len && strcmp(filename + len - ext_len, ext) == 0;
}

// Return a heap-allocated string with the full socket file path, or NULL if not found
char *find_socket_file() {
    char *ubus_socket_path = NULL;
    struct dirent *entry;
    DIR *dp = opendir(UBUS_SOCKET_DIR);

    if (!dp) {
        perror("opendir failed");
        goto exit;
    }

    while ((entry = readdir(dp))) {
        if (!ends_with_sock(entry->d_name))
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s%s", UBUS_SOCKET_DIR, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1)
            continue;

        if (S_ISSOCK(st.st_mode)) {
	    char abs_dir[PATH_MAX];
	    if (!realpath(fullpath, abs_dir)) {
		perror("realpath failed!");
		goto exit;
	    }

	    ubus_socket_path = strdup(abs_dir); // Found Socket!
            goto exit;
        }
    }

exit:
    closedir(dp);
    return ubus_socket_path;
}

int main() {
    char *socket_path = find_socket_file();
    if (socket_path) {
        printf("Found socket: %s\n", socket_path);
        free(socket_path);
    } else {
        printf("No socket file found.\n");
    }

    return 0;
}

