# lem_in
**school project**: a project about graph traversing algorithm implementation.

## ABOUT
*** WIP ***
*lem_in* is a program that directs "ants" through an "antfarm" (i.e. through a graph's nodes/vertices).

## RULES
A node or an edge can be occupied by one ant at a time, excluding the source and sink nodes. All of the ants must be transported through the graph using the least amount of turns. Ants need to move on each turn.
 
For example, consider the graph below:

```
         ---(4)
        /    |
   ---(3)    |
  /          |
(s)---(1)---(2)---(t)
       |          /
       |    (6)---
       |    /
      (5)---
```

Least amount of turns in the case of one ant would be using the shortest ("middle") path `s - 1 - 2 -t`,
but for 4 ants, the least amount of turns would be accomplished only by using the paths `s - 3 - 4 - 2 - t` and `s - 1 - 5 - 6 - t` like so:

```
turn 1: antA s -> 1, antB s -> 3
turn 2: antA 1 -> 5, antB 3 -> 4, antC s -> 3, antD s -> 1
turn 3: antA 5 -> 6, antB 4 -> 2, antC 3 -> 4, antD 1 -> 5
turn 4: antA 6 -> t, antB 2 -> t, antC 4 -> 2, antD 5 -> 6
turn 5: antC 2 -> t, antD 6 -> t
```

Input for the program is given in a text file, in a specific format:

```
the_number_of_ants
vertex_1 x_coord y_coord
[...]
vertex_n x_coord y_coord
vertex_1-vertex_3
[...]
vertex_8-vertex_n
```

Example input:
```
2
1 0 2
##start
0 2 0
##end
4 2 6
2 4 2
3 4 4
0-2
2-3
3-4
4-1
0-1
```
which says that we need to transport 2 ants through the following graph:
```
    (0) <---- start/source
   /   \
 (1)   (2)
  |     |
  |    (3)
   \   /
    (4) <---- end/sink
```

Example output for the above graph:
```
L1-1 L2-2
L1-4 L2-3
L2-4
```

Note that using the left side for both ants would result in the same amount of turns, which is just as fine:
```
L1-1
L1-4 L2-1
L2-4
```


## NOTES
The project familiarizes the student with graph-theory and invites them to explore different algorithms best suited for flow optimization.
At first this project led me astray, as I tried to implement a max flow graph search algorithm. Eventually I figured out that we are not trying to find the max flow, but a little more than that...
