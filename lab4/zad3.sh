#!/bin/bash

if [[ -e $1  ]]
then
  find $1 -maxdepth 1 -printf '%p %y %M\n'
fi


exit 0
