# Shortest-Path
Implements a weighted graph class with c++.


## Introduction 
In this lab, you are supposed to implement a graph class with weighted edges.

### Input file format
The file you are supposed to create the graph with will be formatted as below. 
The first line is an integer n that indicates the number of vertices. 
Each vertice owns an id from 0 to n-1. Each line below contains the information 
of an edge. For instance, the following line represents an edge from vertice 1 
to vertice 3 with a weight 2.
```
1 3 2
```

A sample input is given below.
```
5
0 2 1
0 1 2
0 3 3
2 3 1
1 4 5
2 4 3
3 4 1
```

Implement the findShortestPath function so that, given a beginning and an end, 
it returns the string of the shortest path between the two nodes. 

For the input above, if 0 is given as the start point and 4 is given as the 
destination, the string returned should be: 
```
0 2 3 4
``` 
If there exists no route from the start point to the destination or the input 
is not valid, e.g., the graph is empty, return the string 
```
The target and the source are not connected.
```
