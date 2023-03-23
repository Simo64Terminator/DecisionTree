# DecisionTree

//////////////////////////////////////////////////////////////////

Tomasella Simone - UNIGE Computer Science - Simple Decision Tree

Compile with "g++ -Wall -Wextra -Wpedantic *.cpp"

//////////////////////////////////////////////////////////////////

This program is the final assignment of UNIGE "Algorithms and Data Structures" course.
This decision tree is created using a generic tree represented with a node list and an edge list.

Both nodes and edges have informations on how to predict the result.

Maybe it's not the best implementation for a tree, but at the time I thought that was the best solution.

/////////////////////////////////////////////////////////////////

I use dynamic arrays for printing purposes, probably there is a better way to do the same thing.
(arrayListUtility.cpp, arrayListUtility.h)

/////////////////////////////////////////////////////////////////

Take demo.txt as a demonstration:

__Start of demo.txt__

travel_1

travel_1 office_1 =Yes office_2 =No

office_1 workload_1 =PE workload_2 =ME workload_3 =BA

office_2 workload_4 =PE workload_5 =ME workload_6 =BA

workload_1 diskSpace_1 =500 diskSpace_2 =1000

workload_2 diskSpace_3 =500 diskSpace_4 =1000

workload_3 diskSpace_5 =500 diskSpace_6 =1000

workload_4 diskSpace_7 =500 diskSpace_8 =1000

workload_5 diskSpace_9 =500 diskSpace_10 =1000

workload_6 diskSpace_11 =500 diskSpace_12 =1000

diskSpace_1 END_1 =Workstation_Laptop_500GB

diskSpace_2 END_2 =Workstation_Laptop_1000GB

diskSpace_3 END_3 =Gaming_Laptop_500GB

diskSpace_4 END_4 =Gaming_Laptop_1000GB

diskSpace_5 END_5 =Office_Laptop_500GB

diskSpace_6 END_6 =Office_Laptop_1000GB

diskSpace_7 END_7 =Workstation_Desktop_500GB

diskSpace_8 END_8 =Workstation_Desktop_1000GB

diskSpace_9 END_9 =Gaming_Desktop_500GB

diskSpace_10 END_10 =Gaming_Desktop_1000GB

diskSpace_11 END_11 =Office_Desktop_500GB

diskSpace_12 END_12 =Office_Desktop_1000GB

__End of demo.txt__

The first line (travel_1) is tree's root.

The second line represents the father (travel_1), two children (office_1, office_2) and how to reach a specific child by asking a value to the user (=Yes, =No, stored in edges). This is repeated on all lines

For example, the program starts from travel_1, and asks the user if the computer he needs is for basic or heavy workloads. If user choose Yes, the program goes to child "office_1", if not, the program goes to child "office_2".

The program continues to travel down the tree like I just said until it reaches a leaf: that means we predicted something (if the tree was created correctly by the user).
