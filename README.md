# VT-Emulation
* VT-Emulation stands for the emulation of Virtualization Techniques. 
* The tasks of this project aim to implement efficient execution of bytecode. 

## Infrastrure
* 3 registers: IP (instruction pointer), A (accumulator), and L (loop counter)

## Virtual Instruction Set Architecture
* `HALT` : (opcode 0), stop execution
* `CLRA` : (opcode 1), 
   ```=c
   A = 0; IP = IP + 1;
   ```
* `INC3A`: (opcode 2), 
   ```=c
   A = A + 3; IP = IP + 1;
   ```
* `DECA` : (opcode 3), 
   ```=c
   A - 1; IP = IP + 1;
   ```
* `SETL` : (opcode 4), 
   ```=c
   L = A; IP = IP + 1;
   ```
* `BACK7`: (opcode 5), 
   ```=c
   if(L > 0) { 
      L--; IP = IP - 6;
   }
   else
      IP = IP + 1;
   ```

## Build & Check
* `$ make clean`
* `$ make`
* `$ main.out`
* `$ valgrind --tool=memcheck --leak-check=full ./main.out`

## Interpreters
* interpreter_v1: No optimization
* interpreter_v2: **Indirect threaded** interpretation
* interpreter_v3: **Predecoding** with **direct threaded** interpretation
* interpreter_v4: Reducing the number of jumps by using "**superevents**" (combinations of 2 original instructions in a row).

## Binary Translators
* jit_v1: Pre-generation of Static BBs, Direct Mapped Code Cache
* jit_v2: Pre-generation of Dynamic BBs, Direct Mapped Code Cache
* jit_v3: Dynamic Generation of Dynamic BBs, Direct Mapped Code Cache

