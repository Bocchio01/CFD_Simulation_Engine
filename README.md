# Lid-driven cavity incompressible flow

This assignment is about solving the well known **2D lid-driven cavity incompressible flow** problem using different algorithms and schemes.

<div align=center>

![Lid-driven cavity incompressible flow](https://www.fifty2.eu/wp-content/uploads/2021/08/thumbnailupdate.png)

Lid-driven cavity incompressible flow solution

</div>

## Problem statement

The problem consists in a square cavity with a lid moving at a constant velocity. The flow is incompressible and the Reynolds number is low. **Navier-Stokes** equations and the **pressure-velocity coupling** are used to solve the problem.

## Methods and schemes

The code is able to solve the problem using various methods and schemes.
In particular, we can choose the following options:

- Methods:
  - **Gauss-Siedel (SCGS)**
  - **SIMPLE**
- Schemes:
  - **Convection schemes**:
    - UDS
    - Hybrid
    - QUICK
  - **Diffusion schemes**:
    - Second order central difference
    - Fourth order central difference

## Data in

The code is higly customizable and as an in it requires the following parameters:

```json
// Example of in file
{
    "in": {
        "uLid": 1.0,
        "geometry": {
            "x": 1,
            "y": 1
        },
        "fluid": {
            "mu": 1.0
        }
    },
    "engine": {
        "mesh": {
            "type": "STAGGERED",
            "nodes": {
                "Nx": 10,
                "Ny": 10
            },
            "elements": {
                "type": "RECTANGULAR"
            }
        },
        "method": {
            "type": "SCGS",
            "tolerance": 1e-4,
            "maxIter": 1000,
            "underRelaxation": {
                "u": 0.5,
                "v": 0.5,
                "p": 0.3
            }
        },
        "schemes": {
            "convection": "UDS",
            "diffusion": "SECOND_ORDER"
        }
    },
    "out": {
        "format": "JSON"
    }
}
```

### CMD in

From the command line, the possible in parameters are:

- `-h` or `--help` to print the help
- `-v` or `--version` to print the version
- `-i` or `--in` to specify the in file relative or absolute. Default: `-i data/input.json`
- `-f` or `--format` to specify the out file format. Default: `-f JSON`

## Output

The out is a file containing the solution of the problem.
The format of the out file can be specified in the in file.


## How to...

> [!WARNING]
> The `Makefile` is platform dependent and the one included here works for Windows.

### Compile the source code

You can compile the code by typing:

```bash
# TODO fix the gcc SRCS
gcc -Wall -Wextra -Werror -pedantic -std=c99 -O2 *.c -o main
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
./main -i data/input.json -f JSON
```

### Usefull links

- [MIT education](https://web.mit.edu/calculix_v2.7/CalculiX/ccx_2.7/doc/ccx/node14.html)
- [Fifty2](https://www.fifty2.eu/innovation/lid-driven-cavity-2d-in-preonlab/)
- [Java plots](https://stackoverflow.com/questions/1740830/java-3d-plot-library)