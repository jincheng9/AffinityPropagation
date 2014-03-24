=============
 DESCRIPTION
=============

This code is the C++ implementation of affinity propagation, a clustering algorithm by passing messages between data points.

In this code, I cluster two-dimensional data points. The similarity between data points is the Eculidean distance. 
The preference of each data point is set as the median of all non-diagnoal elements of the similarity matrix. 
 
The code is based on Michael Pfeiffer slides about affinity propagation. 

http://www.igi.tugraz.at/lehre/MLA/WS07/MLA_AffinityPropagation.pdf.


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



This implementation has passed the test cases provided by the author of affinity propagation:

http://www.psi.toronto.edu/index.php?q=affinity%20propagation

 
Reference: "Clustering by Passing Messages between Data Points", Brendan J. Frey, Delbert Dueck, Science 2007. 