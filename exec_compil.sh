#!/bin/bash
./bin/compiler $1
dot -Tpng AST.dot -o $2
