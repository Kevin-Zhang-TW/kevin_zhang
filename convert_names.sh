#!/bin/sh
working_dir=~/Downloads
target=~/test_data
test_zip=${1:-""}
back_up_dir=~/old_test_data
if [[ $test_zip == "" ]]
then
	read test_zip
fi
if [ ! -e $back_up_dir/$test_zip ]
then
	rm $working_dir/test_data/*
	unzip $working_dir/${test_zip}.zip -d $target
	unzip $working_dir/${test_zip}.zip -d $back_up_dir/$test_zip
else 
	cp $back_up_dir/${test_zip}/* $target/
fi
## transform formats
for i in $target/I.*
do
 	mv $i ${target}/"${i##*.}".in
done
for i in $target/O.* 
do
	mv $i ${target}/"${i##*.}".out
done
## delete zip file
if [ -e $working_dir/$test_zip ]
then
	rm $working_dir/$test_zip.zip
fi
echo transform complete ~ 
