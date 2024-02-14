# TCPEchoServer

This project is a show case for my studies in sockets.

The original objective here was to create a C++ code for echo server, but in the end I choose to create a generic library for sockets.

## 🧱 Project Structure

- `src`: main source code
- `include`: public headers
- `tests`: unit tests
- `examples`: examples of usage **MAIN GOAL: ECHO SERVER**

## 🔨 How to build

It's just an ordinary `cmake` process

```bash
mkdir build; cd build
cmake ..
make
```

## ✅ Development Steps

- [x] build a basic socket server and client
- [ ] turn the code into a library
- [ ] add paralellism
- [ ] add the example of client and echox server for a simple buffer comunication
- [ ] add login requests as in document
- [ ] add encryption/decryption