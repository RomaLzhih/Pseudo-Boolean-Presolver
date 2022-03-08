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
program + file_path, e.g.,
```
./pre ../test/opt/p0033.opb
```
a quick test (may need to change the path of roundingSat and instances manually):
```
cd test
python pretest.py
```