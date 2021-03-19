DIR_BIN = .
DIR_OBJ = ./obj
DIR_GEN = ./generator
DIR_INT = ./interpreter
DIR_BT = ./binary_translator

BIN_SRC = $(wildcard ${DIR_BIN}/*.c)
BIN_TGT = $(patsubst %.c, %, $(wildcard ${DIR_BIN}/*.c))
SRC = $(wildcard ${DIR_GEN}/*.c ${DIR_INT}/*.c ${DIR_BT}/*.c)
# OBJ = $(patsubst %.c, ${DIR_OBJ}/%.o, $(notdir ${SRC})) 

CC = gcc
# CFLAGS = -g -Wall -I${DIR_GEN} -I${DIR_INT}
CFLAGS = -g -I${DIR_GEN} -I${DIR_INT} -I${DIR_BT}

ALL:$(BIN_TGT)

test:
	@echo $(BIN_TGT)
	@echo $(BIN_SRC)
	@echo $(SRC)

${BIN_TGT}:%:%.c
	$(CC) $< ${SRC} $(CFLAGS) -o $@.out
    
# ${DIR_OBJ}/%.o: ${SRC}
# 	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	find ./ -name "*.out" -exec rm -rf {} \;