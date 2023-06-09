#include <iostream>
#include <string>
#include <stdio.h>

#define __IMPORT(module, name) __attribute__((__import_module__(#module), __import_name__(#name)))
#define __EXPORT(name) __attribute__((__export_name__(#name)))


extern "C" void raw_init(char* p, std::size_t len) __IMPORT(polyfill, raw_init);

extern "C" void ic0_debug_print(const char *str, std::size_t len) __IMPORT(ic0, debug_print);
extern "C" int  ic0_msg_arg_data_size() __IMPORT(ic0, msg_arg_data_size);
extern "C" void ic0_msg_arg_data_copy(char * buf, std::size_t offset, std::size_t length) __IMPORT(ic0, msg_arg_data_copy);
extern "C" void ic0_msg_reply() __IMPORT(ic0, msg_reply);
extern "C" void ic0_msg_reply_data_append(const char * buf, std::size_t length) __IMPORT(ic0, msg_reply_data_append);

extern "C" __EXPORT(canister_query greet) __attribute__((noinline)) void greet()  {

    int n = ic0_msg_arg_data_size();
    char buf[n];
    
    ic0_msg_arg_data_copy(buf, 0, n);
    
    std::string s(buf);
    std::cout << "Hello from WASI: " << s;
    
    std::string ret = std::string("Hello, ") + s;
    
    ic0_msg_reply_data_append(ret.c_str(), ret.length());
    ic0_msg_reply();
}

int main() {
    
    raw_init(nullptr, 0);
    
    return 0;
}
