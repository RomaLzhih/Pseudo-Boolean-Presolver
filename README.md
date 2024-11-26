## Introduction

`Pre` is a parallel Pseudo-Boolean presolver integrated with MIP solver [PaPILO](https://github.com/scipopt/papilo)(git version: 60ab076) and some novel implemented SAT presolving techniques 💖.

## Pre-Request

1. TBB (required by PaPILO).
2. C++17
3. Boost library

Please not update the PaPILO version since some contents have been modified.

## To build 

In the root directory of `Pre`:

```bash
mkdir build 
cp roundingsat build/
cd build 
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

Replace above `Release` to `Debug` to launch a `Debug` build.

## Usage
To run `Pre`, one need to pass five parameters to the binary file, namely:

1. `filePath`: the path where the input instance located, now only supports pseudo-Boolean [PBO](http://www.cril.univ-artois.fr/PB16/format.pdf) format;
2. `SATparam`: the parameter configuration for SAT presolving techniques, please find the sample file in `../param/defaultSAT.txt`;
3. `MIPparam`: provide the same utility for MIP as the previous one, a sample file is `../param/defaultMIP.txt`;
4. `onlyPreSolve`: whether only presolve the instance. Boolean $[0, 1]$;
5. `solverType`: Specify the presolver type. Integer `0`: only run SAT presolver, `1`:only run MIP presolver, `2`: run both, `3`: run [roundingSat](https://gitlab.com/MIAOresearch/roundingsat) only.

For example:

```bash
cd build
./pre ../test/opt/p0033.opb ../param/defaultSAT.txt ../param/defaultMIP.txt 0 2
```

## Ciatation
If you use our code, please cite our paper:
```
@phdthesis{menleveraging,
  title={Leveraging cutting planes reasoning for faster Pseudo-Boolean solving and optimization},
  author={Men, Ziyang},
  school={Department of Computer Science, University of Copenhagen}
}

```

