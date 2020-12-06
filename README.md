# TUM-IN2125-VT

## Build & Check
* $ make clean
* $ make
* $ main.out

## Interpreters
* interpreter_v1: No optimization
* interpreter_v2: **Indirect threaded** interpretation
* interpreter_v3: **Predecoding** with **direct threaded** interpretation
* interpreter_v4: Reducing the number of jumps by using "**superevents**" (combinations of 2 original instructions in a row).

## Measurement
* $ main.out
* $ sudo perf stat -r 1000 \<target\>
* $ ./perfmyinterpreters \<senario\> \<interpreter no\> <rounds>

## Senario 1
### size 10000, seed 1, probabilities 0/1/0/0/0
 Performance counter stats for './run_interpreter_v1.out 1' (1000 runs):

             10.64 msec task-clock                #    0.966 CPUs utilized            ( +-  1.11% )
                 1      context-switches          #    0.113 K/sec                    ( +-  2.69% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 22.15% )
                27      page-faults               #    0.003 M/sec                    ( +-  0.06% )
        27,171,132      cycles                    #    2.554 GHz                      ( +-  0.19% )
            84,307      stalled-cycles-frontend   #    0.31% frontend cycles idle     ( +-  0.80% )
        13,734,575      stalled-cycles-backend    #   50.55% backend cycles idle      ( +-  0.08% )
        66,997,638      instructions              #    2.47  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.00% )
         8,277,741      branches                  #  778.137 M/sec                    ( +-  0.00% )
            22,854      branch-misses             #    0.28% of all branches          ( +-  0.13% )

          0.011014 +- 0.000121 seconds time elapsed  ( +-  1.10% )


 Performance counter stats for './run_interpreter_v2.out 1' (1000 runs):

              5.65 msec task-clock                #    0.946 CPUs utilized            ( +-  1.40% )
                 0      context-switches          #    0.088 K/sec                    ( +-  4.09% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 31.48% )
                27      page-faults               #    0.005 M/sec                    ( +-  0.06% )
        12,647,101      cycles                    #    2.240 GHz                      ( +-  0.10% )
            63,487      stalled-cycles-frontend   #    0.50% frontend cycles idle     ( +-  0.73% )
         7,011,963      stalled-cycles-backend    #   55.44% backend cycles idle      ( +-  0.14% )
        25,663,354      instructions              #    2.03  insn per cycle         
                                                  #    0.27  stalled cycles per insn  ( +-  0.00% )
         2,650,196      branches                  #  469.298 M/sec                    ( +-  0.00% )
            22,499      branch-misses             #    0.85% of all branches          ( +-  0.14% )

         0.0059693 +- 0.0000820 seconds time elapsed  ( +-  1.37% )


 Performance counter stats for './run_interpreter_v3.out 1' (1000 runs):

              5.33 msec task-clock                #    0.941 CPUs utilized            ( +-  1.37% )
                 1      context-switches          #    0.104 K/sec                    ( +-  4.56% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                67      page-faults               #    0.013 M/sec                    ( +-  0.02% )
        11,476,099      cycles                    #    2.153 GHz                      ( +-  0.07% )
            64,161      stalled-cycles-frontend   #    0.56% frontend cycles idle     ( +-  0.71% )
         5,775,589      stalled-cycles-backend    #   50.33% backend cycles idle      ( +-  0.19% )
        29,360,688      instructions              #    2.56  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         2,683,081      branches                  #  503.419 M/sec                    ( +-  0.00% )
            22,790      branch-misses             #    0.85% of all branches          ( +-  0.13% )

         0.0056619 +- 0.0000761 seconds time elapsed  ( +-  1.34% )


 Performance counter stats for './run_interpreter_v4.out 1' (1000 runs):

              4.66 msec task-clock                #    0.937 CPUs utilized            ( +-  1.35% )
                 0      context-switches          #    0.104 K/sec                    ( +-  4.75% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 35.23% )
                67      page-faults               #    0.014 M/sec                    ( +-  0.02% )
        10,519,642      cycles                    #    2.255 GHz                      ( +-  0.12% )
            73,408      stalled-cycles-frontend   #    0.70% frontend cycles idle     ( +-  1.04% )
         4,843,879      stalled-cycles-backend    #   46.05% backend cycles idle      ( +-  0.34% )
        26,284,153      instructions              #    2.50  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.00% )
         2,459,144      branches                  #  527.237 M/sec                    ( +-  0.00% )
            26,708      branch-misses             #    1.09% of all branches          ( +-  0.11% )

         0.0049765 +- 0.0000656 seconds time elapsed  ( +-  1.32% )

