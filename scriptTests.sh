#!/bin/bash
#
#  Compile the program with GCC.
#
echo "Generating test files"
procs=(1 2 4 8 16)
echo "Executing the main program"
for i in {1..5}
do
	echo ""
	echo "Execute the time $i"
	echo "procs 20 21 22 23 24" > times-$i.txt
	for j in ${procs[@]}
	do
		echo "With $j process"
		echo -n "$j " >> times-$i.txt
			echo -n "	$k elements: "
			tempo=`mpiexec -n $j Ep3 < ./inputs/inp18.txt`
			echo "$tempo"
			echo -n "$tempo " >> times-$i.txt
		echo "" >> times-$i.txt
	done
done

