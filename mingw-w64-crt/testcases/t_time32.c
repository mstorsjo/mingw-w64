#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include <utime.h>

int main() {
    /* Check that all 32-bit time functions are present and can be called */
    struct tm tm;
    __time32_t t;
    struct __timeb32 tb;
    struct __utimbuf32 utb;
    _ctime32(&t);
    _difftime32(t, t);
    _ftime32(&tb);
    _futime32(0, &utb);
    _gmtime32(&t);
    _localtime32(&t);
    _mkgmtime32(&tm);
    _mktime32(&tm);
    _time32(&t);
    _utime32("", &utb);
    _wctime32(&t);
    _wutime32(L"", &utb);
    printf("TEST PASSED\n");
    return 0;
}