## Senario 2
### size 10000, seed 1, probabilities 1/1/1/0/0
 Performance counter stats for './run_interpreter_v1.out 2' (1000 runs):

              2.05 msec task-clock                #    0.864 CPUs utilized            ( +-  0.41% )
                 0      context-switches          #    0.061 K/sec                    ( +-  8.52% )
                 0      cpu-migrations            #    0.000 K/sec                  
                27      page-faults               #    0.013 M/sec                    ( +-  0.06% )
         2,994,341      cycles                    #    1.460 GHz                      ( +-  0.06% )
            46,920      stalled-cycles-frontend   #    1.57% frontend cycles idle     ( +-  0.28% )
           419,183      stalled-cycles-backend    #   14.00% backend cycles idle      ( +-  0.39% )
         3,763,056      instructions              #    1.26  insn per cycle         
                                                  #    0.11  stalled cycles per insn  ( +-  0.01% )
           617,579      branches                  #  301.215 M/sec                    ( +-  0.01% )
            28,917      branch-misses             #    4.68% of all branches          ( +-  0.05% )

        0.00237420 +- 0.00000902 seconds time elapsed  ( +-  0.38% )


 Performance counter stats for './run_interpreter_v2.out 2' (1000 runs):

              1.87 msec task-clock                #    0.853 CPUs utilized            ( +-  0.40% )
                 0      context-switches          #    0.066 K/sec                    ( +-  8.56% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +-100.00% )
                27      page-faults               #    0.015 M/sec                    ( +-  0.06% )
         2,772,331      cycles                    #    1.480 GHz                      ( +-  0.06% )
            46,599      stalled-cycles-frontend   #    1.68% frontend cycles idle     ( +-  0.26% )
           430,667      stalled-cycles-backend    #   15.53% backend cycles idle      ( +-  0.36% )
         3,343,175      instructions              #    1.21  insn per cycle         
                                                  #    0.13  stalled cycles per insn  ( +-  0.01% )
           558,380      branches                  #  298.050 M/sec                    ( +-  0.01% )
            29,146      branch-misses             #    5.22% of all branches          ( +-  0.04% )

        0.00219595 +- 0.00000822 seconds time elapsed  ( +-  0.37% )


 Performance counter stats for './run_interpreter_v3.out 2' (1000 runs):

              1.80 msec task-clock                #    0.856 CPUs utilized            ( +-  0.72% )
                 0      context-switches          #    0.064 K/sec                    ( +-  8.99% )
                 0      cpu-migrations            #    0.000 K/sec                  
                67      page-faults               #    0.037 M/sec                    ( +-  0.02% )
         2,842,182      cycles                    #    1.577 GHz                      ( +-  0.10% )
            50,002      stalled-cycles-frontend   #    1.76% frontend cycles idle     ( +-  0.44% )
           472,490      stalled-cycles-backend    #   16.62% backend cycles idle      ( +-  0.38% )
         3,727,262      instructions              #    1.31  insn per cycle         
                                                  #    0.13  stalled cycles per insn  ( +-  0.01% )
           591,249      branches                  #  328.067 M/sec                    ( +-  0.01% )
            29,255      branch-misses             #    4.95% of all branches          ( +-  0.05% )

         0.0021064 +- 0.0000146 seconds time elapsed  ( +-  0.69% )


 Performance counter stats for './run_interpreter_v4.out 2' (1000 runs):

              1.87 msec task-clock                #    0.855 CPUs utilized            ( +-  0.55% )
                 0      context-switches          #    0.075 K/sec                    ( +-  7.81% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 70.68% )
                67      page-faults               #    0.036 M/sec                    ( +-  0.02% )
         2,904,298      cycles                    #    1.553 GHz                      ( +-  0.09% )
            52,462      stalled-cycles-frontend   #    1.81% frontend cycles idle     ( +-  0.35% )
           428,697      stalled-cycles-backend    #   14.76% backend cycles idle      ( +-  0.42% )
         3,812,030      instructions              #    1.31  insn per cycle         
                                                  #    0.11  stalled cycles per insn  ( +-  0.01% )
           605,236      branches                  #  323.672 M/sec                    ( +-  0.01% )
            31,637      branch-misses             #    5.23% of all branches          ( +-  0.05% )

         0.0021859 +- 0.0000115 seconds time elapsed  ( +-  0.52% )

