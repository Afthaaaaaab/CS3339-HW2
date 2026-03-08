# CS3339-HW2
CS3339 Homework 2
Floating Point Overflow Checker

Team Members:
- Name1
- Name2

Compilation:
g++ fp_overflow_checker.cpp -o fp_overflow_checker

Run:
./fp_overflow_checker <loop_bound> <loop_counter>

Example:
./fp_overflow_checker 1e8 1.0

Description:
The program analyzes the IEEE-754 representation of two floating-point
values and determines whether floating-point overflow may occur due to
loss of precision when incrementing a loop counter.
