# csc300_prog3

##Author
Kevin Hilt
 
##Date
April 9, 2014
 
##Professor 
 Corwin, Edward
 
##Course
 CSC300 - M001 -  MWTF 10:00AM
 
##Program Information 
 This program counts the number (n) of postivie, 32-bit integers 
 in a text file and then reads them into an dynamically allocated array of
 size n. Afterward, it dynamically allocates another array of n times the
 largest specified constant value and uses that table to hash the n values
 using the function number % table size. Each constant value (of which there
 are currently 5) is used first with linear probing, and then the used spots
 are reinitialized to 0 and the hashing is redone using quadratic probing.
 
 Since the insert function returns how many tries it took to insert the 
 current number, this is added to the sum held in an averages array. Once
 linear and quadratic probing for a given constant have been completed, the
 average tries for each are computed and stored back in the averages array
 and the table is reinitialized to 0s before proceeding to the next
 constant. When all constants have been hashed using both probing methods,
 a table comparing the averages to the theoretical 1 / (1 - alpha) is printed
 to the screen before the program exits.
 
 @section compile_section Compiling and Usage 
 
##Compiling Instructions: 
No special instructions for compiling. The program takes as a command line
 argument the file that will be used for input.
 
##Usage: 
   g++ prog3.C
   