## Senario 3
### size 10000, seed 1, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 3' (1000 runs):

             11.02 msec task-clock                #    0.966 CPUs utilized            ( +-  1.09% )
                 1      context-switches          #    0.105 K/sec                    ( +-  2.25% )
                 0      cpu-migrations            #    0.002 K/sec                    ( +- 24.06% )
                27      page-faults               #    0.002 M/sec                    ( +-  0.06% )
        26,844,105      cycles                    #    2.436 GHz                      ( +-  0.14% )
            81,361      stalled-cycles-frontend   #    0.30% frontend cycles idle     ( +-  0.67% )
        13,777,907      stalled-cycles-backend    #   51.33% backend cycles idle      ( +-  0.06% )
        66,996,226      instructions              #    2.50  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.00% )
         8,277,383      branches                  #  751.288 M/sec                    ( +-  0.00% )
            22,769      branch-misses             #    0.28% of all branches          ( +-  0.13% )

          0.011408 +- 0.000124 seconds time elapsed  ( +-  1.08% )


 Performance counter stats for './run_interpreter_v2.out 3' (1000 runs):

              7.87 msec task-clock                #    0.947 CPUs utilized            ( +-  0.71% )
                 1      context-switches          #    0.085 K/sec                    ( +-  2.79% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 44.63% )
                27      page-faults               #    0.003 M/sec                    ( +-  0.06% )
        12,566,148      cycles                    #    1.597 GHz                      ( +-  0.05% )
            59,653      stalled-cycles-frontend   #    0.47% frontend cycles idle     ( +-  0.62% )
         7,077,130      stalled-cycles-backend    #   56.32% backend cycles idle      ( +-  0.06% )
        25,666,824      instructions              #    2.04  insn per cycle         
                                                  #    0.28  stalled cycles per insn  ( +-  0.00% )
         2,650,849      branches                  #  336.943 M/sec                    ( +-  0.00% )
            23,099      branch-misses             #    0.87% of all branches          ( +-  0.09% )

         0.0083067 +- 0.0000576 seconds time elapsed  ( +-  0.69% )


 Performance counter stats for './run_interpreter_v3.out 3' (1000 runs):

              7.06 msec task-clock                #    0.943 CPUs utilized            ( +-  0.78% )
                 1      context-switches          #    0.073 K/sec                    ( +-  3.48% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 49.92% )
                67      page-faults               #    0.010 M/sec                    ( +-  0.02% )
        11,382,968      cycles                    #    1.613 GHz                      ( +-  0.04% )
            59,994      stalled-cycles-frontend   #    0.53% frontend cycles idle     ( +-  0.63% )
         5,807,705      stalled-cycles-backend    #   51.02% backend cycles idle      ( +-  0.10% )
        29,362,206      instructions              #    2.58  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         2,683,284      branches                  #  380.326 M/sec                    ( +-  0.00% )
            23,293      branch-misses             #    0.87% of all branches          ( +-  0.10% )

         0.0074787 +- 0.0000569 seconds time elapsed  ( +-  0.76% )


 Performance counter stats for './run_interpreter_v4.out 3' (1000 runs):

              5.98 msec task-clock                #    0.937 CPUs utilized            ( +-  0.91% )
                 1      context-switches          #    0.085 K/sec                    ( +-  3.45% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 70.68% )
                67      page-faults               #    0.011 M/sec                    ( +-  0.02% )
        10,363,841      cycles                    #    1.733 GHz                      ( +-  0.05% )
            62,800      stalled-cycles-frontend   #    0.61% frontend cycles idle     ( +-  0.57% )
         4,951,091      stalled-cycles-backend    #   47.77% backend cycles idle      ( +-  0.10% )
        26,284,439      instructions              #    2.54  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         2,459,138      branches                  #  411.253 M/sec                    ( +-  0.00% )
            26,974      branch-misses             #    1.10% of all branches          ( +-  0.10% )

         0.0063783 +- 0.0000560 seconds time elapsed  ( +-  0.88% )

