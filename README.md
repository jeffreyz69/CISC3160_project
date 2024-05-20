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
```
./main <yourfile>
```