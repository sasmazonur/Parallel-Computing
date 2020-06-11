# Functional Decomposition
This project uses parallelism, not for speeding data-computation, but for programming-convenience. It creates a month-by-month simulation in which each agent of the simulation will execute in its own thread where it just has to look at the state of the world around it and react to it

### Performance Graph
<p align="center"><img width=90.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/Functional%20Decomposition%20/Graph.png"></p>

### What your own-choice quantity was and how it fits into the simulation.
There are also Rabbits living in the same environment. If there are too many Deers, Deers can't find enough grain. They get so hungry that they consider eating 5 rabbits all together. They flip a wood stick (Flip coin) and decide rather they eat the rabbits or not. If deers don’t eat the Rabbits, rabbit number keep increasing every month.

### A commentary about the patterns in the graph and why they turned out that way. What evidence in the curves proves that your own quantity is actually affecting the simulation correctly?
As we can see from the graph and data table above, as deer number increases, number of rabbits are decreasing. Also, the number of grain deer depends on the amount of grain available to eat. In addition, the amount the grain grows is affected by the temperature, amount of precipitation, and the number of grain deer around to eat it.

### How to Run:
To run on Server:
./run_bash_server.sh

To run on MacOS
./run_bash_maxos.sh

It will generate output.csv file with desired outputs. 


Reference:http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj03.html
