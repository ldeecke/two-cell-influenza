© (2014-2016) L. Deecke (*ldeecke@gmail.com*) and H. Dobrovolny (*h.dobrovolny@tcu.edu*)

Required: CMake (2.8.9) and boost/program_options (0.24.1).

---

![symmetric kernel](sk.png)

The following code provides the building block that is used to study the dynamics in an influenza A infection. A two-cell model (that is mathematically realized through a stochastic system of differential equations) is parametrized via 29 unique parameters that are passed to the program (at runtime) via a user-editable config file. This program allows researchers to simulate pharmaceutical treatment schemes commonly used in the curing of an influenza infection in an easy manner and at short execution times.

Usage:

1. Create and navigate into a directory `build`.
2. Execute CMake via `cmake ..` and then `make`.
3. Navigate back to the root directory, edit `config.ini` and execute `build/influenza`.
4. Viral titer curves are written into `out.dat`.
