#!/bin/bash

if [[ ${#1} -gt ${#2} ]]
then
  longest=$1
else
  longest=$2
fi

if [[ $1 < $2 ]]
then
  lexfirst=$1
else
  lexfirst=$2
fi

echo "Dluzszy: ${longest}"
echo "Wczesniej leksykograficznie: ${lexfirst}"

exit 0
