© (2014-2016) L. Deecke (*ldeecke@gmail.com*) and H. Dobrovolny (*h.dobrovolny@tcu.edu*)

Required: CMake (2.8.9) and boost/program_options (0.24.1).

---

![symmetric kernel](sk.png)

The following code is the building block that is used to study the influenza dynamics in a two-cell model, mathematically realized via a stochastic system of differential equations. The systems parametrization (constituted from 29 unique parameters) is passed to the program via a user-editable config file that allows the study of pharmaceutical treatment schemes commonly used to fight off influenza inections, amantadines and neuraminidase inhibitors.

Usage:

1. Create and navigate into a directory `build`.
2. Execute CMake via `cmake ..`. Call `make` when completed.
3. Navigate back to the root directory, edit `config.ini` and execute `build/influenza`.
4. Viral titer curves are written into `out.dat`.