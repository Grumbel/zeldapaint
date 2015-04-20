
zeldapnt.exe : zeldapnt.o zelda.o
	gcc zeldapnt.o zelda.o -o zeldapnt.exe -lallegr -Wall
zeldapnt.o : zeldapnt.c zeldapnt.h
	gcc zeldapnt.c -Wall -c
zelda.o : zelda.c zeldapnt.h
	gcc zelda.c -c  -Wall
