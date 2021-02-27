#include <stdio.h>
#include "lab6.h"

char *strings[] = {
"FIRST STRING IN THE LIST.",
	"That's all folks!", "Let's be careful out there." , 
"395 Dreese Labs, 2015 Neil Avenue, COlumbus, OH, 43210",
"Well, to tell you the truth, in all this excitement I kind of lost track myself.",
"And gentlemen in England now a-bed shall think themselves accursed that they were not here!",
"Use The Force, Luke!", "C is call by value.", "O-H!", "I-O!", "Go Bucks!",
"",
"I don't know about you but I just found /* inside a comment.", 
"3 to beam up.",
"We few, we hapy few, we band of programmers;",
"8 6 7 5 3 0 9 (Sorry if that got stuck in your head)",
"4 I In thIs strIng.",
"THAT FOUGHT WITH US UPON SAINT CRISPIN'S DAY!",
"https://en.wikipedia.org/wiki/St_Crispin%27s_Day_Speech",
"https://www.youtube.com/watch?v=bvFHRNGYfuo",
"last string in the list.",
NULL

};


int main()
{
	char *ptr;
	long range;
	int size = sizeof(strings) / sizeof(strings[0]) -1;

printf("The last string is %s\n", strings[size-1]);

	for(range=0; range <3; range++)
	{
	    ptr = search(strings,size, range);
printf("Lab6: '%s' has the most words using range %ld'\n\n", ptr, range);
	}


	return 0;

}

