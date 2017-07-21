Kaley Findley Project 3

For clustering algorithms K-Means and EM I used Weka for running my tests and my plots used in my analysis. No additional packages were required to run these tests.

For the dimensionality algorithms (PCA, Random Projections, and Random Subset) I used weka but I needed to download the student-filters package from the package manager in weka. 

For Random Projections and Random Subset I ran my RandomGen java file (provided in code) to generate random values for the seeds. Run this to find the seed values to use before running RP or RS for part 2 and later parts.

For part 2, to see the eigenvalues for PCA, go to the Select Attributes tab in weka and run PCA from there (using Ranker) and it’ll provide a nice result buffer.

As for ICA I used Abagail. I provided my version of Abagail code that contains the script allTogetherNow to run ICA for both of my data sets (wine and online news data). This provided me with csv files containing the transformed features in a readable manner so I can use the ICA results in weka for part 3, 4, and 5 for both data sets.

To visualize the clusters for part 3, once you run the test, right click on result buffer in bottom left box and go to visualize cluster assignments. You can save these clusters (they save as arff files) to later load them in the preprocess tab in weka to use for part 5.

Also, after running a particular dimensionality algorithm on a dataset, click the save button (upper right) to save the new dataset (they also save as arff files) to use later in part 3.