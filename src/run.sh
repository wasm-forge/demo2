#!/bin/bash

set -e

/opt/wasi-sdk/bin/clang++ -mexec-model=reactor -fno-exceptions main.cpp -L../../ic-wasi-polyfill/target/wasm32-wasi/release -lic_wasi_polyfill -o main.wasm
wasi2ic main.wasm nowasi.wasm

wasm2wat nowasi.wasm > nowasi.wat

dfx canister create demo2_backend
dfx canister install -y --mode reinstall --wasm nowasi.wasm demo2_backend

dfx canister call demo2_backend greet --output raw --type raw `echo "world" | xxd -p` | xxd -p -r

