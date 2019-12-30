#!/bin/sh
working_dir=~/Downloads
path=$working_dir/test_data
read dir
if [ $dir != "test_data" ]
then
	rm $working_dir/test_data/*
	unzip $working_dir/${dir}.zip -d $working_dir/test_data
fi
for i in $path/I.*
do
 	mv $i ${path}/"${i##*.}".in
done
for i in $path/O.*
do
	mv $i ${path}/"${i##*.}".out
done
rm $working_dir/$dir.zip
echo transform complete ~ 
