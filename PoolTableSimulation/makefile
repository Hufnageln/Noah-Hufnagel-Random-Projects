
# AU20 Lab 3 makefile Copyright 2020 Neil Kirby Do not remove this comment
# IF you modify this file, comment any place you do so.
#

all:  tags headers lab3 lib8ball.a

# make headers to refresh the .vs files *after* you save/write all .c
# files.  This makes it very easy to update your own .h files

headers: *.c tags
	headers.sh

# THis is the line that links everything together (only .o and .a files)
# It doesn't need the 4 warnings since compilation is already done by the
# time we link.
#CHANGE: LAB3 CHANGED TO LAB4 ADDED linkedlist.o as dependency. reliable.o and unreliable.o added,
# REMOVED  linkedlist library
lab4: lab4.o table.o dt.o functions.o io.o mem.o reliable.o linkedlist.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -lncurses -lm
lab4u: lab4.o table.o dt.o functions.o io.o mem.o unreliable.o linkedlist.o 
	gcc -g -o $@ $^ -lncurses -L. -l8ball  -lncurses -lm
#PROTOTYPES ALL ADDED BY NOAH HUFNAGEL
#GRADE THIS: Prototype 1, iterate
p1: p1.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lncurses -lm
#GRADE THIS: Prototype 2, some
p2: p2.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lncurses -lm
#GRADE THIS: Prototype 3, least
p3: p3.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lncurses -lm
#GRADE THIS: Prototype 4, insert
p4: p4.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball -llinkedlist -lncurses -lm
p5: p5.o linkedlist.o reliable.o
	gcc -g -o $@ $^ -lncurses -L. -l8ball  -lncurses -lm
p6: p6.o 
	gcc -g -o $@ $^ -lncurses -L. -l8ball  -lncurses -lm

#END PROTOTYPES

#CHANGE: MAKE ZIP ADDED
#this is where you create an entry to build yuour zip file
#it will also update with new labs
lab4.zip:	makefile *.c *.h *.a README_LAB4 reliable.o unreliable.o
	zip $@ $^
	# remove old install folder
	rm -rf install
	#create the install folder
	mkdir install
	#unzip to the install folder
	unzip lab4.zip -d install
	#make ONLY the lab4 target, not lab1.zip
	make -C install lab4 
# tags are what we use to generate visible symbol files (.vs)
# In vi, it enables control-] (control closing square bracket)
# which lets you jump to a symbol definition

tags: *.c
	ctags -R .

# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


