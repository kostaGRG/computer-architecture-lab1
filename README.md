# Computer Architecture: Lab 1
## Contributors
1. Full Name: Konstantinos Gerogiannis  
   Email: kostas.gerogiannis04@gmail.com  
   Github: [kostaGRG](https://github.com/kostaGRG/)  
2. Full Name: Katerina Vosniadou
   Email: katerinavosn@gmail.com  
   Github: [katerinavos](https://github.com/katerinavos)
   
## Intro
This project is created for the university class named Computer Architecture at Aristotle University of Thessaloniki (AUTh). It's the first out of three repositories referenced on the same class.

## Tasks
1. Please open the starter_se.py file that you used in the Hello World example and try to understand the basic parameters passed to gem5 for system simulation. Record the system's key characteristics, such as CPU type, operating frequency, basic units, caches, memory, etc. How could you change the operating frequency of the system?

2. The stats.txt file contains various statistics related to the gem5 simulation. The most important elements are sim_seconds, sim_insts, and host_inst_rate. What does each of these measurements represent?

3. In addition to the stats.txt output file generated at the end of the simulation, gem5 also produces the config.ini and config.json files. These files provide information about the system being simulated by gem5. Suppose the system has L1 miss penalty = 6 cycles, L2 miss penalty = 50 cycles, and a 1-cycle cache hit/instruction execution. Use the corresponding parameters from  the config and stats files and calculate the CPI according to the equation.

![Equation 0](/images/equation0.png)

4. It is important to be able to refer to and search for information in the literature. So, using the gem5 website (gem5.org) as a starting point, look for information about the different in-order CPU models used by gem5 (hint: in the example, you used the CPU model "minor") and provide a brief paragraph for each of them.

a) Write a program in C and execute it in gem5 using different CPU models while keeping all other parameters the same. Use the TimingSimpleCPU and MinorCPU models.
(Note: Do not use the same configuration file (starter_se.py) but use the file configs/example/se.py instead.)

Example execution:  
$ ./build/ARM/gem5.opt -d hello_result configs/example/arm/starter_se.py --cpu="minor" "tests/test-progs/hello/bin/arm/linux/hello"

Provide your results regarding execution times (hint: check stats.txt). Please note that gem5 is much slower in executing a program compared to your processor when running it directly.

b. Change one parameter of the processor and observe the results for the two different CPU models. Try changing the operating frequency and the memory technology used. Provide and justify the results you observed.
  i. Which CPU model is more sensitive to changes in operating frequency? Why does this happen?
  ii. Which CPU model is more sensitive to changes in memory technology used? Why does this happen?


#### Answers
1) The major parameters of the simulation are:
* **CPU type** = Minor: In this specific processor type there are L1 instruction cache, L1 data cache, walk cache και L2 cache.
* **CPU frequency** = 4 GHz (default value): As we didn't add a specific value, CPU frequency takes the default value. We could change this value if we had added during the execution the flag --cpu-freq CPU\_FREQ.
* **Memory type** = DDR3-16000-8X8 (default value)
* **Global frequency** = 1GHz
> The simulation included the processor, memory, and cache memories, but it did not have its own operating system. Additionally, one processor core was used.

2) In file stats.txt:
* **sim\_seconsds** = 0.000024 sec: total duration of the simulation
* **sim\_insts** = 5028: How many instructions simulated
* **host\_inst\_rate** = 92679: Instruction execution rate (instructions per second) based on the execution time that the host calculated.

3) Miss penalty: L1\_cache = 6 cycles, L2\_cache = 50 cycles  
  From the simulation files:  
 * **IL1.miss\_num** = 332
 * **DL1.miss\_num** = 179
 * **L2.miss\_num** = 479
 * **Total\_inst\_num** = 5028  
So we calculate that **_CPI = 6.3731_**

4) gem5 has the capability to use different models of in-order CPUs, for example minor, atomic etc.
* **Minor CPU**: This model has a fixed pipeline with 4 stages but variable data structures and behavior during execution. It is used to model processors with strict in-order behavior. It also allows tracking the position of each instruction in the pipeline. This model is not suitable for multithreading. 
* **HPI CPU**: It represents an effort to create an even more realistic model, enhancing the level of detail that already exists in the minor model.
* **Simple CPU**: This particular model is used when a detailed model is not required; it is fast but not realistic. Examples of its use include pre-warming or testing the operation of a program. In gem5, the models _AtomicSimpleCPU_ and _TimingSimpleCPU_ are available.
1. The atomic simple model supports atomic memory accesses. This means it returns an approximate value for the time required for the memory request to complete.
2. On the other hand, the timing simple model operates with timing simple accesses, meaning it accurately returns the time required to access memory. This method is slower compared to the previous one.

We execute a simple program on the Minor CPU and Timing Simple CPU models that multiplies a small array by itself and prints it to the screen (file matrix_mult.c). The execution times for each model are as follows:
* **Minor CPU time** = 0.000063 seconds
* **Timing Simple CPU time** = 0.000102 seconds
>I notice that the simulation time in the Timing Simple model is almost double compared to the Minor model. This is likely happening because the Minor CPU manages to achieve better performance thanks to its optimizations.

We change the frequency to 4 GHz. Then:
* **Minor CPU time** = 0.000058 seconds
* **Timing Simple CPU time** = 0.000097 seconds
>Both models reduce the execution time, but we have a higher percentage reduction in the first processor, 7.9%, compared to 4.9% in the second processor.

We changed the architecture of the memory to DDR4_2400_8x8 and we got:
* **Minor CPU time** = 0.000062 seconds
* **Timing Simple CPU time** = 0.000102 seconds
>The optimization on the execution time is tiny on the first model and zero on the second.

The previous experiments can be summed up on the following table:
| |initial state|higher frequency|faster memory|
|:-----------:|:---------:|:----------:|:----------:|
|Minor CPU|0.00063|0.000058|0.000062|
|Timing Simple CPU|0.000102|0.000097|0.000102|

#### References
1. [Git tutorial](https://www.freecodecamp.org/news/the-essential-git-handbook-a1cf77ed11b5/)  
2. [Markdown tutorial](https://www.markdowntutorial.com/)  
3. [Gem5](https://www.gem5.org)  
4. [Minor CPU](https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu)  
5. [Simple CPU](https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU)  
6. [Memory system access types](https://www.gem5.org/documentation/general_docs/memory_system/index.html#access-types)  
7. [CPU types](https://cirosantilli.com/linux-kernel-module-cheat/#gem5-cpu-types)  

#### Review
In my opinion, the assignment as the first one in this course had the appropriate level of difficulty: not too easy so that you couldn't learn something substantial from it, but also not too difficult to discourage the student from completing it. Personally, I found git to be quite challenging as a tool, and I had to watch several explanatory videos, even though the link you provided was detailed.
