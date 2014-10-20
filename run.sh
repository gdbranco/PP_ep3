#!/bin/bash
I=0
J=0
COUNTER=0
LIMIT=$1
NUMS_PROC=(1 2 4 8 16)
INPUTS=(18 19 20 21)
OUT_EXT=".csv"
IN_EXT=".txt"
IN_DIRECTORY="./inputs"
MPI="mpiexec -np "
HOST=" -host localhost "
SRC="./"
while [ $I -lt 5 ]; do
	while [ $J -lt 4 ]; do
		echo "starting num proc : ${NUMS_PROC[$I]} input: ${INPUTS[$J]}"
		OUT_DIRECTORY="./outputs/${NUMS_PROC[$I]}"
		if [ ! -d "$OUT_DIRECTORY" ]; then
			mkdir $OUT_DIRECTORY -p
		fi
		while [ $COUNTER -lt $LIMIT ]; do
			echo $(mpiexec -np ${NUMS_PROC[$I]} Ep3 < ./inputs/inp${INPUTS[$J]}.txt > $OUT_DIRECTORY/${INPUTS[$J]}.csv)
			#mpiexec -np ${NUMS_PROC[$I]} -host localhost ./$PROGRAM_NAME < $IN_DIRECTORY/inp${INPUTS[$J]}$IN_EXT >> $OUT_DIRECTORY/${INPUTS[$J]}$OUT_EXE
			echo "$COUNTER done"
			COUNTER=$[$COUNTER+1]
		done
		COUNTER=0
        echo "=AVERAGE(A1:A$LIMIT);=STDEV(A1:A$LIMIT);=(B$(($LIMIT+1))/A$(($LIMIT+1)))*100" >> $OUT_DIRECTORY/${INPUTS[$J]}$OUT_EXT
        echo "=AVERAGE(B1:B$LIMIT);=STDEV(B1:B$LIMIT);=(B$(($LIMIT+2))/A$(($LIMIT+2)))*100" >> $OUT_DIRECTORY/${INPUTS[$J]}$OUT_EXT
        echo "-------------------------------------------------------------------"
		J=$[$J+1]
	done
	J=0
	I=$[$I+1]
done
echo exiting
