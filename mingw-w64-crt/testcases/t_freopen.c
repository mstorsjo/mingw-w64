#include <stdio.h>
#include <assert.h>

int main() {
    assert(freopen(NULL, "rb", stdin) != NULL);
    assert(freopen(NULL, "ab", stdout) != NULL);
    assert(freopen(NULL, "ab", stderr) != NULL);
    return 0;
}
