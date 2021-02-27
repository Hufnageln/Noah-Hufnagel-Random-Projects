/*Prototype 3
 *Tests least
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
double length(void *data){
	char* s = data;
	return (double)strlen(s);
}
void printString (void *data){
	printf("%s\n",data);
}

/*tests least*/
int m1(){
	
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
	printf("%lf\n", least(head, length));
	return (1);
}
/*tests least*/
int main(){
	void* head=NULL;
	printf("%lf\n", least(head, length));
	return (1);
}
