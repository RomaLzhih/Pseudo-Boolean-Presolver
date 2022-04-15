## Pre-Request

1. (ignore now) download PaPILO(https://github.com/scipopt/papilo), unzip and rename it to 'papilo', put it into the source folder: ../pre/
2. install TBB (required by PaPILO).

PaPILO now is on git version 60ab076

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

## Customized API added in PaPILO:
1. in Presolve.hpp: PreSolve<REAL>(line 249): add getPresolver() and getPresolverStat()
```
///! access presolvers and states
   const Vec<std::unique_ptr<PresolveMethod<REAL>>>&
   getPresolvers() const
   {
      return presolvers;
   }

   const Vec<std::pair<int, int>>&
   getPresolverStats() const
   {
      return presolverStats;
   }
```
2. In PresolveMethod.hpp (line 223): add getSuccessfulCalls() and getExectime()
```
/// ! add NSuccessCalls and ExecTime
   unsigned int
   getNSuccessCalls() const
   {
      return nsuccessCall;
   }

   double
   getExecTime() const
   {
      return execTime;
   }
```
3. In PreSolve.hpp (line 210): add getHugeVal()
```
/// get huge value
   const REAL&
   getHugeVal() const
   {
      return num.getHugeVal();
   }
```