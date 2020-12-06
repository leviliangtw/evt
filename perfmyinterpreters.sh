#!/bin/bash

ROUNDS=1000
SENARIO=0

if [ $# -eq 3 ]; then
	ROUNDS=$3
fi

if [ $# -eq 0 ]; then
	echo "$ ./perfmyinterpreter <senario> <interpreter no> <rounds>"
	exit 1
elif [ $# -gt 1 ]; then
	echo "Senario: $1"
	SENARIO=$1
	sudo perf stat -r ${ROUNDS} ./run_interpreter_v$2.out ${SENARIO};
	exit 0
else
	echo "Senario: $1"
	SENARIO=$1
fi

sudo perf stat -r ${ROUNDS} ./run_interpreter_v1.out ${SENARIO}; 
sudo perf stat -r ${ROUNDS} ./run_interpreter_v2.out ${SENARIO}; 
sudo perf stat -r ${ROUNDS} ./run_interpreter_v3.out ${SENARIO}; 
sudo perf stat -r ${ROUNDS} ./run_interpreter_v4.out ${SENARIO};

exit 0
