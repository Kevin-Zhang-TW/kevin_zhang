#!/bin/sh
path=~/Downloads/test_data/
for i in $path/I.*
do
 	mv $i ${path}"${i##*.}".in
done
for i in $path/O.*
do
	mv $i ${path}"${i##*.}".out
done
echo transform complete ~ 
