.PHONY: Ep3 BKP

all: Ep3 BKP

BKP:
	mpic++ -ansi -Wall Ep3_.cpp -o Ep3_

Ep3:
	mpic++ -ansi -Wall Ep3.cpp -o Ep3

Clean:
	rm -f Ep3
	rm -f BKP
