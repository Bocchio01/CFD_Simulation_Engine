> [!CAUTION]
> Unfortunately, the code still doesn't work properly. Looks like Reynolds number doesn't affect the solution and the bottom vortices are not created. I really have no idea why. I'm still working on it.


# Lid-driven cavity incompressible flow (steady state)

This assignment is about solving the well known **2D lid-driven cavity incompressible flow (steady state)** problem using different algorithms and schemes.

<div align=center>

![Lid-driven cavity incompressible flow](https://www.fifty2.eu/wp-content/uploads/2021/08/thumbnailupdate.png)

Lid-driven cavity incompressible flow solution

</div>

## Problem statement

The problem consists in a square cavity with a lid moving at a constant velocity.
The flow is incompressible and Reynolds number is low (Re < 1000).
**Navier-Stokes** equations and the **pressure-velocity coupling** are used to solve the problem.

## Methods and schemes

The code is able to solve the problem using various methods and schemes.
In particular, we can choose the following options:

- Methods:
  - **Gauss-Siedel (SCGS)**
  - **SIMPLE** (still not implemented)
- Schemes:
  - **Convection schemes**:
    - UDS
    - CDS (still not implemented)
    - Hybrid (still not implemented)
    - QUICK
  - **Diffusion schemes**:
    - Second order central difference
    - Fourth order central difference

## Data input

The code reads the input from a file in JSON format.

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
            "type": "STAGGERED",
            "nodes": {
                "Nx": 40,
                "Ny": 40
            },
            "elements": {
                "type": "RECTANGULAR"
            }
        },
        "method": {
            "type": "SCGS",
            "tolerance": 1e-4,
            "maxIter": 5000,
            "underRelaxation": {
                "u": 0.5,
                "v": 0.5,
                "p": 0.3
            }
        },
        "schemes": {
            "convection": "UDS",
            "diffusion": "SECOND"
        }
    },
    "out": {
        "file": {
            "path": "results",
            "name": "04_40_40_1000_UDS_05",
            "format": "DAT"
        }
    }
}
```

### CMD input

From the command line, the possible in parameters are:

- `-h` or `--help` to print the help
- `-v` or `--version` to print the version
- `-i` or `--in` to specify the in file relative or absolute. Default: `-i data/input.json`
- `-f` or `--format` to specify the out file format. Default: `-f DAT`

## Output

The output is saved in a `DAT` file and it is possible to visualize it using the `MATLAB` script provided in the `results/plotting` folder.

## How to...

> [!WARNING]
> The `Makefile` is platform dependent and the one included here works for Windows.

### Compile the source code

You can compile the code by typing:

```bash
gcc -DLOG_USE_COLOR  src/utils/cALGEBRA/*.c src/utils/cJSON/*.c  src/utils/cFILE/*.c src/utils/cLOG/*.c src/*.c src/in/*.c src/out/*.c src/in/parsers/*.c src/engine/*.c src/engine/mesh/*.c src/engine/methods/*.c src/engine/schemes/*.c -o main
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
./main -i data/input.json -f DAT
```

### Input files

NN_NX_NY_RE_CONV_DIFF_URU_URV










