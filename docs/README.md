# OpenFlights route planner

CS 225 final project, Spring 2022
Eli Konopinski, Satvik Yellanki, Lucian Bontumasi, Jake Li

## Welcome to our CS225 Final Project!
For our final project, we used the OpenFlights database to find the optimal paths between airports, then plot that path onto a map!

All of our major code is in the main branch. Both our algorithm for DFS and Djikstra's Algorithm are stored in the WeightedGraph.cpp file. For our visual output, everything is handled in Visual.cpp. All of our data is prepared in DataParser.cpp. Lastly, all of our test cases for the above algorithms are in the [/tests](/tests) folder. All of our input files are stored in the [/data](/data) folder, which stores both the pre-processed and post-processed CSV files. All of our images for the project are stored in the [/images](/images) folder, including our default output image file. And lastly, all documents related to the project, including this one and the video presentation, are stored in [/docs](/docs).

## How to use our project
We tried to make our project as easy to use as possible. After running "make", our entire project can be accesed using "./flights". A simple GUI will guide you on how to access whichever part of the project you want. We have 4 options. DFS with text output to console, Djikstra's with text output to console, Djikstra's with visual output, and a simple test output for drawing the shortest line between two airports.

For choosing input and output, both can be selected upon running your desired function, if applicable. You can select input files for all 4 of our functions, and output files for the PNG from our Djikstra's visual output all within our simple GUI. There are also default file locations for both of them, so if you would like to use our input data and standard output file location, you can.

We have provided some fun paths to try in our [/docs/paths_to_try](/docs/paths_to_try) folder.

## Test suite
For our test suite, we used Catch v2.13.8, which is in the [/cs225](cs225/) folder. For our Djikstra's and DFS, we made extensive testing in order to make sure our functions were working as expected. To run our tests, all you need to do is run "make test" and then "./test". 

For both algorithms, we used some basic graphs that we created, as well as a sample datasets from our larger dataset. We then manually computed the expected results, and used Catch to verify whether our expected results were met or not. All of our tests can be viewed in the [/tests](/tests) folder, with tests_dfs.cpp containing our tests for DFS, tests_djikstra.cpp containing our tests for Djikstra's Algorithm, and various images in the folder describing our test graphs. 

For our visual output, we think that the output is self explanatory. As our visual is mostly based off of Djikstra's Algorithm, most of the work done in this algorithm is appropriately displaying the visuals, which anyone can test for themselves by playing around with our program for a couple of minutes!

## Third-party components
Lastly, we did use some third-party components to help build our project. All of the third-party components that we used are listed below.

- [rapidcsv: C++ CSV-parsing library](https://github.com/d99kris/rapidcsv) by Kristofer Berggren
	- License included in [LICENSE (rapidcsv).txt](LICENSE%20(rapidcsv).txt)
- [Equirectangular projection SW.jpg](https://commons.wikimedia.org/wiki/File:Equirectangular_projection_SW.jpg) (world map) by [Daniel R. Strebe](https://commons.wikimedia.org/wiki/User:Strebe), 15 Aug 2011
