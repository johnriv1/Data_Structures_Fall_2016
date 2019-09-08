HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  < John Rivera >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Lecture Notes,  >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8 hours >



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)

n = number of different costumes in the shop
m = maximum copies of a given costume
c = number of people who visit the shop

q = This is a variable I made to represent the number of people who are renting a certain costume.
	I felt it deserved it's own variable that's not c because of the fact that 99% of the time and
	in most real life scenerios, the amount of people renting a specific costume (q) will be far less than
	the total amount of people who visited the shop (c). However, it isn't exactly log(n) and not exactly constant
	either.

a ->  adding: O(log(n)) due to costume_shop[costume_name] += num;
			 
			 => O(log(n))

r -> renting: O(log(n)) due to costume_shop.find()
              O(log(c)) due to people.find()
			  O(log(c)) due to people[curr_person] which is a search
			  O(1)      due to push back on lists
			  O(q)      due to list.remove
			  
			  => O(log(n) + log(c) + q)
			  
l -> look up: O(log(n)) due to costume_shop.find()
			  O(log(n)) due to costume_shop[costume_name]
			  O(q)      due to looping through list of people (to print) who are renting a costume
			  
			  => O(log(n) + q)
			 
p ->  prints: O(c)      due to looping through every person who ever attempted to rent from the shop and printing
			  
			  => O(c)


EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






