set -e

/opt/wasi-sdk/bin/clang++ main.cpp -L../../ic_polyfill/target/wasm32-wasi/release -lic_polyfill -o main.wasm
wasi2ic main.wasm nowasi.wasm
wasm2wat nowasi.wasm > nowasi.wat
dfx canister install -y --mode reinstall --wasm nowasi.wasm demo2_backend

dfx canister call demo2_backend greet --output raw --type raw `echo "world" | xxd -p` | xxd -p -r

