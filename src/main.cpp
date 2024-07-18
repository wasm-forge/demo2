#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define __IMPORT(module, name) __attribute__((__import_module__(#module), __import_name__(#name)))
#define __EXPORT(name) __attribute__((__export_name__(#name)))


extern "C" void raw_init(char* p, std::size_t len) __IMPORT(polyfill, raw_init);

extern "C" void ic0_debug_print(const char *str, std::size_t len) __IMPORT(ic0, debug_print);
extern "C" int  ic0_msg_arg_data_size() __IMPORT(ic0, msg_arg_data_size);
extern "C" void ic0_msg_arg_data_copy(char * buf, std::size_t offset, std::size_t length) __IMPORT(ic0, msg_arg_data_copy);
extern "C" void ic0_msg_reply() __IMPORT(ic0, msg_reply);
extern "C" void ic0_msg_reply_data_append(const char * buf, std::size_t length) __IMPORT(ic0, msg_reply_data_append);

std::vector<uint64_t> vec1(2, 0);

extern "C" __EXPORT(canister_query greet) __attribute__((noinline)) void greet()  {
    // Work with vector defined in static memory
    // -> data is persisted across calls, using Orthogonal persistence
    ++vec1[0];
    ++vec1[1];
    // TODO: currently, the above access to vec1 results in an error:
    /*
    Error: Failed update call.
    Caused by: The replica returned a rejection error: reject code CanisterError, reject message Error from Canister bkyz2-fmaaa-aaaaa-qaaaq-cai: Canister trapped: heap out of bounds, error code None
    */
    // See: https://forum.dfinity.org/t/orthogonal-persistence-of-c-data-structures-on-the-internet-computer-a-study/21828/6?u=icpp 

    int n = ic0_msg_arg_data_size();
    char buf[n];

    ic0_msg_arg_data_copy(buf, 0, n);
    
    // work with text
    std::string s(buf);
    
    std::string content = std::string("Hello, ") + s;

    // do some file operations
    std::ofstream ofile("content.txt");
    ofile << "File content: " << content;
    ofile.close();

    std::string line;
    std::ifstream ifile("content.txt");
    getline (ifile,line);
    ifile.close();

    ic0_msg_reply_data_append(line.c_str(), line.length());
    ic0_msg_reply();
}

int main() {
    
    raw_init(nullptr, 0);
    
    return 0;
}
