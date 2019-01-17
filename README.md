# Castle-Game
The algorithm goes like this:


1-	Initialize the structures of enemy, tower, heap, and queue. 
2-	Create a total number of 8 binary heaps for the active and inactive enemies in each region.
3-	Create a queue to store the killed enemies in it.
4-	Read the data from the input file and store it in its appropriate locations of the towers and store all the enemies at first in the inactive heaps sorted in an ascending order by their arrival time.
5-	Initialize a flag = 0, that represents the state of the game (flag =1 “Loss”, flag=2 “Win”)
6-	While all the towers haven’t been destroyed yet, nor all the enemies are killed, loop on the 4 regions and do the following:
7-	Check on the type of the active enemies, if any of them is a paver, update the unpaved distance of this region based on the paver power.
8-	Update the distance of all the active enemies; decrease it by one meter if this meter is already paved and not less than 2 meters from the castle, otherwise leave the distance unchanged. 
9-	Compare the arrival time of the inactive enemies with the current time stamp, and transforms them into active enemies if their arrival time == current time stamp. (We don’t need to loop over all the inactive heap, just the first enemies until we reach an enemy with an arrival time greater than the current time)
10-	Calculates the priority of the active enemies and updates it in its variable at the enemies’ structures. 
11-	Sort the active enemies in the active binary heap according to their priority in a descending order. 
12-	Fire from the enemies on the tower; loop on the active enemies and check their type, then increase the damage of the tower by the formula mentioned in the project document. If the damage of the tower is greater than the tower health, mark this tower as destroyed.
13-	Fire from the tower on the enemy; reduce the health of the first N enemies that the tower can shoot at by the formula mentioned in the project document based on the enemy type. Then, check if any of these enemies are killed and store them in the killed enemies queue, delete it from the active heap.
14-	Repeat steps (7 -> 13) on each region of the 4 regions.
15-	Then, check if any of the towers is destroyed, and move the enemies at its region to the following region by inserting the inactive and active enemies of the destroyed region into their corresponding inactive and active heaps of the following region. 
16-	At the end of the while loop, check if all the towers are destroyed, or all the number of killed enemies equals to the original number of enemies, and update the flag to 1 or 2 respectively, if any of these conditions were satisfied. Otherwise, the flag remains 0 and the loop on the regions goes over again until the flag changes its value.
17-	After the loop ends, we get the output data from the killed enemies queue, the towers, and the flag state, calculate the required statistics and store them in the output file.
