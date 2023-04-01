# demo2 - Create the "Hello World" canister by using C++ to WASI compiler

This "hello world" demo project shows how to compile a Wasm canister written in C++ and deploy it using dfx. 

## Prerequisites

It is assumed that you have [rust](https://doc.rust-lang.org/book/ch01-01-installation.html), [dfx](https://internetcomputer.org/docs/current/developer-docs/setup/install/), and [wasi2ic](https://github.com/wasm-forge/wasi2ic) installed.

You will also need the Wasm-oriented [clang](https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-19/) installation. In this tutorial we use the .deb package [installation](https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-19/wasi-sdk_19.0_amd64.deb). Once installed the clang compiler is available from the path `/opt/wasi-sdk/bin/`.

Make sure you have the `ic_polyfill` library source available in the neighbouring folder, you can download it from github:
```bash
git clone https://github.com/wasm-forge/ic_polyfill.git
```
Enter the folder and compile it with the wasi32-wasm target:

```bash
cd ic_polyfill
cargo build --release --target wasm32-wasi
```

Now return to the parent folder:

```bash
cd ..
```

## Building project from scratch

Creare a new project using `dfx`:

```bash
dfx new --type=rust --no-frontend demo2
```

Enter the src folder of the project:
```bash
cd demo2/src
```

Create the main.cpp file with the following content:
```cpp
#include <string.h>

#define __IMPORT(module, name) __attribute__((__import_module__(#module), __import_name__(#name)))
#define __EXPORT(name) __attribute__((__export_name__(#name)))


extern "C" void init() __IMPORT(polyfill, init);

extern "C" void ic0_debug_print1(char *str, int len) __IMPORT(ic0, debug_print);
extern "C" int  ic0_msg_arg_data_size() __IMPORT(ic0, msg_arg_data_size);
extern "C" void ic0_msg_arg_data_copy(char * buf, int offset, int length) __IMPORT(ic0, msg_arg_data_copy);
extern "C" void ic0_msg_reply() __IMPORT(ic0, msg_reply);
extern "C" void ic0_msg_reply_data_append(char * buf, int length) __IMPORT(ic0, msg_reply_data_append);


extern "C" __EXPORT(canister_query greet) __attribute__((noinline)) void greet()  {

    int n = ic0_msg_arg_data_size();
    char buf[1000];
    ic0_msg_arg_data_copy(buf, 0, n);
    buf[n] = 0;

    char s[1000];
    sprintf(s, "Hello, %s", buf);

    ic0_debug_print1(s, strlen(s));

    ic0_msg_reply_data_append(s, strlen(s));
    ic0_msg_reply();
}

int main() {
    init();
    
    return 0;
}
```


## Compilation and deployment

Assuming you are in the `src` folder of the demo2 project, you should now be able to compile the main.cpp and and link the `ic_polyfill` library to it:

```bash
/opt/
```

