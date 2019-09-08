HOMEWORK 3: UNDO ARRAY


NAME:  < John Rivera >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Lecture 8 notes, Male TA/Mentor form 4-8pm office hours >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 hours >


ORDER NOTATION:
For each function, using the variables:
  n = size of the array
  h = the length of the longest history for one slot of the array
Include a short description of your order notation analysis 
for the non-trivial functions.

size: O(1)

set: O(h)
		Loops through history array

initialized: O(1)

get: O(1)

undo: O(h)
		Loops through history

print: O(n*h)
		Loop inside a loop. First loop goes through size and second loop goes through history

basic constructor: O(n)
		Loop through size of array and make pointer point to NULL

copy constructor: O(n*h)
		Loops through size and inside that loop, loops through history to copy values

destructor: O(n)
		Loops through size to delete what pointers point to

EXTRA CREDIT:
Discuss your implementation & order notation of push_back and pop_back.

push_back:

pop_back:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

