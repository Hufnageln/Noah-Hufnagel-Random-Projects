#BY SUBMITTING THIS FILE AS PART OF MY LAB ASSIGNMENT, I CERTIFY THAT
#ALL OF THE CODE FOUND WITHIN THIS FILE WAS CREATED BY ME WITH NO
#ASSISTANCE FROM ANY PERSON OTHER THAN THE INSTRUCTOR OF THIS COURSE
#OR ONE OF OUR UNDERGRADUATE GRADERS. I WROTE THIS CODE BY HAND,
#IT IS NOT MACHINE GENERATED OR TAKEN FROM MACHINE GENERATED CODE

#Name: Noah Hufnagel
.file "evaluate.s"

.section	.rodata
	firstPrint: .string "evaluate: using range %d to evaluate \"%s\".\n"
	secondPrint: .string "evaluate: found %d words in \"%s\" using range %d.\n"

.data
.globl evaluate
	.type evaluate, @function
 
.align 8

.text
evaluate:				#param 1= char pointer (string input), param 2= range number (long)
	pushq %rbp			#save old base pointer
	movq %rsp, %rbp			#set new base pointer

	pushq %r12			#set up a place to hold the string
	pushq %r13			#set up a place to hold the range number
	pushq %r14			#set up a place to save the count

	movq %rdi, %r12			#store the input string
	movq %rsi, %r13			#store the range number
	xorq %r14, %r14			#zero count
	
	movq $firstPrint, %rdi		#load the first print statement into the first parmeter
	movq %r13, %rsi			#the second parameter should already be the range number, but we'll set it to be safe
	movq %r12, %rdx			#set the character string to the third parameter

	xorq %rax, %rax			#zero output for print
	call print			#do the first print print(firstPrint, range, str)

	movq %r12, %rdi			#set up the string for count. first parameter is string
	movq %r13, %rsi			#set up the range for count. 2nd parameter is range

	call count			#count the words using the leaf level function we wrote count(str, range)
	movq %rax, %r14			#save the count for later use	

	movq $secondPrint, %rdi		#load the second print statement into the first parmeter
	movq %r13, %rcx			#set the fourth parameter to the range number
	movq %r12, %rdx			#set the character string to the third parameter
	movq %r14, %rsi			#set the word count to the second parameter
	

	xorq %rax, %rax			#zero output for print
	call print			#do the second print print(secondPrint, count, str, range)

	movq %r14, %rax			#set the return value to the word count

tear_down: 	
	popq %r14			#tear down count register. restore old value
	popq %r13			#tear down range register. restore old value
	popq %r12			#tear down string register. restore old value

	leave				#tear down stack frame
	ret				#return to call

	.size evaluate, .-evaluate	#reqired directive