## Senario 4
### size 10000, seed 2, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 4' (1000 runs):

              5.66 msec task-clock                #    0.943 CPUs utilized            ( +-  1.26% )
                 1      context-switches          #    0.100 K/sec                    ( +-  4.58% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 35.23% )
                27      page-faults               #    0.005 M/sec                    ( +-  0.06% )
        11,466,421      cycles                    #    2.025 GHz                      ( +-  0.15% )
            58,984      stalled-cycles-frontend   #    0.51% frontend cycles idle     ( +-  0.64% )
         5,422,134      stalled-cycles-backend    #   47.29% backend cycles idle      ( +-  0.11% )
        26,626,938      instructions              #    2.32  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         3,343,953      branches                  #  590.623 M/sec                    ( +-  0.00% )
            22,593      branch-misses             #    0.68% of all branches          ( +-  0.12% )

         0.0060050 +- 0.0000741 seconds time elapsed  ( +-  1.23% )


 Performance counter stats for './run_interpreter_v2.out 4' (1000 runs):

              3.49 msec task-clock                #    0.909 CPUs utilized            ( +-  0.69% )
                 0      context-switches          #    0.083 K/sec                    ( +-  5.29% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                27      page-faults               #    0.008 M/sec                    ( +-  0.06% )
         5,885,668      cycles                    #    1.686 GHz                      ( +-  0.07% )
            46,476      stalled-cycles-frontend   #    0.79% frontend cycles idle     ( +-  0.55% )
         2,806,136      stalled-cycles-backend    #   47.68% backend cycles idle      ( +-  0.08% )
        10,857,082      instructions              #    1.84  insn per cycle         
                                                  #    0.26  stalled cycles per insn  ( +-  0.00% )
         1,199,005      branches                  #  343.414 M/sec                    ( +-  0.00% )
            22,067      branch-misses             #    1.84% of all branches          ( +-  0.10% )

         0.0038408 +- 0.0000255 seconds time elapsed  ( +-  0.66% )


 Performance counter stats for './run_interpreter_v3.out 4' (1000 runs):

              3.17 msec task-clock                #    0.904 CPUs utilized            ( +-  0.83% )
                 0      context-switches          #    0.098 K/sec                    ( +-  5.02% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +-100.00% )
                67      page-faults               #    0.021 M/sec                    ( +-  0.02% )
         5,523,260      cycles                    #    1.740 GHz                      ( +-  0.08% )
            50,522      stalled-cycles-frontend   #    0.91% frontend cycles idle     ( +-  0.59% )
         2,409,970      stalled-cycles-backend    #   43.63% backend cycles idle      ( +-  0.14% )
        12,481,810      instructions              #    2.26  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         1,231,771      branches                  #  388.071 M/sec                    ( +-  0.00% )
            22,469      branch-misses             #    1.82% of all branches          ( +-  0.10% )

         0.0035128 +- 0.0000284 seconds time elapsed  ( +-  0.81% )


 Performance counter stats for './run_interpreter_v4.out 4' (1000 runs):

              2.99 msec task-clock                #    0.901 CPUs utilized            ( +-  0.96% )
                 0      context-switches          #    0.091 K/sec                    ( +-  5.37% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 70.68% )
                67      page-faults               #    0.023 M/sec                    ( +-  0.02% )
         5,343,171      cycles                    #    1.785 GHz                      ( +-  0.08% )
            54,936      stalled-cycles-frontend   #    1.03% frontend cycles idle     ( +-  0.62% )
         2,109,365      stalled-cycles-backend    #   39.48% backend cycles idle      ( +-  0.15% )
        11,788,245      instructions              #    2.21  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.00% )
         1,195,847      branches                  #  399.427 M/sec                    ( +-  0.00% )
            26,330      branch-misses             #    2.20% of all branches          ( +-  0.09% )

         0.0033221 +- 0.0000310 seconds time elapsed  ( +-  0.93% )

