HOMEWORK 6: PAINT BY PAIRS RECURSION


NAME:  < John Rivera >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Previous recursion labs and previous lab holding the Point2D object, mentor Andrea, mentor John >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 16 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of strokes (s)? 
The total number of painted cells(p) or unpainted cells (u)?
The average length of each stroke (l)?
Etc.

n -> amount of pairs

O(n*log(s*l)) -> collecting possible strokes for every number
O(n*log(s*l)) -> following possible strokes and painting until board(s) is solved

= 0(2*n*log(s*l))

The algorithm first collects the possible paths for each coordinate and collects them into vector.
The algorithm then recursively loops through the possible paths until it reaches a solved board, in which case it will push the board back and then continue.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.  Also, describe the
image in words.

puzzle1, all solutions - > 0 ms; (3 solutions)
puzzle1 - > 0 ms;  (1 solutions)
puzzle2 - > 0 ms;  (1 solution)
puzzle3 -> 15 ms;  (1 solution)
puzzle4 -> 125 ms; (0 solutions)
puzzle5 -> 265 ms; (0 solutions)
puzzle6 -> 656 ms; (0 solutions)



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Recursion was pretty difficult to think about which made it hard to get started.
My code wasn't able to solve puzzles 4 and up but I wasn't able to find the solution to this bug in time.
