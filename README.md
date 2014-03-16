=============
 DESCRIPTION
=============

This code is the C++ implementation of affinity propagation, a clustering algorithm by passing messages between data points.

In this code, I cluster two-dimensional data points. 
 
The code is based on Brendan Frey's science paper "Clustering by Passing Messages between Data Points" published in 2007.

http://www.sciencemag.org/content/315/5814/972.short

=============
 Prepare
============= 

Prepare a file named "ToyProblemData.txt" which stores the two-dimensional data points and put this file in the same directory as the source code. 

In this file, there are two real numbers in each line, which is separated by a space. 

The first number is the x coordinate and the second number is the y coordinate.
 
=============
 Compile
=============

g++ affinity_propagation -o ap


=============
 Run
=============

ap


This implementation has passed the test cases provided by this url:

http://www.psi.toronto.edu/index.php?q=affinity%20propagation

 
Reference: Clustering by Passing Messages between Data Points