## Senario 5
### size 10000, seed 3, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 5' (1000 runs):

             11.54 msec task-clock                #    0.965 CPUs utilized            ( +-  1.00% )
                 1      context-switches          #    0.107 K/sec                    ( +-  2.11% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 40.72% )
                27      page-faults               #    0.002 M/sec                    ( +-  0.06% )
        26,777,920      cycles                    #    2.320 GHz                      ( +-  0.12% )
            80,962      stalled-cycles-frontend   #    0.30% frontend cycles idle     ( +-  0.67% )
        13,774,609      stalled-cycles-backend    #   51.44% backend cycles idle      ( +-  0.08% )
        66,996,849      instructions              #    2.50  insn per cycle         
                                                  #    0.21  stalled cycles per insn  ( +-  0.00% )
         8,277,536      branches                  #  717.047 M/sec                    ( +-  0.00% )
            22,947      branch-misses             #    0.28% of all branches          ( +-  0.12% )

          0.011967 +- 0.000119 seconds time elapsed  ( +-  0.99% )


 Performance counter stats for './run_interpreter_v2.out 5' (1000 runs):

              6.92 msec task-clock                #    0.948 CPUs utilized            ( +-  1.12% )
                 1      context-switches          #    0.092 K/sec                    ( +-  3.08% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 49.92% )
                27      page-faults               #    0.004 M/sec                    ( +-  0.06% )
        12,598,291      cycles                    #    1.820 GHz                      ( +-  0.08% )
            61,322      stalled-cycles-frontend   #    0.49% frontend cycles idle     ( +-  0.65% )
         7,053,805      stalled-cycles-backend    #   55.99% backend cycles idle      ( +-  0.08% )
        25,665,618      instructions              #    2.04  insn per cycle         
                                                  #    0.27  stalled cycles per insn  ( +-  0.00% )
         2,650,619      branches                  #  382.942 M/sec                    ( +-  0.00% )
            22,736      branch-misses             #    0.86% of all branches          ( +-  0.13% )

         0.0073026 +- 0.0000806 seconds time elapsed  ( +-  1.10% )


 Performance counter stats for './run_interpreter_v3.out 5' (1000 runs):

              6.33 msec task-clock                #    0.942 CPUs utilized            ( +-  1.08% )
                 1      context-switches          #    0.083 K/sec                    ( +-  4.19% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 44.63% )
                67      page-faults               #    0.011 M/sec                    ( +-  0.02% )
        11,393,665      cycles                    #    1.801 GHz                      ( +-  0.05% )
            61,190      stalled-cycles-frontend   #    0.54% frontend cycles idle     ( +-  0.68% )
         5,822,632      stalled-cycles-backend    #   51.10% backend cycles idle      ( +-  0.10% )
        29,361,317      instructions              #    2.58  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         2,683,099      branches                  #  424.080 M/sec                    ( +-  0.00% )
            22,969      branch-misses             #    0.86% of all branches          ( +-  0.13% )

         0.0067162 +- 0.0000711 seconds time elapsed  ( +-  1.06% )


 Performance counter stats for './run_interpreter_v4.out 5' (1000 runs):

              5.95 msec task-clock                #    0.937 CPUs utilized            ( +-  0.97% )
                 0      context-switches          #    0.083 K/sec                    ( +-  3.60% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 57.68% )
                67      page-faults               #    0.011 M/sec                    ( +-  0.02% )
        10,370,692      cycles                    #    1.742 GHz                      ( +-  0.04% )
            63,964      stalled-cycles-frontend   #    0.62% frontend cycles idle     ( +-  0.52% )
         4,960,798      stalled-cycles-backend    #   47.83% backend cycles idle      ( +-  0.08% )
        26,285,257      instructions              #    2.53  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
         2,459,246      branches                  #  412.972 M/sec                    ( +-  0.00% )
            27,055      branch-misses             #    1.10% of all branches          ( +-  0.10% )

         0.0063543 +- 0.0000598 seconds time elapsed  ( +-  0.94% )

