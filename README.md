# Nanoscale-Compute
Academic coursework for Aristotle University of Thessaloniki 

Simulation Exercises access point for result extraction. This set of exercises, presented below is part of the curriculum in
Models and Theories of Molecular and Atomic Processes in the undergoing MSc study in Nanosciences & Nanotechnologies.

1
Create a program which calculates the average of N random numbers taken from a uniform random number distribution. The program 
must run for Ν = 10, 100, 1000, 10000, 100000, 1000000 random numbers. Plot the mean value as a function of N (axis of N should 
be logarithmic). Describe your conclusions. As initial seed use your record number (as in all the following exercises).

2
Create a program which performs a random walk for N = 1000 steps. You will do that for two cases: (a) a one dimensional system, 
(b) a two dimensional system. The program should calculate the square displacement R2. Run the program for 10000 runs and find 
the mean square displacement, namely <R2>

3
Use the program in the previous exercise to find the same thing, i.e. <R2> but now every 100 steps, from 0 to 1000. You will 
perform 10000 runs and find 10 points (one every 100 steps), of which every point will be the average of 10000 runs. Plot your 
results, namely <R2> vs. time. Use the least squares method as a fitting method to find the best straight line and the slope. 
Describe your conclusions.

4
Create a program which performs a random walk for N = 1000 steps in one dimension. Calculate the displacement R for these N steps 
and perform 100.000 runs. Find the mean displacement <R>. Find the distribution of R. Do the same for N = 500 steps and find the 
distribution as well. Plot the distributions for both N values in the same graph. What are you conclusions from the two curves? 
  
5
In the file stud_grades.dat  are the grades of 10000 students who took an exam in a class. The grade range is from 0 to 20.  
a. Create a histogram where x-axis represents the grades in integer values and y-axis represents the frequency for each grade. 
b. Create a second histogram where x-axis represents the grades in decimal values of 1 digit precision and y-axis represent the 
frequency for each grade. (If a grade belongs in the interval [17.95, 18.04] then it is stored as 18.0, if it belongs in the 
interval [18.05, 18.14] it is stored as 18.1 etc)  c. Calculate the mean value of the distribution  d. Calculate the standard 
deviation of the distribution

6
Create a program which generates a 2 dimensional lattice of size 1000 x 1000. In this lattice place at random positions a 
number of trap molecules with concentration c. Place one particle at a random position on the lattice and let it perform a 
random walk as in the previous exercises. In this walk you will not place a time restriction, i.e. you will not declare a 
specific number of steps. The walk will stop when the particle falls on a trap. The time required for this is the trapping 
time. Perform 100000 runs, save the trapping times and make the distribution of these times. Beware of boundary conditions. 
When the particle reaches the borders of the lattice it shouldn’t be allowed to fall outside but to remain in the lattice, 
either by returning on its former position or by being placed in the opposite site of the lattice. Run this program for 
c = 10^-2 and 10^-3. Put both distributions on the same graph. Describe your conclusions. 
