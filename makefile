.PHONY: Ep3 BKP

all: Ep3

BKP:
	g++ -ansi -Wall Ep3bkp.cpp -o BKP

Ep3:
	mpic++ -ansi -Wall Ep3.cpp -o Ep3

Clean:
	rm -f Ep3
	rm -f BKP
