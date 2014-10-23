.PHONY:

all: Ep3 BKP EP3_SERIAL

EP3_SERIAL: Ep3_serial.cpp
	g++ -ansi -Wall Ep3_serial.cpp -o Ep3_serial.out

BKP: Ep3_.cpp
	mpic++ -ansi -Wall Ep3_.cpp -o Ep3_.out

Ep3: Ep3.cpp
	mpic++ -ansi -Wall Ep3.cpp -o Ep3.out

clean:
	rm -f *.out
