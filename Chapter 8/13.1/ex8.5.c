/* fsize: print file information from inode

inode: An inode is a Unix file system structure 
that stores all metadata about a file except 
its name, including where the file’s data is 
stored on disk. (For Reference) */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void fsize(char*);

main()
{
    char name[256];

    printf("Enter file name: ");
    scanf("%255s", name);

    fsize(name);
    return 0;
}

void fsize(char* name)
{
    struct stat st;
    char *ctime();

    if (stat(name, &st) < 0) {
        printf("fsize: can't access %s\n", name);
        return;
    }

    printf("File: %s\n", name);
    printf("Inode number: %ld\n", (long) st.st_ino);
    printf("Size (bytes): %ld\n", (long) st.st_size);
    printf("Links: %ld\n", (long) st.st_nlink);
    printf("User ID: %ld\n", (long) st.st_uid);
    printf("Group ID: %ld\n", (long) st.st_gid);
    printf("Mode: %o\n", st.st_mode & 0777);
    printf("Last modified: %s", ctime(&st.st_mtime));
}
