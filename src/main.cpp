#include <stdio.h>

#define __IMPORT(module, name) __attribute__((__import_module__(#module), __import_name__(#name)))


extern "C" void init() __IMPORT(polyfill, init());

int main() {
    init();

    printf("Hello World\n");
//    rust_function();
    
    char buf[6] = "123\0";

    printf("Before call: %s\n", buf);
//    __ic_custom_random_get(buf, 4);
    printf("After call: %s\n", buf);
 
    return 0;
}


