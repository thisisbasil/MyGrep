# MyGrep

A barebones implementation of grep using C++20

## Building

cd into MyGrep
run: $ cmake CMakeLists.txt && make

## Running

$ ./MyGrep <search string> <path>

## Overall Design

Very simple implementation of grep. Performs a recursive regex search on a given directory and outputs matching files to stdout.

Consists of a single class, MyGrep, which is a thread-safe singleton class.

It starts by validating the number of parameters, and whether or not the path parameter is, in actuality, a path. If these checks
fail, the program bails and prints the appropriate error message to stderr.

If these checkes pass, it will then do use std::filesystem to do a recursive search on the path and will collect all regular files
into a std::queue.

It will then determine the number of cores and create a thread pool of that size. 

The threads will then all fire off and begin their search of the file using std::regex.

It uses std::mutex to provide mutually exclusive access to the queue and each thread loops until the queue is empty, wherein all threads join and
the program completes. If it is able to pull a file from the queue, it opens the file and reads it line by line, performing a regex search on
each line, short-circuiting whenever a match is found. If a match is found, a message will print to stdout to this effect.

Originally written on MacOS Sonoma 14.5 using clang++ 15.0. and tested on the same machine, as well as Almalinux 8.10 using g++ 8.5.0

I don't have access to a Windows Machine

Standard is c++20
