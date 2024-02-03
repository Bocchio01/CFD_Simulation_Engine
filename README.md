# Lid-driven cavity incompressible flow

This assignment is about solving the well known **2D lid-driven cavity incompressible flow** problem using different convection schemes (UDS, Hybrid and QUICK).

<div align=center>

![Lid-driven cavity incompressible flow](https://www.fifty2.eu/wp-content/uploads/2021/08/thumbnailupdate.png)

</div>

## Output

The code gives as output a `.txt` file with the following format:

```bash
x y u v p
```

Where `x` and `y` are the coordinates of the mesh, `u` and `v` are the velocity components and `p` is the pressure.
All the data refers to the steady state solution.


## How to...

> [!WARNING]
> The `Makefile` is platform dependent and the one included here works for Windows.

### Compile the source code

You can compile the code by typing:

```bash
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

However, you can also give the code some arguments as:

- `-h` or `--help` to get some help
- `-s` or `--scheme` to choose the convection scheme (`UDS`, `Hybrid` or `QUICK`)
- `-r` or `--relaxation` to choose the relaxation factor
- `-i` or `--iterations` to choose the maximum number of iterations
- `-t` or `--tolerance` to choose the tolerance for the residual
- `-o` or `--output` to choose the output file name
- `-p` or `--plot` to plot the results
- `-v` or `--verbose` to print the residual at each iteration
- `-d` or `--debug` to print some debug information
- `-c` or `--clean` to clean the output files
- `-f` or `--force` to force the execution of the code even if the output file already exists
- `-q` or `--quiet` to suppress the output
- `-a` or `--all` to run the code with all the convection schemes
- `-e` or `--error` to compute the error between the analytical and numerical solution
- `-n` or `--nodes` to choose the number of nodes in the x and y direction
- `-x` or `--xlength` to choose the length of the domain in the x direction
- `-y` or `--ylength` to choose the length of the domain in the y direction
- `-u` or `--velocity` to choose the velocity of the lid
- `-m` or `--mu` to choose the viscosity of the fluid
<!-- - `-b` or `--beta` to choose the under-relaxation factor -->
<!-- - `-l` or `--lambda` to choose the relaxation factor for the pressure -->

Here is an example of how to run the code with the default parameters:

```bash
./main -s QUICK -r 0.5 -i 10000 -t 1e-6 -o output.txt -p -v -d -c -f -q -a -e -n 100 -x 1 -y 1 -u 1 -m 0.01
```

### Usefull links

- [MIT education](https://web.mit.edu/calculix_v2.7/CalculiX/ccx_2.7/doc/ccx/node14.html)
- [Fifty2](https://www.fifty2.eu/innovation/lid-driven-cavity-2d-in-preonlab/)
- [Java plots](https://stackoverflow.com/questions/1740830/java-3d-plot-library)