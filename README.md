# Operating-Systems-Simulation
## 1.  Introduction
### 1.1 An overview
The assignment is about simulating a simple operating system to help me understand the fundamental concepts of scheduling, synchronization and memory management. Figure 1 shows the overall architecture of the operating system that I'm going to implement. Generally, the OS has to manage two virtual resources:
CPU(s) and RAM using two core components:
- Scheduler (and Dispatcher): determines which process is allowed to run on which CPU.
- Virtual memory engine (VME): isolates the memory space of each process from other. The physical RAM is shared by multiple processes but each process do not know the existence of other. This is done by letting each process has its own virtual memory space and the Virtual memory engine will map and translate the virtual addresses provided by processes to corresponding physical addresses.

## 2. How to run ?
**Start from your terminal (be sure that your terminal now is in project and at the same level(folder) with *Makefile*), type these command in order:**
1. `make all` to create executable file (*os.exe*)
2. `./os [configure_file]` where *configure_file* is the path to configure file for the evironment on which you want to run and it shoul associated with the name of a description file placed placed in *input* directory.
## 3. Details of OS:
You can get all detail information about this simulated Operating System in this link: [Simple Operating System](https://drive.google.com/drive/u/1/folders/15Dob9lXrMWt8VSuIcNwW0EATKoteKxXy)


