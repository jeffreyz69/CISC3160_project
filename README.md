**Usage: Make sure the makefile exists in the same dir as the c++ files**

Also make sure the local machine has a c++ compiler installed

i.e g++ or clang++ or mingw on windows

To compile the code, run the following command:
```
make run
```
To clean the compiled files, run the following command:
```
make clean
```
By default, the make run command will compile the code and run the executable file with a default input file named test.txt

To run the executable file with a different input file, run the following command:
NOTE: The input file should be in the same directory as the executable file and make run should've been ran at least once before running the following command. If not, the executable file won't exist. 
```
./main <yourfile>
```