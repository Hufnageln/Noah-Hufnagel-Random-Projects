/*Linked List code.
 *Name: Noah Hufnagel
 */
#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "altmem.h"
#include "debug.h"
#include "linkedlist.h"
/*HELPER FUNCTIONS*/
/*
 *Creates a node and fills data. keeps count of how many nodes have been allocated 
 */
static Node *createNode(void *data){
	static int nodeAlloc=0;
	Node* n;
	if(n =  alternative_malloc(sizeof(Node))){
	    nodeAlloc++;
	    n->data= data;
	    n->next=NULL; 
	    if(TEXT) printf("DIAGNOSTIC: %d nodes allocated\n", nodeAlloc);
	}
	else {
	    if(TEXT) printf("ERROR: unable to allocate a node\n");
	}
	return n;
}
/*
 *Recycles(frees) a node and keeps track of how many have been freed 
 */
static void recycleNode(Node *n){
	static int freedNodes=0;
	if( n== NULL){
	    if(TEXT) printf("ERROR: recycleNode: NULL passed in.\n");
	}
	else{
	    freedNodes++;
	    alternative_free(n);
	    n=NULL;
	    if(TEXT) printf("DIAGNOSTIC: %d nodes freed\n", freedNodes);
	}
}

/*END HELPER FUNCTIONS*/

/*
 * inserts an element into the linked list
 * passes work off to createNode
 */
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int verbose){
	/*initialize result to false (0)*/
	int res=0;
	Node* newNode;
	Node** p2p2current=p2head;
	/*check if allocation worked*/
	if( (newNode = createNode( data ))!= NULL){
	   /*skip nodes with bigger data than the new data*/
	   while(*p2p2current!= NULL && goesInFrontOf((**p2p2current).data,newNode->data )){
		p2p2current= &((**p2p2current).next);
	    } 
	    /*do the insert*/
	    /*make the new node next point to what the current changing pointer points to*/
	    newNode->next=*p2p2current;
	    /*make the pointer to current point to the new node*/
	    *p2p2current= newNode;
	    /*set result to 1 since insert worked*/
	    res=1;
	}
	return res;
}
/*
 * delets an element from the linked list
 * passes work off to recycleNode
 */
void deleteSome(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int verbose){
	int res=0;
	Node* deleteNode;
	Node** p2p2current=p2head;
	/*test every node*/
	while(*p2p2current!= NULL){
	    if(mustGo((**p2p2current).data)){
		/*do the delete*/
		/*save the node to delete so we can free it*/
		deleteNode=*p2p2current;
		/*set the current pointer to the next one this updates p2p2current too*/
		*p2p2current= ((**p2p2current).next);
		/*dispose node*/
		disposal(deleteNode->data);
		/*recycle Node*/
		recycleNode(deleteNode);
	    }
	    else {
		/*change p2p2current the same way as insert if we dont remove an element*/
	        p2p2current= &((**p2p2current).next);
	    }
	} 
}

/*
 * Iterates through the linked list performing action doThis on all
 */
void iterate(void *head, ActionFunction doThis){
	Node* current= head;
	/*loop through every node doing do this*/
	while(current != NULL){
	    doThis(current->data);
	    /*next node*/
	    current= current->next;
	}
}
/*
 * finds if any item matches someTest
 */
int some(void *head, CriteriaFunction someTest){
	Node* current= head;
	/*initialize result to 0 (false)*/
	int res=0;
	/*loop through every node testing*/
	while(res !=1 && current != NULL){
	    /*if test is true then result =1*/
	    if(someTest(current->data)) res=1 ;
	    /*next node*/
	    current= current->next;
	}
	return res;
}
/*
 * finds the lowest value returned by the list given comparison Function
 */
double least(void *head, NumericFunction compute_this){
	Node* current= head;
	/*initialize least to NaN*/
	double leastVal=0.0/0.0;
	/*only start this is the list is not empty*/
	if(current!= NULL){
	    /*if list not empty set least to first value computed and move to next node*/
	    leastVal= compute_this(current->data);
	    current=current->next;
	    /*calculate for every node*/
	    while(current != NULL){
		/*if a value computed is less than least then change least to the new value*/
	        if(compute_this(current->data) < leastVal) leastVal=compute_this(current->data) ;
	        /*next node*/
		current= current->next;
	    }
	}
	return leastVal;
}
