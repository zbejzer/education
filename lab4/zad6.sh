#!/bin/bash

let pos=${#1}

while [[ pos > 1 ]]
do
  let
  echo ${!argn}
  let argn=$((argn-1))
done

exit 0