## Senario 6
### size 50000, seed 1, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 6' (1000 runs):

             34.27 msec task-clock                #    0.986 CPUs utilized            ( +-  0.30% )
                 4      context-switches          #    0.107 K/sec                    ( +-  1.35% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 20.39% )
                36      page-faults               #    0.001 M/sec                    ( +-  0.04% )
       118,176,951      cycles                    #    3.449 GHz                      ( +-  0.06% )
           231,167      stalled-cycles-frontend   #    0.20% frontend cycles idle     ( +-  0.89% )
        61,593,946      stalled-cycles-backend    #   52.12% backend cycles idle      ( +-  0.04% )
       300,751,022      instructions              #    2.54  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        37,195,455      branches                  # 1085.416 M/sec                    ( +-  0.00% )
           104,593      branch-misses             #    0.28% of all branches          ( +-  0.02% )

          0.034750 +- 0.000105 seconds time elapsed  ( +-  0.30% )


 Performance counter stats for './run_interpreter_v2.out 6' (1000 runs):

             20.03 msec task-clock                #    0.977 CPUs utilized            ( +-  0.40% )
                 2      context-switches          #    0.093 K/sec                    ( +-  1.19% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 28.71% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        55,688,475      cycles                    #    2.781 GHz                      ( +-  0.03% )
           188,231      stalled-cycles-frontend   #    0.34% frontend cycles idle     ( +-  0.37% )
        31,817,108      stalled-cycles-backend    #   57.13% backend cycles idle      ( +-  0.03% )
       114,553,246      instructions              #    2.06  insn per cycle         
                                                  #    0.28  stalled cycles per insn  ( +-  0.00% )
        11,622,057      branches                  #  580.321 M/sec                    ( +-  0.00% )
           105,873      branch-misses             #    0.91% of all branches          ( +-  0.02% )

         0.0205040 +- 0.0000820 seconds time elapsed  ( +-  0.40% )


 Performance counter stats for './run_interpreter_v3.out 6' (1000 runs):

             19.15 msec task-clock                #    0.975 CPUs utilized            ( +-  0.40% )
                 2      context-switches          #    0.096 K/sec                    ( +-  1.11% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 33.20% )
               232      page-faults               #    0.012 M/sec                    ( +-  0.01% )
        50,297,790      cycles                    #    2.627 GHz                      ( +-  0.03% )
           201,147      stalled-cycles-frontend   #    0.40% frontend cycles idle     ( +-  0.37% )
        26,356,157      stalled-cycles-backend    #   52.40% backend cycles idle      ( +-  0.04% )
       131,338,012      instructions              #    2.61  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        11,778,159      branches                  #  615.057 M/sec                    ( +-  0.00% )
           106,782      branch-misses             #    0.91% of all branches          ( +-  0.01% )

         0.0196447 +- 0.0000781 seconds time elapsed  ( +-  0.40% )


 Performance counter stats for './run_interpreter_v4.out 6' (1000 runs):

             17.88 msec task-clock                #    0.973 CPUs utilized            ( +-  0.44% )
                 2      context-switches          #    0.091 K/sec                    ( +-  1.23% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 33.20% )
               232      page-faults               #    0.013 M/sec                    ( +-  0.01% )
        45,250,428      cycles                    #    2.530 GHz                      ( +-  0.03% )
           217,866      stalled-cycles-frontend   #    0.48% frontend cycles idle     ( +-  0.37% )
        21,429,421      stalled-cycles-backend    #   47.36% backend cycles idle      ( +-  0.06% )
       115,860,581      instructions              #    2.56  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.00% )
        10,899,768      branches                  #  609.443 M/sec                    ( +-  0.00% )
           126,254      branch-misses             #    1.16% of all branches          ( +-  0.01% )

         0.0183802 +- 0.0000789 seconds time elapsed  ( +-  0.43% )

