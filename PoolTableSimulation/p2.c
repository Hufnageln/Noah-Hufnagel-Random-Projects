/*Prototype 2
 *Tests some
 *Name: Noah Hufnagel
 */
#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

#define TEXT 1
#define DEBUG 1
/*returns comparison value after comparing first letter
 *capitals come before lowercase. alphabetical
 */
int value( void *lower , void *higher){
	char *l =lower;
	char *h= higher;
	int res=1;
	if(DEBUG) printf("comparison began\n");
	if(*l>*h) res=0;
	return res;
}
int uCase( void *data){
	char* s= data;
	return ( *s <'a');
}

void printString (void *data){
	printf("%s\n",data);
}

/*tests some*/
int main(){
	void* s1="test";	
	void* s2="word";
	void* uc="notanuppercaseword";
	void* head=NULL;
	insert(&head, s1, value,TEXT);
	insert(&head, s2, value, TEXT);
	insert(&head, uc, value, TEXT);
	printf("insert done\n");
	/*test*/
	iterate(head, printString);
	printf("%d\n",some(head, uCase ));
	return (1);
}
