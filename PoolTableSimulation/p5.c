/*Prototype 5
 *Tests delete
 *Name: Noah Hufnagel
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
int fiveLetters( void *data){
	char* s= data;
	return ( strlen(s)==5);
}
double length(void *data){
	char* s = data;
	return (double)strlen(s);
}
void printString (void *data){
	printf("%s\n",data);
}

void fakeFree (void *data){
	printf("%s, removed\n",data);
}
/*tests insert*/
int main(){
	void* s1="test";	
	void* s2="word";
	void* uc="Uppercaseword";
	void* fivea= "Alpha";
	void* fiveb= "Zetas";
	void* fivec= "zoooo";
	void* head=NULL;
	insert(&head, s1, value,TEXT);
	insert(&head, s2, value, TEXT);
	insert(&head, uc, value, TEXT);
	insert(&head, fivea, value, TEXT);
	insert(&head, fiveb, value, TEXT);
	insert(&head, fivec, value, TEXT);
	printf("insert done\n");
	/*test*/
	iterate(head, printString);
	deleteSome(&head, fiveLetters,fakeFree, TEXT);
	printf("delete done\n");
	iterate(head, printString);
	return (1);
}

