#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <sys/stat.h>

static int num_dirs = 0;
static int num_regular = 0;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_D)
        num_dirs++;
    else if (typeflag == FTW_F)
        num_regular++;
    return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        printf("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    if (ftw(argv[1], callback, MAX_FTW_DEPTH) != 0) {
        perror("ftw failed");
        return 2;
    }

    printf("Processed all the files from %s.\n", argv[1]);
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}