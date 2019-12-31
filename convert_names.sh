#!/bin/sh
working_dir=~/Downloads
target=~/test_data
test_zip=${1:-""}
if [ $test_zip == "" ]
then
	read test_zip
fi

if [ $test_zip != "test_data" ]
then
	rm $working_dir/test_data/*
	unzip $working_dir/${test_zip}.zip -d $target
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
rm $working_dir/$test_zip.zip
echo transform complete ~ 
