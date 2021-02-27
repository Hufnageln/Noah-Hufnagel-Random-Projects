# AU20 Lab 6 makefile Copyright 2020 Neil Kirby Do not remove this comment
# Your name goes here.
#Name: Noah Hufnagel



# makes the lab6 main file to test search and all the code as a whole
# uses provided main
lab6: lab6main.o search.s evaluate.s count.s 
	gcc -g -m64 -o lab6 lab6main.o print.o count.s evaluate.s search.s

# makes the lab6 main file to test search and all the code as a whole. 
# using bonus A. This file still compiles to an executable named "lab6"
# just like the prior make command. but this uses my main instead of
# the provided one
lab6bonus: lab6bonus.s search.s evaluate.s count.s 
	gcc -g -m64 -o lab6bonus lab6bonus.s print.o count.s evaluate.s search.s
	
# makes the evaluate main file to test evaluate
evaluate: evalmain.o count.s evaluate.s
	gcc -g -m64 -o evaluate evalmain.o print.o count.s evaluate.s

# makes the count main file to test count
count: countmain.o count.s
	gcc -g -m64 -o count countmain.o print.o count.s


# you need to add an entry to build your zipfile
# you should be experts at this by now.
#this is where you create an entry to build yuour zip file
#it will also update with new labs
lab6.zip:	README_LAB6 makefile *.s *.o *.c
	zip $@ $^
	# remove old install folder
	rm -rf install
	#create the install folder
	mkdir install
	#unzip to the install folder
	unzip lab6.zip -d install
	#make ONLY the lab6 target, not lab6.zip
	make -C install lab6 





#students ignore this entry, it's how I built the zip file of goodies 
l6_stuff.zip : makefile *.txt lab6main.c evalmain.c countmain.c lab6.h print.o
	zip $@ $^




# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


