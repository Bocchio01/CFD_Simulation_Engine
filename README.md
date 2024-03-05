> [!CAUTION]
> Unfortunately, the code still doesn't work properly (needs for too low under-relaxation factors for convergence).

# Lid-driven cavity incompressible flow (steady state)

This assignment was about solving the well known **2D lid-driven cavity incompressible flow (steady state)** problem using different algorithms and schemes.

<div align=center>

![Lid-driven cavity incompressible flow](https://www.fifty2.eu/wp-content/uploads/2021/08/thumbnailupdate.png)

Lid-driven cavity incompressible flow solution

</div>

## Problem statement

The problem consists in a square cavity with a lid moving at a constant velocity.
The flow is incompressible and Reynolds number is low (Re <= 1000).
**Navier-Stokes** equations and the **pressure-velocity coupling** are used to solve the problem.

## Methods and schemes

The code is able to solve the problem using various methods and schemes.
In particular, we can choose the following options:

- Methods:
  - **Gauss-Siedel (SCGS)**
  - **SIMPLE** (not implemented yet)
- Schemes:
  - **Convection schemes**:
    - UDS
    - CDS
    - QUICK
    - Hybrid (not implemented yet)
  - **Diffusion schemes**:
    - Second order central difference
    - Fourth order central difference

## Data input

The code reads the input parameters from a file in JSON format.

```json
// Example of in file
{
    "in": {
        "uLid": 1.0,
        "geometry": {
            "x": 1.0,
            "y": 1.0
        },
        "fluid": {
            "Re": 1000
        }
    },
    "engine": {
        "mesh": {
            "nodes": {
                "Nx": 80,
                "Ny": 80
            }
        },
        "method": {
            "tolerance": 1e-05,
            "maxIter": 5000,
            "underRelaxation": {
                "u": 0.08,
                "v": 0.08
            }
        },
        "schemes": {
            "convection": "QUICK",
            "diffusion": "SECOND"
        }
    }
}
```

### CMD input

From the command line, the possible input arguments are:

- `-h` or `--help` to print the help
- `-v` or `--version` to print the version
- `-i` or `--in` to specify the input file path (relative or absolute). Default: `-i sim_input/input.json`
- `-f` or `--format` to specify the out file format. Default: `-f DAT`

## Output

The output is saved in a `DAT` file and it is possible to visualize it using the `MATLAB` script provided in the `sim_output/plotting` folder.

An example of the output file is:

```bash
07_80_80_1000_QUICK_SECOND_008_008
RE=1000.000000
ITERATIONS=5001
CPU_TIME=119.330000
RESIDUALS=0.000000 0.128145 0.122590 ...
VARIABLES="X", "Y", "U", "V", "P"
ZONE F=POINT, I=80, J=80
0.006250,0.006250,0.000017,-0.000021,0.044281
0.018750,0.006250,0.000113,-0.000085,0.044314
0.031250,0.006250,0.000310,-0.000123,0.044337
0.043750,0.006250,0.000558,-0.000137,0.044344
...
```

## How to...

> [!WARNING]
> The `Makefile` is platform dependent and the one included here works for Windows.

### Compile the source code

You can compile the code by typing the following command from the root folder of the repository:

```bash
gcc -DLOG_USE_COLOR -Wall -Wextra -Werror -std=c99 -O2  src/utils/cALGEBRA/*.c src/utils/cJSON/*.c  src/utils/cFILE/*.c src/utils/cLOG/*.c src/main.c src/CFD.c src/in/*.c src/out/*.c src/in/parsers/*.c src/engine/*.c src/engine/mesh/*.c src/engine/methods/*.c src/engine/schemes/*.c -o main
```

Or, alternatively, you can use the `Makefile` included in the repository by typing:

```bash
make
```

### Run the code

The most straightforward way to run the code is by typing:

```bash
./main
```

Here is an example of how to run the code with the default parameters:

```bash
./main -i sim_input/input.json -f DAT
```

### CMake version

```bash
mkdir build
cmake -S . -B build
cmake --build build

# Picking a compiler
CC=clang CXX=clang++ cmake -S . -B build
```