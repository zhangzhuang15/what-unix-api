#include <assert.h>

int main(){
    int a = 0;
    int b = 1;

    // assert is macro

    assert(a<1); // true, send no error
    assert(b>1); // false, send error
    return 0;
}