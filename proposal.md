Dataset:
University of Illinois “courses-dataset” (https://github.com/illinois/courses-dataset)
Leading Questions
What are the prerequisites required for a certain course?
What is the least expensive (lowest credit hours) prerequisite chain of courses?
How many paths can be taken to be able to take a certain course?
How important is a singular course (how many courses is it one of the prerequisites to?)
Data Acquisition and Processing
Data Format: 
Source of the dataset is from https://courses.illinois.edu/cisdocs/explorer. Data is divided into Course Catalog and Course Section.
Input format of dataset includes Course Catalog Data Format and Course Schedule Data Format. The Course Catalog Data lists each course and its attributes like Term offered, Subject, Course Number, Credit Hours, Section Info (Prerequisites, duplicate courses), Degree Attributes etc. The Course Schedule Data lists each section of a course and its attributes like CRN, Section number, Enrollment Type, Time, Building, Instructor etc. We mainly plan on using the prerequisites, Course Name information to store and traverse our data structure of classes. 
Data Correction:
We do not plan on using data for each individual section of each class. Instead, we will collapse all the sections into one. Data like time, section, CRN, and day of the week will not be necessary, so those must be ignored when we are formatting our data. We also only want each class to be collected once, so any duplicate listings of a class (ie. a different section) will be ignored. For an entry to be valid, it must contain the name, subject, number, and section info. Entries without this information will be ignored, as they cannot be used with our proposed graph structure. Furthermore, classes without any prerequisites or are not required as a prerequisite will not be included, as they also cannot be used with our proposed graph structure. Because our data is coming from a source that has already formatted much of it, our data correction is mostly ignoring entries that do not contain complete information or ignoring entries that we cannot use with our data structure. 
Data Storage: 
As a preprocessing step, the dataset table will be iterated over, and each hierarchy of classes will be stored as a separate graph, encoded as separate files in a folder on disk. Each file will be named after the topmost course in the graph for easy querying. When a given course is to be analyzed, its department code and class number will be entered by the user, and these will be used to locate and load the appropriate graph file from disk. For the graphs that we create, we think that each graph will be of size O(n), as each graph gets bigger linearly with each class added. However, our total storage will be of size O(n*log(n)), because some classes will be included in multiple graphs.
There are approximately 4,400 unique classes (not sections) in the dataset, spread across ~190 departments.

Figure 1: Simple example of a course dependency/prerequisite graph
Graph Algorithms
Traversal: Depth First Search
Purpose: Given a desired course and a second course, this algorithm will return whether the desired course depends (directly or indirectly) on the second course.
Function Inputs: the node corresponding to the course that the user would like to enroll in, and the node corresponding to the aforementioned second course.
Function Outputs: The distance between the nodes if there is a dependency relationship, or -1 if the desired course does not depend on the second course.
Function Efficiency: In the worst case, this function will take time O(n), where n is the number of classes in the graph.	
Algorithm # 1: Shortest Path (Dijkstra’s Algorithm)
Function Inputs: The node containing a course that you would like to see the least number of prerequisite credit hours for. This will allow the student to minimize their tuition costs. The credit hour values will be used for the edge weights for the shortest-path algorithm.
Function Outputs: The head of a linked list that has all the courses in the order you have to take them in. So the head would point to the first course in the chain and the final node would contain the input course.
Function Efficiency: The general time efficiency of this function should be O(Elog(V)) where E is the total number of course interconnections which create the edges of the graph and V is the number of courses which create each node. Two variables are required for this efficiency since there is no mathematical correlation between E and V.
Algorithm # 2: Graphic Output of Directed Graph
Function Inputs: The node containing the course that you would like to see the prerequisites of.
Function Outputs: Visualization of courses in the prerequisite chain, including the final course in the chain. This can be utilized with our shortest path algorithm to visualize the fewest number of classes possible in order to satisfy the prerequisites of a final class. We are unsure about the exact specifics of our visualization at this time, but we would like to have an easy visualization of the required chain of courses to satisfy all prerequisites given an input course. We would like it to print both the entire graph of prerequisite courses as well as individual chains of courses.
Function Efficiency: We think the efficiency of our function should be O(n) for both time and memory. Each course added increases time and memory required in a linear fashion. 
Timeline
Data Acquisition and Processing: Our first goal will be to make a process to extract our data from our dataset and store it in a way that we can use it with the rest of our algorithms. Without this, we will not be able to complete any other algorithms. Ideal Completion Date: Week of 4/1.
Completion of Depth First Search: This will be our first algorithm we complete, as the search will be important to find specific classes that are a prerequisite for a given input. This will answer our first leading question: “What are the prerequisites required for a certain course?” “What is the least expensive (lowest credit hours) prerequisite chain of courses?” and Ideal Completion Date: Week of 4/8 (Before mid-project meeting)
Completion of Shortest Path Algorithm: This will be the second algorithm we complete, as the shortest path algorithm will be part of the Graphic Output of Graph algorithm, so it is necessary to implement this algorithm first. Ideal Completion Date: Week of 4/15
Completion of Graphic Output of Graph algorithm: This will be the last algorithm we complete, as it uses a previously completed algorithm (shortest path) and is also the most complex algorithm that we will implement. Ideal Completion Date: Week of 4/29
Production of Final Deliverables: This will be the final task, as we will need to prepare for our final project presentation. Ideal Completion Date: Week of 5/6
