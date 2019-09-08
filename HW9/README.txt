HOMEWORK 9: IMAGE COMPARISON HASHING


NAME:  < John Rivera >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Yuri, Andrew, Lecture Notes >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 17 >




i = # of images
w = width x h = height (average size image)
s x s = seed size
r x r = typical subregion match. 
t = hash table size 
c = fraction of hash table to compare


ANALYSIS OF SIMPLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

running time -> O(i*w*h*w*h*s*s)

Simple uses less memory but with more running time

ANALYSIS OF HASH TABLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

memory usage -> O(t)

Hash uses more memory (uses very large array) but with less running time

SUMMARY OF RESULTS: 
Test your implementation on a variety of images and command line
arguments and summarize and discuss the results (both running time and
quality of results).

I wasn't able to finish but my guess would be that the bigger the image and the more the images, 
the better the hashtable is. This is because of the constant time access unlike the simple implementation.
Hash function may also be a bit less accurate due to the fact that the hash function isn't guaranteed to 
perfectly distribute data.

EXTRA CREDIT -- MULTIPLE ROTATION AND/OR 90/180/270 ROTATION AND
HORIZONTAL/VERTICAL FLIP:
Discuss your implementation and results of testing.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!

This homework was extremely confusing due to the fact that I had no experience using hash tables
and little experience with images, so it took a while to even understand how we could have used them 
to store and compare images. With all the confusion, I had very little time to actually write code once
I was able to find a way to start it.




