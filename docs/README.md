# OpenFlights route planner

CS 225 final project, Spring 2022
Eli Konopinski, Satvik Yellanki, Lucian Bontumasi, Jake Li

## Welcome to our CS225 Final Project!
For our final project, we used the OpenFlights database to find the optimal paths between airports, then plot that path onto a map!

All of our major code is in the main branch. Both our algorithm for DFS and Dijkstra's Algorithm are stored in the WeightedGraph.cpp file. For our visual output, everything is handled in Visual.cpp. All of our data is prepared in DataParser.cpp. Lastly, all of our test cases for the above algorithms are in the [/tests](/tests) folder. All of our input files are stored in the [/data](/data) folder, which stores both the pre-processed and post-processed CSV files. All of our images for the project are stored in the [/images](/images) folder, including our default output image file. And lastly, all documents related to the project, including this one and the video presentation, are stored in [/docs](/docs).

## How to use our project
We tried to make our project as easy to use as possible. After running "make", our entire project can be accesed using "./flights". An interactive text interface will guide you through how to access the various parts of the project. There are four options: DFS with text output to the console, Dijkstra's algorithm with text output to the console, Dijkstra's algorithm with visual output, and a simple test output for drawing the shortest line between two airports.

Within our simple UI, you may select input dataset files for all four of our functions, and output PNG files for our Dijkstra's visual output. There are also default file locations for both input and output, so if you would like to use our input data and standard output file location, you can. (If you would like to manually change the defaults, they are stored on lines 253-255 in [main.cpp](/main.cpp#L253)).

We have provided some fun flight paths to try in [/docs/paths_to_try](/docs/paths_to_try.md).

## Test suite
For our test suite, we used Catch v2.13.8, which is in the [/cs225](/cs225) folder. For our Dijkstra's and DFS, we made extensive testing in order to make sure our functions were working as expected. To run our tests, all you need to do is run "make test" and then "./test". 

For both algorithms, we used some basic graphs that we created, as well as a sample datasets from our larger dataset. We then manually computed the expected results, and used Catch to verify whether our expected results were met or not. All of our tests can be viewed in the [/tests](/tests) folder, with tests_dfs.cpp containing our tests for DFS, tests_dijkstra.cpp containing our tests for Dijkstra's Algorithm, and various images in the folder describing our test graphs. 

For our visual output, we think that the output is self explanatory. As our visual is mostly based off of Dijkstra's Algorithm, most of the work done in this algorithm is appropriately displaying the visuals, which anyone can test for themselves by playing around with our program for a couple of minutes!

## Third-party components
Lastly, we did use some third-party components to help build our project. All of the third-party components that we used are listed below.

- [rapidcsv: C++ CSV-parsing library](https://github.com/d99kris/rapidcsv) by Kristofer Berggren
	- License included in [LICENSE (rapidcsv).txt](LICENSE%20(rapidcsv).txt)
- [Equirectangular projection SW.jpg](https://commons.wikimedia.org/wiki/File:Equirectangular_projection_SW.jpg) (world map) by [Daniel R. Strebe](https://commons.wikimedia.org/wiki/User:Strebe), 15 Aug 2011
- Fixed Medium Semicondensed 6x13 (font): public domain
	- License text inside [font file itself](/fonts/fixed-6x13.bdf)
