# PresolveOpb
PaPILO integration with Pseudo-Boolean Problem instances of filetype `.opb`. File format is described here: http://www.cril.univ-artois.fr/PB16/format.pdf
## Dependencies
`papilo` library. Update paths in `CMakeFiles.txt` before building. `papilo` also requires TBB, refer to https://github.com/lgottwald/PaPILO for more information.<br>
Standard location for papilo is `<project_root>/papilo`. If your papilo is located in another folder, change location in `CMakeLists.txt`
## To build
```
mkdir build 
cd build 
cmake ..
make
```
## Binary usage
### All Options
```
All options:
  --help                Display all options
  -I [ --filein ] arg   Path to file in (.opb)
  -O [ --fileout ] arg  Path to file out (default <file-name>.pre.opb
  --postsolve           Postsolve solution. Supply .postsolve file and solution
  -P [ --postfile ] arg Path to postsolve file (default 
                        <file-name>.pre.postsolve
```
### Presolving
Presolve an instance by
```
./PresolveOpb -I <file-in>
```
### Postsolving
Supply your solution along with the postsolve file.
```
./PresolveOpb -I <solution> -P <postsolve-file> --postsolve
```
## Solution format
Currently only supports RoundingSat solution format. If you use RoundingSat pipe the solution to a file and supply that file.
## Example workflow with RoundingSat
1. run `./PresolveOpb -I example.opb -O example.pre.opb`
2. run `./roundingsat example.pre.opb --print-sol=1 > example.pre.sol`
3. run `./PresolveOpb -I example.pre.sol -P example.pre.postsolve --postsolve`
## Changing Presolver Settings
The solver reads the settings from `parameters.opb.txt`. Settings can be changed there. Note that there are a few settings that might break `.opb` instances, these are marked in the parameters file.