## Senario 7
### size 50000, seed 2, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 7' (1000 runs):

             24.25 msec task-clock                #    0.981 CPUs utilized            ( +-  0.26% )
                 3      context-switches          #    0.109 K/sec                    ( +-  0.75% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 40.72% )
                36      page-faults               #    0.001 M/sec                    ( +-  0.04% )
        71,699,259      cycles                    #    2.957 GHz                      ( +-  0.02% )
           194,898      stalled-cycles-frontend   #    0.27% frontend cycles idle     ( +-  0.34% )
        36,140,976      stalled-cycles-backend    #   50.41% backend cycles idle      ( +-  0.04% )
       177,508,815      instructions              #    2.48  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        22,051,139      branches                  #  909.363 M/sec                    ( +-  0.00% )
           104,478      branch-misses             #    0.47% of all branches          ( +-  0.01% )

         0.0247288 +- 0.0000626 seconds time elapsed  ( +-  0.25% )


 Performance counter stats for './run_interpreter_v2.out 7' (1000 runs):

             16.02 msec task-clock                #    0.971 CPUs utilized            ( +-  0.38% )
                 2      context-switches          #    0.107 K/sec                    ( +-  1.05% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 30.00% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        35,448,688      cycles                    #    2.213 GHz                      ( +-  0.02% )
           171,456      stalled-cycles-frontend   #    0.48% frontend cycles idle     ( +-  0.34% )
        18,487,772      stalled-cycles-backend    #   52.15% backend cycles idle      ( +-  0.04% )
        69,754,402      instructions              #    1.97  insn per cycle         
                                                  #    0.27  stalled cycles per insn  ( +-  0.00% )
         7,388,704      branches                  #  461.261 M/sec                    ( +-  0.00% )
           105,656      branch-misses             #    1.43% of all branches          ( +-  0.01% )

         0.0165013 +- 0.0000620 seconds time elapsed  ( +-  0.38% )


 Performance counter stats for './run_interpreter_v3.out 7' (1000 runs):

             15.49 msec task-clock                #    0.970 CPUs utilized            ( +-  0.39% )
                 2      context-switches          #    0.106 K/sec                    ( +-  1.09% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 49.92% )
               232      page-faults               #    0.015 M/sec                    ( +-  0.01% )
        32,494,994      cycles                    #    2.097 GHz                      ( +-  0.02% )
           175,844      stalled-cycles-frontend   #    0.54% frontend cycles idle     ( +-  0.23% )
        15,693,747      stalled-cycles-backend    #   48.30% backend cycles idle      ( +-  0.03% )
        80,179,872      instructions              #    2.47  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
         7,544,738      branches                  #  486.976 M/sec                    ( +-  0.00% )
           106,704      branch-misses             #    1.41% of all branches          ( +-  0.01% )

         0.0159727 +- 0.0000608 seconds time elapsed  ( +-  0.38% )


 Performance counter stats for './run_interpreter_v4.out 7' (1000 runs):

             15.13 msec task-clock                #    0.970 CPUs utilized            ( +-  0.44% )
                 2      context-switches          #    0.107 K/sec                    ( +-  1.17% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 49.92% )
               232      page-faults               #    0.015 M/sec                    ( +-  0.01% )
        31,392,047      cycles                    #    2.074 GHz                      ( +-  0.03% )
           197,517      stalled-cycles-frontend   #    0.63% frontend cycles idle     ( +-  0.23% )
        13,709,712      stalled-cycles-backend    #   43.67% backend cycles idle      ( +-  0.05% )
        76,071,604      instructions              #    2.42  insn per cycle         
                                                  #    0.18  stalled cycles per insn  ( +-  0.00% )
         7,350,263      branches                  #  485.710 M/sec                    ( +-  0.00% )
           126,369      branch-misses             #    1.72% of all branches          ( +-  0.01% )

         0.0156032 +- 0.0000681 seconds time elapsed  ( +-  0.44% )

