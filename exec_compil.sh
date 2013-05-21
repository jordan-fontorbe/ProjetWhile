#!/bin/bash
./bin/compiler $1
dot -Tps AST.dot -o $2
