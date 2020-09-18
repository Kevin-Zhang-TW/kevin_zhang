#!/bin/bash
source ~/.config/myconf/gen.conf
BOLD='\e[0;1m'
RED='\033[1;31m'
GREEN='\033[1;32m'
YEL='\033[1;33m'
BLUE='\033[1;34m'
DEF='\033[0m'
com () {
	file=$1
	tar=$2
	printf "\e[1;34m::  \e[0;1mWanna Recomlie $file? "
	read -p $'[Y/n] \e[0m' status
	if [ "${status^}" != "Y" ]; then
		return
	fi
	if [ "$file" == "generator" ]
	then
		cfile=$generator
	else
		cfile=$solver
	fi

	g++ -std=c++17 -fsanitize=undefined $cfile -o $tar
	while (( $? != 0)); do
		read -p " Recompile it ? [Enter] " 
		g++ -std=c++17 -fsanitize=undefined $cfile -o $tar
	done
	printf " $file Compile Succeeded\n"
}
show () {
	printf " Current test cases\n"
	for((i=1; ;++i))
	do
		if [ ! -d $des/$i ] 
		then
			break
		fi
		printf "  Subtask $i ==>  %3d data\n" $(($(ls -1q $des/$i | wc -l)/2)) 
	done
}
printf " Generator is set to : $generator\n"
printf " Solver    is set to : $solver\n"
printf " Target    is set to : $des\n"
echo
show
com generator GEN
com solver SOL
while read -p $'\e[1;32m==> Subtask id: (eg:\"1\", \"2\".., \"-1\" to Recomlie Files)\n==>\e[0m '  S
do
	if ((S == -1)); then
		com generator GEN
		com solver SOL
		continue
	fi
	read -p $'\e[1;32m==> Test data id: (eg:\"1 10\", "12"... start_id end_id)\n==>\e[0m ' L R && read -p " Generator Args : " A
	mkdir -p $des/$S
	R=${R:-$L}
	for ((i=$L;i<=$R;++i))
	do
		if ((A != "RE")); then
			./GEN $A > $des/$S/$i.in
		fi
		./SOL < $des/$S/$i.in > $des/$S/$i.out
		echo " Test Case $i Generated !"
	done
done

