#!/bin/bash

newDirname=$(date '+%Y-%m-%d')

mkdir -p $newDirname

for file in $(find ~/Systemy_Operacyjne -daystart -ctime -1 -type f)
do
  cp $file "$newDirname/"
done

exit 0
