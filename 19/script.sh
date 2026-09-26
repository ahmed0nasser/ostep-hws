#!/usr/bin/env bash

trials=3000000
printf "Pages# \t Avg.AcessTime\n"
for i in {0..12}; do
  pages=$((1 << $i))
  printf "$pages \t $(./tlb $pages $trials)\n"
done
