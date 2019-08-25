# Who:  Randy Salazar
# What: project_3.asm
# Why:  Program sorts user input in ascending order in a array. Then allow the user 
#       to seach the array for entered values
# When: 3/30/2019, Due 4/2/2019
# How:  $a0	used to pass userinput to sort and binary search subroutine  
#       $a1	used to pass $s2 to sort and binary search subroutine 
#       $a2	used to hold array address  and 
#       $a3	used to hold beginning value of array passed to binary search 
#       $s1	holds user input of array size 
#       $s2	counter used in input loop
#       $t0	Used in calculations of mid value in binary search
#       $t1	Used in calculations of mid value in binary search

.data

prompt:  .asciiz "How many numbers would you like to enter: " 
prompt1: .asciiz "Enter a number: "
prompt2: .asciiz "Here is your array in increasing order: " 
prompt4: .asciiz "What value would you like to search the array for:  "
print_found: .asciiz "Value is in the array" 
print_not_found: .asciiz "Value is not in the array" 
.align 2

input_array: .space  200

.text
.globl main

main:	# program entry

    la $a0, prompt                  # send out prompt
    li $v0, 4
    syscall

    li $v0, 5
    syscall

    move $s1, $v0                   # user input 
    li $s2, 0                       # counter to be used for loop
    
    # Loops gather user input and sends user input to sort
    input_loop:
        beq $s2, $s1, exit_loop             # if counter = array size exit loop

            la $a0, prompt1                 # send out prompt 
            li $v0, 4
            syscall

            li $v0, 5                       # get user input 
            syscall
            move $a0, $v0                   # move user input for passing to subroutine

            move $a1, $s2                   # move counter for passing to subroutine
            la $a2, input_array             # pass array by reference to subroutine

            jal sort                        # send $a0, $a1, $a2 to sort 

            addu $s2, $s2, 1                # increase counter 
            j input_loop

    exit_loop:

    la $a2 input_array                      # load sorted array 
    li $t1, 0                               # set counter 
    
    la $a0, prompt2                         # send out prompt 
    li $v0, 4 
    syscall
    
    # Loop prints out the content of input_array
    print_loop:

        beq $t1, $s1, exit_print_loop       # if counter = (size of the array + 1) exit loop 

        lw $a0, 0($a2)                      # Load value from array and print 
        li $v0, 1
        syscall

        li $a0, ' '                         # print space 
    	li $v0, 11 
    	syscall

        addu $a2, $a2, 4                    # increase local counter 
        addu $t1, $t1, 1                    # increase array position 
        
        j print_loop

    exit_print_loop:
    
    li $a0, '\n'	               	    # write new line
    li $v0, 11	
    syscall  

    # loop is infinte as required by project3 handout 
    search_loop:
        beq $s1,$0, exit                    # infinite loop 

            la $a0, prompt4                 # ask for input 
            li $v0, 4 
            syscall

            li $v0, 5                       # move input to $a0 
            syscall 
  
            move $a0, $v0                   # move user input for passing to subroutine
            move $a1, $s1                   # pass array size to subroutine
            li $a3, 0                       

            jal binary_search               # pass $a0, $a1, $a3 to binary search = binarySearch(&array, start, end, searchVal)

            move $t0, $v0                   # $v0 was returned from subroutine
        
            beq $t0, $0, print_notfound    # if $v0 = 0 print not found
            
            	la $a0, print_found 	    # if $v0 = 1 print found 
            	li $v0, 4 
            	syscall 
            	
            	j jump_over
            
            print_notfound: 
           
            la $a0, print_not_found 	    # print output 
            li $v0, 4 
            syscall 
           
            jump_over: 
            
            li $a0, '\n'	            # write new line
    	    li $v0, 11	
            syscall
            
            
            j search_loop
    exit: 

.text
# Takes user input and stores it into an array in increasing order 

#args
    # a0 is holds user input to be inserted 
    # a1 holds counter to be used for insertion 
    # a2 hold array address
#return
    # nothing is returned, array becomes sorted 

sort:

    li $t0, 0                                   # local counter
    check_input: 
        beq $t0, $a1, array_input           	# if local counter = counter from main then jump 

            lw $t1, 0($a2)                      # grabs value from array for comparison 
            blt $a0, $t1, sort_input            # if user input < current value  then sort 

            addu $t0, $t0, 1                    # increase local counter 
            addu $a2, $a2, 4                    # increase array position 

            j check_input

    sort_input:
        sw $a0, 0($a2)                          # stores the smaller value into higher values address 
        move $a0, $t1                           # store the higher value into $t1 for further comparison in the array 

        addu $t0, $t0, 1                        # increase local counter 
        addu $a2, $a2, 4                        # increase array position 

        j check_input

    array_input:
        sw $a0, 0($a2)                          # stores the highest value into the last index of the array 
        jr $ra



.text 
# Takes user input and searches the array for that input by using binary search
#args
    # a0 holds usr input searched for in the array 
    # a1 holds the array size
    # a2 holds array address 
    # a3 holds the array staring point 
#return
    # v0 hold the value 1 or 0 (1 for true and 0 for false), depending if the value was found 
binary_search:         
    add $sp, $sp, -4                	# create room on the stack 
    sw $ra, 0($sp)                  	# store curret return address onto the stack

    li $t0, 0                       	# will hold offset to get value from array

    blt $a1, $a3, not_found    	   	# start > end     
        sub $t1, $a1, $a3           	# $t1 = (end-start)
        srl $t1, $t1, 1             	# $t1 = (end-start)/2
        add $t1, $a3, $t1           	# mid = start + $t1

        sll $t0, $t1,   2           	# create off set for mid value 
        la $a2, input_array($t0)    	# load address of mid value 
        lw $t0, 0($a2)              	# load value from array

        beq $t0, $a0, found         	# if mid = userinput  
        bgt $t0, $a0, left_side     	# mid > desired value 

        right_side:                 	# mid < desired value 
            add $t1, $t1, 1         	# start = mid + 1 
            move $a3, $t1 

            jal binary_search       	# return binarySearch(array, mid+1, end, searchVal);
            j free_space

        left_side:
            add $t1, $t1, -1     	# end = mid - 1 
            move $a1, $t1       
            
            jal binary_search		# return binarySearch(array, start, mid-1, searchVal);
            j free_space

        free_space:
            lw $ra, 0($sp)      	# grab previous return address from stack 
            add $sp, $sp, 4      	# give memory back to the stack        
            jr $ra               	# go back to previous recursion call 

        found:
            li $v0, 1            	# value was found 
            j free_space

        not_found: 
            li $v0, 0            	# value was not found 
            j free_space
