# Log_function_by_threads
Function in C that uses Threads to calculate the log of a given value between 1 and 2

By: Carter Gamary

Program will calculate the log of a number between 1 and 2. The higher number of threads used and more iterations the more accurate the value will be.

Compile as you normally do with c files.

run with:
ThreadLog *Value 1-2* *Number of threads* *iterations*

*Value 1-2* = the value you want to see the log of.
*Number of threads* = How many threads will be used for calculations
*Iterations* Number of iterations for calculations per thread.

Example:
ThreadLog 1.5 4 3

This will complete 3 iterations of calculations along 4 threads, meaning 12 calculations will be made total.