## Senario 8
### size 50000, seed 3, probabilities 1/9/1/5/5
 Performance counter stats for './run_interpreter_v1.out 8' (1000 runs):

             33.87 msec task-clock                #    0.987 CPUs utilized            ( +-  0.34% )
                 4      context-switches          #    0.107 K/sec                    ( +-  1.22% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 17.18% )
                36      page-faults               #    0.001 M/sec                    ( +-  0.04% )
       118,507,901      cycles                    #    3.499 GHz                      ( +-  0.07% )
           228,666      stalled-cycles-frontend   #    0.19% frontend cycles idle     ( +-  0.78% )
        61,583,547      stalled-cycles-backend    #   51.97% backend cycles idle      ( +-  0.07% )
       300,749,568      instructions              #    2.54  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        37,195,171      branches                  # 1098.134 M/sec                    ( +-  0.00% )
           104,544      branch-misses             #    0.28% of all branches          ( +-  0.02% )

          0.034334 +- 0.000116 seconds time elapsed  ( +-  0.34% )


 Performance counter stats for './run_interpreter_v2.out 8' (1000 runs):

             20.25 msec task-clock                #    0.976 CPUs utilized            ( +-  0.32% )
                 2      context-switches          #    0.092 K/sec                    ( +-  1.14% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 44.63% )
                36      page-faults               #    0.002 M/sec                    ( +-  0.04% )
        55,599,028      cycles                    #    2.745 GHz                      ( +-  0.02% )
           186,593      stalled-cycles-frontend   #    0.34% frontend cycles idle     ( +-  0.33% )
        31,816,611      stalled-cycles-backend    #   57.23% backend cycles idle      ( +-  0.03% )
       114,552,077      instructions              #    2.06  insn per cycle         
                                                  #    0.28  stalled cycles per insn  ( +-  0.00% )
        11,621,858      branches                  #  573.813 M/sec                    ( +-  0.00% )
           105,889      branch-misses             #    0.91% of all branches          ( +-  0.01% )

         0.0207449 +- 0.0000656 seconds time elapsed  ( +-  0.32% )


 Performance counter stats for './run_interpreter_v3.out 8' (1000 runs):

             19.45 msec task-clock                #    0.975 CPUs utilized            ( +-  0.35% )
                 2      context-switches          #    0.097 K/sec                    ( +-  1.01% )
                 0      cpu-migrations            #    0.001 K/sec                    ( +- 28.41% )
               232      page-faults               #    0.012 M/sec                    ( +-  0.01% )
        50,285,925      cycles                    #    2.586 GHz                      ( +-  0.02% )
           203,372      stalled-cycles-frontend   #    0.40% frontend cycles idle     ( +-  0.80% )
        26,370,438      stalled-cycles-backend    #   52.44% backend cycles idle      ( +-  0.03% )
       131,338,276      instructions              #    2.61  insn per cycle         
                                                  #    0.20  stalled cycles per insn  ( +-  0.00% )
        11,778,233      branches                  #  605.623 M/sec                    ( +-  0.00% )
           106,840      branch-misses             #    0.91% of all branches          ( +-  0.01% )

         0.0199537 +- 0.0000698 seconds time elapsed  ( +-  0.35% )


 Performance counter stats for './run_interpreter_v4.out 8' (1000 runs):

             18.31 msec task-clock                #    0.973 CPUs utilized            ( +-  0.34% )
                 2      context-switches          #    0.089 K/sec                    ( +-  1.15% )
                 0      cpu-migrations            #    0.000 K/sec                    ( +- 44.63% )
               232      page-faults               #    0.013 M/sec                    ( +-  0.01% )
        45,200,790      cycles                    #    2.469 GHz                      ( +-  0.02% )
           218,432      stalled-cycles-frontend   #    0.48% frontend cycles idle     ( +-  0.34% )
        21,470,589      stalled-cycles-backend    #   47.50% backend cycles idle      ( +-  0.04% )
       115,860,197      instructions              #    2.56  insn per cycle         
                                                  #    0.19  stalled cycles per insn  ( +-  0.00% )
        10,899,691      branches                  #  595.345 M/sec                    ( +-  0.00% )
           126,286      branch-misses             #    1.16% of all branches          ( +-  0.01% )

         0.0188221 +- 0.0000630 seconds time elapsed  ( +-  0.33% )
