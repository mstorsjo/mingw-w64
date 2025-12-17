#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>

static char *path;

static void remove_path(void) { RemoveDirectoryA(path); }

int main()
{
    char temp[MAX_PATH + 1];
    struct stat st;
    struct stat64 st64;
    HANDLE handle;
    int dirfd;

    assert(fstat(0, &st) == 0);
    printf("fstat(0): mode = %08o\n", st.st_mode);
    assert(!S_ISDIR(st.st_mode));

    assert(fstat64(0, &st64) == 0);
    printf("fstat64(0): mode = %08o\n", st64.st_mode);
    assert(!S_ISDIR(st64.st_mode));

    assert(GetTempPathA(MAX_PATH, temp));
    path = tempnam(temp, "mingw-w64-fstat-test-");
    assert(path);
    printf("CreateDirectoryA: path=%s\n", path);
    assert(CreateDirectoryA(path, NULL));

    printf("Open: path=%s\n", path);
    handle = CreateFileA(path, FILE_READ_ATTRIBUTES | DELETE, FILE_SHARE_VALID_FLAGS, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_DELETE_ON_CLOSE, NULL);
    if (handle != INVALID_HANDLE_VALUE)
        atexit(remove_path);
    assert(handle != INVALID_HANDLE_VALUE);

    dirfd = _open_osfhandle((intptr_t)handle, O_RDONLY);
    assert(dirfd >= 0);

    assert(fstat(dirfd, &st) == 0);
    printf("fstat(dirfd): mode = %08o\n", st.st_mode);
    assert(S_ISDIR(st.st_mode));

    assert(fstat64(dirfd, &st64) == 0);
    printf("fstat64(dirfd): mode = %08o\n", st64.st_mode);
    assert(S_ISDIR(st64.st_mode));

    return 0;
}

