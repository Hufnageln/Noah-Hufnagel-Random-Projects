#BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
#ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
#ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
#OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
#IT IS NOT MACHINE GENERATED OR TAKEN FROM MACHINE GENERATED CODE

#Name: Noah Hufnagel
.file "main.s"
.section	.rodata	
	#our print strings
	lastString: .string "The last string is %s\n"
	l6Print: .string "Lab6: '%s' has the most words using range %d'\n\n"

#the strings we will store in our array of pointers
strings1:
.string "FIRST STRING IN THE LIST."
strings2:
.string "That's all folks!"
strings3:
.string "Let's be careful out there."
strings4:
.string "395 Dreese Labs, 2015 Neil Avenue, COlumbus, OH, 43210"
strings5:
.string "Well, to tell you the truth, in all this excitement I kind of lost track myself."
strings6:
.string "And gentlemen in England now a-bed shall think themselves accursed that they were not here!"
strings7:
.string "Use The Force, Luke!"
strings8:
.string "C is call by value."
strings9:
.string "O-H!"
strings10:
.string "I-O!"
strings11:
.string "Go Bucks!"
strings12:
.string ""
strings13:
.string "I don't know about you but I just found \/\* inside a comment."
strings14:
.string "3 to beam up."
strings15:
.string "We few, we hapy few, we band of programmers;"
strings16:
.string "8 6 7 5 3 0 9 (Sorry if that got stuck in your head)"
strings17:
.string "4 I In thIs strIng."
strings18:
.string "THAT FOUGHT WITH US UPON SAINT CRISPIN'S DAY!"
strings19:
.string "https://en.wikipedia.org/wiki/St_Crispin%27s_Day_Speech"
strings20:
.string "https://www.youtube.com/watch?v=bvFHRNGYfuo"
strings21:
.string "last string in the list."

.globl main
	.type main, @function

.data

.align 8
#the array of pointers
strings:
.quad strings1
.quad strings2
.quad strings3
.quad strings4
.quad strings5
.quad strings6
.quad strings7
.quad strings8
.quad strings9
.quad strings10
.quad strings11
.quad strings12
.quad strings13
.quad strings14
.quad strings15
.quad strings16
.quad strings17
.quad strings18
.quad strings19
.quad strings20
.quad strings21
.quad 0x00		#a NULL quad

.text
main:
	pushq %rbp				#save old base pointer
	movq %rsp, %rbp				#set new base pointer

	pushq %r12				#char *strings. create place to save strings
	pushq %r13				#char *ptr. create place to save ptr
	pushq %r14				#long range; create place to save range
	pushq %r15				#size. create place to save size
	

	movq $strings, %r12			#set up strings array
	movq $-1, %r15				#initialize size to -1. this starts index at 0 once we get to the loop
	movq $0 , %rdi				#hold a null pointer for comparison 
						#it is fine to use a caller saved register
						#here since we only need the null for sizeof
						#and that loop doesn't call anything
size_of_start:
	incq %r15				#increment size
	cmpq (%r12, %r15, 8), %rdi		# compare current element to null
	jnz size_of_start			#jump bck to size of loop if we havent hit null
						#if we fall through then we have hit NULL 
						# this means size=index of NULL

						#first print
	movq $lastString, %rdi			#set strig as first parameter for print
	decq %r15				#size-1 to get last index
	movq (%r12, %r15, 8), %rsi		#last string is second parameter for print
	xorq %rax, %rax				#zero output for print
	call print				#print(..., size-1)
	incq %r15				#undo prior size decrement, doesn't really matter since we don't actually 
						#use size in search. but it is a parameter
						# and it would if we did use that parameter

	xorq %r14, %r14				#zero range
loop_start:					#for loop

	movq %r12, %rdi				#string is the first parameter for search
	movq %r15, %rsi				#size is 2nd parameter
	movq %r14, %rdx				#range is 3rd parameter
	call search				#call search
	movq %rax, %r13				#ptr=search(..)

	movq $l6Print, %rdi			#set lab6:.... string as first parameter for print
	movq %r13, %rsi				#pointer is second parameter for print
	movq %r14, %rdx				#range is third parameter for print
	xorq %rax, %rax				#zero output for print
	call print				#print("lab6:...", ptr, range)

	incq %r14				#increment range
	movq $3, %rdi				#store 3, for loop comparison
	cmpq %rdi, %r14				#compare range to 3
	jl loop_start				#loop if range<3	

						#if we are here then we are done with our loop
						#ie. range>=3

done:
						#pop in reverse order
	popq %r15				#pop size
	popq %r14				#pop range
	popq %r13				#pop ptr
	popq %r12				#pop strings

	xorq %rax, %rax				#zero output for return 0

	leave					#tear down stack frame
	ret					#return 0

	.size main, .-main			#reqired directive
