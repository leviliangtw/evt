# TUM-IN2125-VT

## Build
* $ make clean
* $ make

## Measurement
* $ main.out
* $ sudo perf stat -r 1000 \<TARGET\>

## Senario 1
```
 Performance counter stats for './run_interpreter_v2.out' (1000 runs):

              0.42 msec task-clock                #    0.634 CPUs utilized            ( +-  0.50% )
                 0      context-switches          #    0.072 K/sec                    ( +- 21.38% )
                 0      cpu-migrations            #    0.000 K/sec                  
                28      page-faults               #    0.068 M/sec                    ( +-  0.05% )
           703,986      cycles                    #    1.688 GHz                      ( +-  0.25% )
            17,063      stalled-cycles-frontend   #    2.42% frontend cycles idle     ( +-  1.02% )
           299,242      stalled-cycles-backend    #   42.51% backend cycles idle      ( +-  0.31% )
         1,261,138      instructions              #    1.79  insn per cycle         
                                                  #    0.24  stalled cycles per insn  ( +-  0.01% )
           204,119      branches                  #  489.441 M/sec                    ( +-  0.01% )
             1,377      branch-misses             #    0.67% of all branches          ( +-  0.94% )

        0.00065811 +- 0.00000368 seconds time elapsed  ( +-  0.56% )
```
## Senario 2
```
 Performance counter stats for './run_interpreter_v2.out' (1000 runs):

              0.70 msec task-clock                #    0.761 CPUs utilized            ( +-  0.93% )
                 0      context-switches          #    0.105 K/sec                    ( +- 13.42% )
                 0      cpu-migrations            #    0.000 K/sec                  
                28      page-faults               #    0.040 M/sec                    ( +-  0.05% )
         1,327,904      cycles                    #    1.887 GHz                      ( +-  0.18% )
            31,805      stalled-cycles-frontend   #    2.40% frontend cycles idle     ( +-  0.61% )
           223,113      stalled-cycles-backend    #   16.80% backend cycles idle      ( +-  0.36% )
         1,253,407      instructions              #    0.94  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.02% )
           201,201      branches                  #  285.929 M/sec                    ( +-  0.02% )
            14,861      branch-misses             #    7.39% of all branches          ( +-  0.09% )

        0.00092432 +- 0.00000851 seconds time elapsed  ( +-  0.92% )
```
## Senario 3
```
 Performance counter stats for './run_interpreter_v2.out' (1000 runs):

              3.73 msec task-clock                #    0.932 CPUs utilized            ( +-  1.49% )
                 0      context-switches          #    0.119 K/sec                    ( +-  5.52% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                28      page-faults               #    0.008 M/sec                    ( +-  0.05% )
         9,399,262      cycles                    #    2.518 GHz                      ( +-  0.10% )
            59,363      stalled-cycles-frontend   #    0.63% frontend cycles idle     ( +-  0.76% )
         4,988,694      stalled-cycles-backend    #   53.08% backend cycles idle      ( +-  0.16% )
        18,282,155      instructions              #    1.95  insn per cycle         
                                                  #    0.27  stalled cycles per insn  ( +-  0.00% )
         1,893,718      branches                  #  507.325 M/sec                    ( +-  0.00% )
            22,467      branch-misses             #    1.19% of all branches          ( +-  0.11% )

         0.0040067 +- 0.0000588 seconds time elapsed  ( +-  1.47% )
```
## Senario 4
```
 Performance counter stats for './run_interpreter_v2.out' (1000 runs):

              2.54 msec task-clock                #    0.908 CPUs utilized            ( +-  1.46% )
                 0      context-switches          #    0.105 K/sec                    ( +-  7.58% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 44.63% )
                28      page-faults               #    0.011 M/sec                    ( +-  0.05% )
         5,914,248      cycles                    #    2.328 GHz                      ( +-  0.10% )
            50,188      stalled-cycles-frontend   #    0.85% frontend cycles idle     ( +-  0.58% )
         2,808,063      stalled-cycles-backend    #   47.48% backend cycles idle      ( +-  0.15% )
        10,877,064      instructions              #    1.84  insn per cycle         
                                                  #    0.26  stalled cycles per insn  ( +-  0.00% )
         1,202,869      branches                  #  473.544 M/sec                    ( +-  0.00% )
            22,114      branch-misses             #    1.84% of all branches          ( +-  0.11% )

         0.0027964 +- 0.0000403 seconds time elapsed  ( +-  1.44% )
```
## Senario 5
```
 Performance counter stats for './run_interpreter_v2.out' (1000 runs):

              5.71 msec task-clock                #    0.949 CPUs utilized            ( +-  1.34% )
                 1      context-switches          #    0.088 K/sec                    ( +-  6.80% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 28.71% )
                28      page-faults               #    0.005 M/sec                    ( +-  0.05% )
        12,508,932      cycles                    #    2.190 GHz                      ( +-  0.06% )
            59,865      stalled-cycles-frontend   #    0.48% frontend cycles idle     ( +-  0.61% )
         7,037,846      stalled-cycles-backend    #   56.26% backend cycles idle      ( +-  0.08% )
        25,683,475      instructions              #    2.05  insn per cycle         
                                                  #    0.27  stalled cycles per insn  ( +-  0.00% )
         2,654,072      branches                  #  464.757 M/sec                    ( +-  0.00% )
            22,494      branch-misses             #    0.85% of all branches          ( +-  0.13% )

         0.0060169 +- 0.0000790 seconds time elapsed  ( +-  1.31% )
```
## Senario 6
```

```
## Senario 7
```

```
## Senario 8
```

```