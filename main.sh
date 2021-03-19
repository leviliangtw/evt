#!/bin/bash

ROUNDS=1

if [ $# -eq 1 ]; then
	ROUNDS=$1
fi

for i in {1..8}; do
	./main.out ${ROUNDS} ${i};
done;

exit 0
