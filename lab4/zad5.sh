#!/bin/bash

let argn=$#

for arg in $*
do
  echo ${!argn}
  let argn=$((argn-1))
done

exit 0
