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

Start preparing the project 

## Compilation and deployment from C++

