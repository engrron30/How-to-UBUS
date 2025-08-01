#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>  // for PATH_MAX

#define TOP_DIR             "../"
#define UBUS_SOCKET_DIR     TOP_DIR "Scripts/"

static int ends_with_sock(const char *filename);

/*
 *  Return a heap-allocated string with the full socket file path, 
 *  or NULL if not found
 */  
char *find_socket_file()
{
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

	    /* Socket is found! */
	    ubus_socket_path = strdup(abs_dir);
            goto exit;
        }
    }

exit:
    closedir(dp);
    return ubus_socket_path;
}

/*
 * Checks if filename string is ending with ".sock" keyword
 */ 
static int ends_with_sock(const char *filename)
{
    const char *ext = ".sock";
    size_t len = strlen(filename);
    size_t ext_len = strlen(ext);
    return len >= ext_len && strcmp(filename + len - ext_len, ext) == 0;
}

/* 
 * Example of calling the above function
 * 
 * If someone desires to test this file, rename this example_main as
 * main then compile this file with a simple command:
 * 	gcc find_ubus_socket.c
 *
 * This will generate a.out and test this executable file if it
 * will output the socket string
 */ 
int example_main() {
    char *socket_path = find_socket_file();
    if (socket_path) {
        printf("Found socket: %s\n", socket_path);
        free(socket_path);
    } else {
	printf("No socket found!\n");
    }

    return 0;
}
