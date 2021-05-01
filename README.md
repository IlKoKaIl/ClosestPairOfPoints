# ClosestPairOfPoints
Three algorithms to solve a closest pair of points problem as described in the uploaded pdf. Using brute force, recursion and multiple processes + recursion
Implemented in C and the program solves the problem describes here in O(nlogn) time for the parallel solution.

There are 3 solutions implemented:
closest_brute which uses brute force to solve the problem
closest_serial which uses a single recursive process to solve the problem
closest_parallel which uses multiple fork() processes to recursively solve the problem

Running information:
running 'make' in console will create all the object files
There is already a test files created called closest_tests, to run that first run 'make' followed by './closest_tests'
To get more info about running via command lines arguments after running 'make' type './closest' in console for more information.
