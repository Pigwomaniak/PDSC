#!/bin/bash
echo expected results: -4033.150691 108682304.087947 -164176072.564128 -263485118576781164544 -314940223216530432
for i in mat3.txt mat4.txt mat5.txt mat6.txt mat7.txt; do
  echo Processing file $i 
  ./det $i
done
