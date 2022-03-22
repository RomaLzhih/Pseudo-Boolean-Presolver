## Pre-Request

1. download PaPILO(https://github.com/scipopt/papilo), unzip and rename it to 'papilo', put it into the source folder: ../pre/
2. install TBB (required by PaPILO).

## To build 

```
mkdir build 
cd build 
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Usage
program + file_path + only_pre_solve(0: no, 1: yes only presolve), e.g.,
```
./pre ../test/opt/p0033.opb 0
```
a quick test (may need to change the path of roundingSat and instances manually in runRoundingSat.cpp and pretest):
```
cd test
python pretest.py 0
```
you can find the result on the logger in the folder then.