## Measurement Approaches
* [Measurement Script - `main.sh`](#Measurement-Script---mainsh): 
   * `clock_gettime(CLOCK_MONOTONIC, &time);`
* [Measurement Script - `run_interpreter.sh`](#Measurement-Script---run_interpretersh): 
   * `$ sudo perf stat -r 1000 \<target\>`

## Measurement Script - `main.sh`
```
####################
senario: 1
size: 10000
seed: 1
prob: 0 1 0 0 0
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 2999706, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.133573 msec

INT_v2: Computed goto
myreg.rA: 2999706, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.036198 msec

INT_v3: Predecoded computed goto
myreg.rA: 2999706, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.040134 msec

INT_v4: Superevents
myreg.rA: 2999706, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.039867 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 30003, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.064213 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 30003, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.022327 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 30003, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.022158 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 30003, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.024813 msec


####################
senario: 2
size: 10000
seed: 1
prob: 1 1 1 0 0
rounds: 100
####################

INT_v1: No optimization
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.126985 msec

INT_v2: Computed goto
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.079060 msec

INT_v3: Predecoded computed goto
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.094034 msec

INT_v4: Superevents
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.102477 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.064276 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.022840 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.022378 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: -1, myreg.rL: 7
Total wall-clock Time (CLOCK_MONOTONIC) = 0.024886 msec


####################
senario: 3
size: 10000
seed: 1
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 3.986307 msec

INT_v2: Computed goto
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 1.737577 msec

INT_v3: Predecoded computed goto
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 1.572109 msec

INT_v4: Superevents
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 1.517316 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.089632 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.041566 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.035429 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 95, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.033196 msec


####################
senario: 4
size: 10000
seed: 2
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 2.204011 msec

INT_v2: Computed goto
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.977791 msec

INT_v3: Predecoded computed goto
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.901453 msec

INT_v4: Superevents
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.849267 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.086969 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.035738 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.032007 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 0, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.032038 msec


####################
senario: 5
size: 10000
seed: 3
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 5.668837 msec

INT_v2: Computed goto
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 2.447744 msec

INT_v3: Predecoded computed goto
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 2.222601 msec

INT_v4: Superevents
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 1.982962 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.089723 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.041485 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.039055 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 27, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.034351 msec


####################
senario: 6
size: 50000
seed: 1
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 111.918037 msec

INT_v2: Computed goto
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 48.784745 msec

INT_v3: Predecoded computed goto
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 43.278242 msec

INT_v4: Superevents
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 42.391145 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.741914 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.377928 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.375628 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 152, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.277355 msec


####################
senario: 7
size: 50000
seed: 2
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 15.194884 msec

INT_v2: Computed goto
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 6.555438 msec

INT_v3: Predecoded computed goto
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 5.978090 msec

INT_v4: Superevents
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 5.722097 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 0.420776 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 0.190180 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 0.172645 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 9, myreg.rL: 6
Total wall-clock Time (CLOCK_MONOTONIC) = 0.182010 msec


####################
senario: 8
size: 50000
seed: 3
prob: 1 9 1 5 5
rounds: 100
####################

INT_v1: No optimization
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 25.780819 msec

INT_v2: Computed goto
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 11.343278 msec

INT_v3: Predecoded computed goto
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 10.026728 msec

INT_v4: Superevents
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 8.910866 msec

JIT_v1: Pre-generation of static BBs
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.449707 msec

JIT_v2: Pre-generation of dynamic BBs
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.212956 msec

JIT_v3: Dynamic generation of dynamic BBs
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.200764 msec

JIT_v4: Chained Dynamic generation of dynamic BBs
myreg.rA: 6, myreg.rL: 0
Total wall-clock Time (CLOCK_MONOTONIC) = 0.194325 msec
```
## Measurement Script - `run_interpreter.sh`

### Senario 1
#### size 10000, seed 1, probabilities 0/1/0/0/0
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 0.057203 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 0.021345 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 0.040188 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 0.041322 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 1' (1000 runs):

              0.53 msec task-clock                #    0.671 CPUs utilized            ( +-  0.45% )
                 0      context-switches          #    0.123 K/sec                    ( +- 16.63% )
                 0      cpu-migrations            #    0.000 K/sec                  
                27      page-faults               #    0.052 M/sec                    ( +-  0.06% )
           812,686      cycles                    #    1.542 GHz                      ( +-  0.20% )
            15,764      stalled-cycles-frontend   #    1.94% frontend cycles idle     ( +-  0.66% )
           310,158      stalled-cycles-backend    #   38.16% backend cycles idle      ( +-  0.24% )
         1,609,978      instructions              #    1.98  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.04% )
           249,996      branches                  #  474.453 M/sec                    ( +-  0.05% )
             1,228      branch-misses             #    0.49% of all branches          ( +-  1.03% )

        0.00078527 +- 0.00000412 seconds time elapsed  ( +-  0.53% )


 Performance counter stats for './run_interpreter_v2.out 1' (1000 runs):

              0.44 msec task-clock                #    0.633 CPUs utilized            ( +-  0.47% )
                 0      context-switches          #    0.114 K/sec                    ( +- 20.36% )
                 0      cpu-migrations            #    0.000 K/sec                  
                27      page-faults               #    0.062 M/sec                    ( +-  0.06% )
           686,413      cycles                    #    1.559 GHz                      ( +-  0.20% )
            15,434      stalled-cycles-frontend   #    2.25% frontend cycles idle     ( +-  0.69% )
           263,941      stalled-cycles-backend    #   38.45% backend cycles idle      ( +-  0.34% )
         1,239,827      instructions              #    1.81  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.05% )
           199,978      branches                  #  454.096 M/sec                    ( +-  0.06% )
             1,205      branch-misses             #    0.60% of all branches          ( +-  1.04% )

        0.00069552 +- 0.00000383 seconds time elapsed  ( +-  0.55% )


 Performance counter stats for './run_interpreter_v3.out 1' (1000 runs):

              0.57 msec task-clock                #    0.683 CPUs utilized            ( +-  0.46% )
                 0      context-switches          #    0.130 K/sec                    ( +- 15.21% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.118 M/sec                    ( +-  0.02% )
           887,554      cycles                    #    1.555 GHz                      ( +-  0.21% )
            17,181      stalled-cycles-frontend   #    1.94% frontend cycles idle     ( +-  0.78% )
           398,989      stalled-cycles-backend    #   44.95% backend cycles idle      ( +-  0.24% )
         1,612,070      instructions              #    1.82  insn per cycle         
                                                  #    0.25  stalled cycles per insn  ( +-  0.04% )
           232,835      branches                  #  407.972 M/sec                    ( +-  0.05% )
             1,395      branch-misses             #    0.60% of all branches          ( +-  0.92% )

        0.00083549 +- 0.00000804 seconds time elapsed  ( +-  0.96% )


 Performance counter stats for './run_interpreter_v4.out 1' (1000 runs):

              0.56 msec task-clock                #    0.685 CPUs utilized            ( +-  0.52% )
                 0      context-switches          #    0.117 K/sec                    ( +- 17.06% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.121 M/sec                    ( +-  0.02% )
           904,330      cycles                    #    1.624 GHz                      ( +-  0.26% )
            18,515      stalled-cycles-frontend   #    2.05% frontend cycles idle     ( +-  0.92% )
           373,824      stalled-cycles-backend    #   41.34% backend cycles idle      ( +-  0.35% )
         1,802,233      instructions              #    1.99  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.04% )
           272,841      branches                  #  489.914 M/sec                    ( +-  0.04% )
             1,511      branch-misses             #    0.55% of all branches          ( +-  1.02% )

        0.00081297 +- 0.00000476 seconds time elapsed  ( +-  0.59% )

### Senario 2
#### size 10000, seed 1, probabilities 1/1/1/0/0
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 0.136192 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 0.079500 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 0.071782 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 0.080822 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 2' (1000 runs):

              1.02 msec task-clock                #    0.788 CPUs utilized            ( +-  0.42% )
                 0      context-switches          #    0.100 K/sec                    ( +-  9.79% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +-100.00% )
                27      page-faults               #    0.027 M/sec                    ( +-  0.06% )
         1,535,068      cycles                    #    1.507 GHz                      ( +-  0.09% )
            29,442      stalled-cycles-frontend   #    1.92% frontend cycles idle     ( +-  0.46% )
           167,172      stalled-cycles-backend    #   10.89% backend cycles idle      ( +-  0.28% )
         1,600,606      instructions              #    1.04  insn per cycle         
                                                  #    0.10  stalled cycles per insn  ( +-  0.01% )
           250,172      branches                  #  245.594 M/sec                    ( +-  0.01% )
            14,746      branch-misses             #    5.89% of all branches          ( +-  0.09% )

        0.00129296 +- 0.00000542 seconds time elapsed  ( +-  0.42% )


 Performance counter stats for './run_interpreter_v2.out 2' (1000 runs):

              0.85 msec task-clock                #    0.763 CPUs utilized            ( +-  0.50% )
                 0      context-switches          #    0.126 K/sec                    ( +- 10.49% )
                 0      cpu-migrations            #    0.000 K/sec                  
                27      page-faults               #    0.032 M/sec                    ( +-  0.06% )
         1,351,034      cycles                    #    1.581 GHz                      ( +-  0.16% )
            31,067      stalled-cycles-frontend   #    2.30% frontend cycles idle     ( +-  0.68% )
           203,286      stalled-cycles-backend    #   15.05% backend cycles idle      ( +-  0.33% )
         1,231,205      instructions              #    0.91  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.02% )
           196,936      branches                  #  230.474 M/sec                    ( +-  0.02% )
            14,841      branch-misses             #    7.54% of all branches          ( +-  0.10% )

        0.00112056 +- 0.00000539 seconds time elapsed  ( +-  0.48% )


 Performance counter stats for './run_interpreter_v3.out 2' (1000 runs):

              0.93 msec task-clock                #    0.774 CPUs utilized            ( +-  0.44% )
                 0      context-switches          #    0.137 K/sec                    ( +-  9.48% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.073 M/sec                    ( +-  0.02% )
         1,416,997      cycles                    #    1.528 GHz                      ( +-  0.14% )
            31,899      stalled-cycles-frontend   #    2.25% frontend cycles idle     ( +-  0.56% )
           268,022      stalled-cycles-backend    #   18.91% backend cycles idle      ( +-  0.22% )
         1,603,774      instructions              #    1.13  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.01% )
           229,820      branches                  #  247.884 M/sec                    ( +-  0.02% )
            15,089      branch-misses             #    6.57% of all branches          ( +-  0.10% )

        0.00119802 +- 0.00000511 seconds time elapsed  ( +-  0.43% )


 Performance counter stats for './run_interpreter_v4.out 2' (1000 runs):

              1.04 msec task-clock                #    0.788 CPUs utilized            ( +-  0.43% )
                 0      context-switches          #    0.116 K/sec                    ( +-  8.61% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.065 M/sec                    ( +-  0.02% )
         1,495,620      cycles                    #    1.437 GHz                      ( +-  0.11% )
            34,498      stalled-cycles-frontend   #    2.31% frontend cycles idle     ( +-  0.37% )
           220,423      stalled-cycles-backend    #   14.74% backend cycles idle      ( +-  0.29% )
         1,684,365      instructions              #    1.13  insn per cycle         
                                                  #    0.13  stalled cycles per insn  ( +-  0.01% )
           245,185      branches                  #  235.515 M/sec                    ( +-  0.01% )
            18,466      branch-misses             #    7.53% of all branches          ( +-  0.08% )

        0.00132198 +- 0.00000527 seconds time elapsed  ( +-  0.40% )

### Senario 3
#### size 10000, seed 1, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 3.982712 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 1.815932 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 1.552551 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 1.513960 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 3' (1000 runs):

             11.36 msec task-clock                #    0.962 CPUs utilized            ( +-  0.46% )
                 1      context-switches          #    0.113 K/sec                    ( +-  1.36% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                27      page-faults               #    0.002 M/sec                    ( +-  0.06% )
        19,128,265      cycles                    #    1.684 GHz                      ( +-  0.03% )
            65,402      stalled-cycles-frontend   #    0.34% frontend cycles idle     ( +-  0.55% )
         7,977,679      stalled-cycles-backend    #   41.71% backend cycles idle      ( +-  0.04% )
        47,065,100      instructions              #    2.46  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.00% )
         5,859,645      branches                  #  515.798 M/sec                    ( +-  0.00% )
            23,373      branch-misses             #    0.40% of all branches          ( +-  0.05% )

         0.0118075 +- 0.0000537 seconds time elapsed  ( +-  0.45% )


 Performance counter stats for './run_interpreter_v2.out 3' (1000 runs):

              5.24 msec task-clock                #    0.933 CPUs utilized            ( +-  0.93% )
                 0      context-switches          #    0.084 K/sec                    ( +-  3.69% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                27      page-faults               #    0.005 M/sec                    ( +-  0.06% )
         9,262,865      cycles                    #    1.768 GHz                      ( +-  0.04% )
            48,057      stalled-cycles-frontend   #    0.52% frontend cycles idle     ( +-  0.51% )
         4,563,810      stalled-cycles-backend    #   49.27% backend cycles idle      ( +-  0.05% )
        18,255,819      instructions              #    1.97  insn per cycle         
                                                  #    0.25  stalled cycles per insn  ( +-  0.00% )
         1,888,677      branches                  #  360.402 M/sec                    ( +-  0.00% )
            22,491      branch-misses             #    1.19% of all branches          ( +-  0.11% )

         0.0056143 +- 0.0000502 seconds time elapsed  ( +-  0.90% )


 Performance counter stats for './run_interpreter_v3.out 3' (1000 runs):

              4.57 msec task-clock                #    0.928 CPUs utilized            ( +-  1.04% )
                 0      context-switches          #    0.104 K/sec                    ( +-  4.62% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.015 M/sec                    ( +-  0.02% )
         8,547,632      cycles                    #    1.870 GHz                      ( +-  0.08% )
            56,300      stalled-cycles-frontend   #    0.66% frontend cycles idle     ( +-  1.00% )
         4,109,383      stalled-cycles-backend    #   48.08% backend cycles idle      ( +-  0.14% )
        20,938,117      instructions              #    2.45  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         1,921,616      branches                  #  420.407 M/sec                    ( +-  0.00% )
            22,834      branch-misses             #    1.19% of all branches          ( +-  0.10% )

         0.0049229 +- 0.0000498 seconds time elapsed  ( +-  1.01% )


 Performance counter stats for './run_interpreter_v4.out 3' (1000 runs):

              3.95 msec task-clock                #    0.929 CPUs utilized            ( +-  1.28% )
                 0      context-switches          #    0.126 K/sec                    ( +-  4.98% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                67      page-faults               #    0.017 M/sec                    ( +-  0.02% )
         8,390,415      cycles                    #    2.124 GHz                      ( +-  0.09% )
            61,408      stalled-cycles-frontend   #    0.73% frontend cycles idle     ( +-  0.79% )
         3,994,311      stalled-cycles-backend    #   47.61% backend cycles idle      ( +-  0.14% )
        20,234,157      instructions              #    2.41  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         1,909,437      branches                  #  483.377 M/sec                    ( +-  0.00% )
            26,572      branch-misses             #    1.39% of all branches          ( +-  0.10% )

         0.0042515 +- 0.0000534 seconds time elapsed  ( +-  1.26% )

### Senario 4
#### size 10000, seed 2, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 2.234600 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 0.983687 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 0.867829 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 0.820779 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 4' (1000 runs):

              5.39 msec task-clock                #    0.944 CPUs utilized            ( +-  1.33% )
                 1      context-switches          #    0.098 K/sec                    ( +-  4.26% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                27      page-faults               #    0.005 M/sec                    ( +-  0.06% )
        11,506,499      cycles                    #    2.136 GHz                      ( +-  0.11% )
            65,788      stalled-cycles-frontend   #    0.57% frontend cycles idle     ( +-  1.21% )
         4,416,736      stalled-cycles-backend    #   38.38% backend cycles idle      ( +-  0.09% )
        26,623,733      instructions              #    2.31  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.00% )
         3,343,402      branches                  #  620.594 M/sec                    ( +-  0.00% )
            22,525      branch-misses             #    0.67% of all branches          ( +-  0.12% )

         0.0057077 +- 0.0000747 seconds time elapsed  ( +-  1.31% )


 Performance counter stats for './run_interpreter_v2.out 4' (1000 runs):

              3.78 msec task-clock                #    0.910 CPUs utilized            ( +-  0.47% )
                 0      context-switches          #    0.131 K/sec                    ( +-  3.57% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 70.68% )
                27      page-faults               #    0.007 M/sec                    ( +-  0.06% )
         5,880,115      cycles                    #    1.556 GHz                      ( +-  0.05% )
            44,055      stalled-cycles-frontend   #    0.75% frontend cycles idle     ( +-  0.43% )
         2,515,685      stalled-cycles-backend    #   42.78% backend cycles idle      ( +-  0.07% )
        10,855,177      instructions              #    1.85  insn per cycle         
                                                  #    0.23  stalled cycles per insn  ( +-  0.00% )
         1,198,697      branches                  #  317.212 M/sec                    ( +-  0.00% )
            22,299      branch-misses             #    1.86% of all branches          ( +-  0.10% )

         0.0041510 +- 0.0000189 seconds time elapsed  ( +-  0.45% )


 Performance counter stats for './run_interpreter_v3.out 4' (1000 runs):

              3.29 msec task-clock                #    0.906 CPUs utilized            ( +-  0.72% )
                 0      context-switches          #    0.139 K/sec                    ( +-  4.24% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                67      page-faults               #    0.020 M/sec                    ( +-  0.02% )
         5,534,503      cycles                    #    1.684 GHz                      ( +-  0.09% )
            49,600      stalled-cycles-frontend   #    0.90% frontend cycles idle     ( +-  0.81% )
         2,349,539      stalled-cycles-backend    #   42.45% backend cycles idle      ( +-  0.23% )
        12,479,940      instructions              #    2.25  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         1,231,454      branches                  #  374.598 M/sec                    ( +-  0.00% )
            22,578      branch-misses             #    1.83% of all branches          ( +-  0.09% )

         0.0036293 +- 0.0000255 seconds time elapsed  ( +-  0.70% )


 Performance counter stats for './run_interpreter_v4.out 4' (1000 runs):

              3.03 msec task-clock                #    0.903 CPUs utilized            ( +-  0.93% )
                 0      context-switches          #    0.135 K/sec                    ( +-  4.31% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 44.63% )
                67      page-faults               #    0.022 M/sec                    ( +-  0.02% )
         5,344,939      cycles                    #    1.762 GHz                      ( +-  0.08% )
            53,177      stalled-cycles-frontend   #    0.99% frontend cycles idle     ( +-  0.72% )
         2,173,507      stalled-cycles-backend    #   40.66% backend cycles idle      ( +-  0.13% )
        11,786,046      instructions              #    2.21  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.00% )
         1,195,528      branches                  #  394.051 M/sec                    ( +-  0.00% )
            26,390      branch-misses             #    2.21% of all branches          ( +-  0.09% )

         0.0033581 +- 0.0000309 seconds time elapsed  ( +-  0.92% )

### Senario 5
#### size 10000, seed 3, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 5.770140 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 2.491998 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 2.204778 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 1.980949 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 5' (1000 runs):

             11.75 msec task-clock                #    0.967 CPUs utilized            ( +-  1.01% )
                 1      context-switches          #    0.119 K/sec                    ( +-  2.33% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 30.00% )
                27      page-faults               #    0.002 M/sec                    ( +-  0.05% )
        26,690,884      cycles                    #    2.271 GHz                      ( +-  0.08% )
            80,472      stalled-cycles-frontend   #    0.30% frontend cycles idle     ( +-  1.03% )
        11,643,889      stalled-cycles-backend    #   43.62% backend cycles idle      ( +-  0.08% )
        66,991,589      instructions              #    2.51  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.00% )
         8,276,561      branches                  #  704.330 M/sec                    ( +-  0.00% )
            22,769      branch-misses             #    0.28% of all branches          ( +-  0.12% )

          0.012150 +- 0.000122 seconds time elapsed  ( +-  1.01% )


 Performance counter stats for './run_interpreter_v2.out 5' (1000 runs):

              6.96 msec task-clock                #    0.948 CPUs utilized            ( +-  1.04% )
                 1      context-switches          #    0.088 K/sec                    ( +-  3.53% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 57.68% )
                27      page-faults               #    0.004 M/sec                    ( +-  0.06% )
        12,561,681      cycles                    #    1.805 GHz                      ( +-  0.08% )
            56,946      stalled-cycles-frontend   #    0.45% frontend cycles idle     ( +-  0.74% )
         6,494,716      stalled-cycles-backend    #   51.70% backend cycles idle      ( +-  0.12% )
        25,661,906      instructions              #    2.04  insn per cycle         
                                                  #    0.25  stalled cycles per insn  ( +-  0.00% )
         2,649,939      branches                  #  380.848 M/sec                    ( +-  0.00% )
            22,786      branch-misses             #    0.86% of all branches          ( +-  0.12% )

         0.0073414 +- 0.0000753 seconds time elapsed  ( +-  1.03% )


 Performance counter stats for './run_interpreter_v3.out 5' (1000 runs):

              6.42 msec task-clock                #    0.945 CPUs utilized            ( +-  1.01% )
                 1      context-switches          #    0.082 K/sec                    ( +-  3.44% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                67      page-faults               #    0.011 M/sec                    ( +-  0.02% )
        11,403,422      cycles                    #    1.777 GHz                      ( +-  0.04% )
            57,608      stalled-cycles-frontend   #    0.51% frontend cycles idle     ( +-  0.64% )
         5,846,763      stalled-cycles-backend    #   51.27% backend cycles idle      ( +-  0.08% )
        29,357,045      instructions              #    2.57  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         2,682,365      branches                  #  418.078 M/sec                    ( +-  0.00% )
            23,004      branch-misses             #    0.86% of all branches          ( +-  0.11% )

         0.0067922 +- 0.0000670 seconds time elapsed  ( +-  0.99% )


 Performance counter stats for './run_interpreter_v4.out 5' (1000 runs):

              4.93 msec task-clock                #    0.937 CPUs utilized            ( +-  1.30% )
                 0      context-switches          #    0.093 K/sec                    ( +-  4.22% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                67      page-faults               #    0.014 M/sec                    ( +-  0.02% )
        10,395,766      cycles                    #    2.108 GHz                      ( +-  0.07% )
            62,525      stalled-cycles-frontend   #    0.60% frontend cycles idle     ( +-  0.66% )
         5,140,447      stalled-cycles-backend    #   49.45% backend cycles idle      ( +-  0.14% )
        26,279,059      instructions              #    2.53  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         2,458,178      branches                  #  498.391 M/sec                    ( +-  0.00% )
            26,537      branch-misses             #    1.08% of all branches          ( +-  0.11% )

         0.0052625 +- 0.0000668 seconds time elapsed  ( +-  1.27% )

### Senario 6
#### size 50000, seed 1, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 114.781366 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 48.973231 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 43.284736 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 42.381889 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 6' (1000 runs):

            120.35 msec task-clock                #    0.996 CPUs utilized            ( +-  0.10% )
                11      context-switches          #    0.095 K/sec                    ( +-  0.26% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 20.18% )
                36      page-faults               #    0.302 K/sec                    ( +-  0.04% )
       500,188,959      cycles                    #    4.156 GHz                      ( +-  0.04% )
           320,938      stalled-cycles-frontend   #    0.06% frontend cycles idle     ( +-  0.77% )
       222,769,303      stalled-cycles-backend    #   44.54% backend cycles idle      ( +-  0.10% )
     1,329,480,322      instructions              #    2.66  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.00% )
       162,693,304      branches                  # 1351.821 M/sec                    ( +-  0.00% )
           103,737      branch-misses             #    0.06% of all branches          ( +-  0.03% )

          0.120875 +- 0.000125 seconds time elapsed  ( +-  0.10% )


 Performance counter stats for './run_interpreter_v2.out 6' (1000 runs):

             57.01 msec task-clock                #    0.993 CPUs utilized            ( +-  0.20% )
                 6      context-switches          #    0.097 K/sec                    ( +-  0.54% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 21.52% )
                36      page-faults               #    0.638 K/sec                    ( +-  0.04% )
       222,184,581      cycles                    #    3.897 GHz                      ( +-  0.04% )
           219,102      stalled-cycles-frontend   #    0.10% frontend cycles idle     ( +-  0.89% )
       123,844,618      stalled-cycles-backend    #   55.74% backend cycles idle      ( +-  0.06% )
       493,283,305      instructions              #    2.22  insn per cycle         
                                                  #    0.25  stalled cycles per insn  ( +-  0.00% )
        49,187,046      branches                  #  862.756 M/sec                    ( +-  0.00% )
           105,675      branch-misses             #    0.21% of all branches          ( +-  0.03% )

          0.057440 +- 0.000114 seconds time elapsed  ( +-  0.20% )


 Performance counter stats for './run_interpreter_v3.out 6' (1000 runs):

             52.06 msec task-clock                #    0.991 CPUs utilized            ( +-  0.18% )
                 5      context-switches          #    0.096 K/sec                    ( +-  0.46% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 19.76% )
               232      page-faults               #    0.004 M/sec                    ( +-  0.01% )
       196,424,108      cycles                    #    3.773 GHz                      ( +-  0.02% )
           237,076      stalled-cycles-frontend   #    0.12% frontend cycles idle     ( +-  0.83% )
       113,317,872      stalled-cycles-backend    #   57.69% backend cycles idle      ( +-  0.04% )
       562,754,255      instructions              #    2.86  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        49,341,075      branches                  #  947.748 M/sec                    ( +-  0.00% )
           106,313      branch-misses             #    0.22% of all branches          ( +-  0.02% )

         0.0525161 +- 0.0000943 seconds time elapsed  ( +-  0.18% )


 Performance counter stats for './run_interpreter_v4.out 6' (1000 runs):

             51.50 msec task-clock                #    0.991 CPUs utilized            ( +-  0.18% )
                 5      context-switches          #    0.096 K/sec                    ( +-  0.46% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 35.23% )
               232      page-faults               #    0.005 M/sec                    ( +-  0.01% )
       192,487,141      cycles                    #    3.737 GHz                      ( +-  0.02% )
           243,346      stalled-cycles-frontend   #    0.13% frontend cycles idle     ( +-  0.40% )
       113,447,614      stalled-cycles-backend    #   58.94% backend cycles idle      ( +-  0.03% )
       550,803,391      instructions              #    2.86  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.00% )
        48,831,652      branches                  #  948.102 M/sec                    ( +-  0.00% )
           126,085      branch-misses             #    0.26% of all branches          ( +-  0.02% )

         0.0519870 +- 0.0000960 seconds time elapsed  ( +-  0.18% )

### Senario 7
#### size 50000, seed 2, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 15.129888 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 6.809585 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 6.047718 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 5.714163 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 7' (1000 runs):

             23.06 msec task-clock                #    0.982 CPUs utilized            ( +-  0.49% )
                 3      context-switches          #    0.109 K/sec                    ( +-  1.34% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 27.57% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        72,118,353      cycles                    #    3.128 GHz                      ( +-  0.07% )
           194,857      stalled-cycles-frontend   #    0.27% frontend cycles idle     ( +-  1.32% )
        29,090,103      stalled-cycles-backend    #   40.34% backend cycles idle      ( +-  0.05% )
       177,499,424      instructions              #    2.46  insn per cycle         
                                                  #    0.16  stalled cycles per insn  ( +-  0.00% )
        22,049,430      branches                  #  956.214 M/sec                    ( +-  0.00% )
           103,576      branch-misses             #    0.47% of all branches          ( +-  0.02% )

          0.023476 +- 0.000115 seconds time elapsed  ( +-  0.49% )


 Performance counter stats for './run_interpreter_v2.out 7' (1000 runs):

             15.77 msec task-clock                #    0.973 CPUs utilized            ( +-  0.44% )
                 2      context-switches          #    0.105 K/sec                    ( +-  1.28% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 57.68% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        35,502,333      cycles                    #    2.251 GHz                      ( +-  0.02% )
           156,268      stalled-cycles-frontend   #    0.44% frontend cycles idle     ( +-  0.30% )
        16,474,051      stalled-cycles-backend    #   46.40% backend cycles idle      ( +-  0.03% )
        69,746,869      instructions              #    1.96  insn per cycle         
                                                  #    0.24  stalled cycles per insn  ( +-  0.00% )
         7,387,343      branches                  #  468.390 M/sec                    ( +-  0.00% )
           105,569      branch-misses             #    1.43% of all branches          ( +-  0.02% )

         0.0162163 +- 0.0000712 seconds time elapsed  ( +-  0.44% )


 Performance counter stats for './run_interpreter_v3.out 7' (1000 runs):

             15.41 msec task-clock                #    0.971 CPUs utilized            ( +-  0.38% )
                 2      context-switches          #    0.103 K/sec                    ( +-  1.19% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 57.68% )
               232      page-faults               #    0.015 M/sec                    ( +-  0.01% )
        32,641,505      cycles                    #    2.119 GHz                      ( +-  0.02% )
           168,758      stalled-cycles-frontend   #    0.52% frontend cycles idle     ( +-  0.33% )
        15,317,525      stalled-cycles-backend    #   46.93% backend cycles idle      ( +-  0.04% )
        80,173,212      instructions              #    2.46  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         7,543,537      branches                  #  489.656 M/sec                    ( +-  0.00% )
           106,629      branch-misses             #    1.41% of all branches          ( +-  0.01% )

         0.0158606 +- 0.0000598 seconds time elapsed  ( +-  0.38% )


 Performance counter stats for './run_interpreter_v4.out 7' (1000 runs):

             12.83 msec task-clock                #    0.971 CPUs utilized            ( +-  0.92% )
                 1      context-switches          #    0.108 K/sec                    ( +-  2.26% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 26.55% )
               232      page-faults               #    0.018 M/sec                    ( +-  0.01% )
        31,843,447      cycles                    #    2.482 GHz                      ( +-  0.09% )
           206,441      stalled-cycles-frontend   #    0.65% frontend cycles idle     ( +-  1.15% )
        14,222,117      stalled-cycles-backend    #   44.66% backend cycles idle      ( +-  0.18% )
        76,066,058      instructions              #    2.39  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         7,349,237      branches                  #  572.853 M/sec                    ( +-  0.00% )
           125,620      branch-misses             #    1.71% of all branches          ( +-  0.03% )

          0.013208 +- 0.000121 seconds time elapsed  ( +-  0.91% )

### Senario 8
#### size 50000, seed 3, probabilities 1/9/1/5/5
interpreter_v1,Total wall-clock Time (CLOCK_MONOTONIC) = 25.828954 msec <br>
interpreter_v2,Total wall-clock Time (CLOCK_MONOTONIC) = 11.209537 msec <br>
interpreter_v3,Total wall-clock Time (CLOCK_MONOTONIC) = 10.025245 msec <br>
interpreter_v4,Total wall-clock Time (CLOCK_MONOTONIC) = 8.859035 msec <br>
 <br>
 Performance counter stats for './run_interpreter_v1.out 8' (1000 runs):

             33.58 msec task-clock                #    0.988 CPUs utilized            ( +-  0.35% )
                 3      context-switches          #    0.100 K/sec                    ( +-  0.95% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 22.15% )
                36      page-faults               #    0.001 M/sec                    ( +-  0.04% )
       118,450,759      cycles                    #    3.527 GHz                      ( +-  0.04% )
           214,332      stalled-cycles-frontend   #    0.18% frontend cycles idle     ( +-  1.09% )
        50,564,168      stalled-cycles-backend    #   42.69% backend cycles idle      ( +-  0.07% )
       300,735,842      instructions              #    2.54  insn per cycle         
                                                  #    0.17  stalled cycles per insn  ( +-  0.00% )
        37,192,468      branches                  # 1107.573 M/sec                    ( +-  0.00% )
           103,908      branch-misses             #    0.28% of all branches          ( +-  0.02% )

          0.033999 +- 0.000121 seconds time elapsed  ( +-  0.36% )


 Performance counter stats for './run_interpreter_v2.out 8' (1000 runs):

             18.76 msec task-clock                #    0.979 CPUs utilized            ( +-  0.61% )
                 2      context-switches          #    0.099 K/sec                    ( +-  1.73% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 28.71% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        55,928,825      cycles                    #    2.981 GHz                      ( +-  0.06% )
           175,136      stalled-cycles-frontend   #    0.31% frontend cycles idle     ( +-  0.75% )
        29,018,173      stalled-cycles-backend    #   51.88% backend cycles idle      ( +-  0.11% )
       114,546,362      instructions              #    2.05  insn per cycle         
                                                  #    0.25  stalled cycles per insn  ( +-  0.00% )
        11,620,862      branches                  #  619.462 M/sec                    ( +-  0.00% )
           105,757      branch-misses             #    0.91% of all branches          ( +-  0.03% )

          0.019166 +- 0.000117 seconds time elapsed  ( +-  0.61% )


 Performance counter stats for './run_interpreter_v3.out 8' (1000 runs):

             17.91 msec task-clock                #    0.977 CPUs utilized            ( +-  0.65% )
                 2      context-switches          #    0.095 K/sec                    ( +-  1.61% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 24.81% )
               232      page-faults               #    0.013 M/sec                    ( +-  0.01% )
        50,601,109      cycles                    #    2.825 GHz                      ( +-  0.05% )
           196,580      stalled-cycles-frontend   #    0.39% frontend cycles idle     ( +-  0.81% )
        25,703,742      stalled-cycles-backend    #   50.80% backend cycles idle      ( +-  0.11% )
       131,332,437      instructions              #    2.60  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        11,777,103      branches                  #  657.515 M/sec                    ( +-  0.00% )
           106,509      branch-misses             #    0.90% of all branches          ( +-  0.03% )

          0.018331 +- 0.000118 seconds time elapsed  ( +-  0.64% )


 Performance counter stats for './run_interpreter_v4.out 8' (1000 runs):

             16.42 msec task-clock                #    0.976 CPUs utilized            ( +-  0.72% )
                 2      context-switches          #    0.099 K/sec                    ( +-  2.08% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 26.34% )
               232      page-faults               #    0.014 M/sec                    ( +-  0.01% )
        45,576,690      cycles                    #    2.777 GHz                      ( +-  0.05% )
           213,548      stalled-cycles-frontend   #    0.47% frontend cycles idle     ( +-  1.17% )
        22,285,089      stalled-cycles-backend    #   48.90% backend cycles idle      ( +-  0.12% )
       115,856,159      instructions              #    2.54  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
        10,899,001      branches                  #  663.964 M/sec                    ( +-  0.00% )
           125,769      branch-misses             #    1.15% of all branches          ( +-  0.03% )

          0.016822 +- 0.000121 seconds time elapsed  ( +-  0.72% )
