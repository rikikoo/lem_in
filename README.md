# lem_in
a graph traversing algorithm implementation

## ABOUT
*lem_in* is a program that directs "ants" through an "antfarm" (i.e. through a graph's nodes/vertices).
The program takes the antfarm layout and the number of ants to pass through it as input from STDIN, finds different paths and determines which paths to use for transporting the ants.
The program optimises ant distribution so that the minimum amount of _turns_ is used to get all ants through the antfarm. A turn is when any ant moves from one step forward. Multiple ants may move at once, within the constraints of the rules.

## RULES
A node or an edge can be occupied only by one ant at a time, excluding the source and sink nodes. In graph theory terms, all vertices and edges have a capacity of one. All of the ants must be transported through the graph using the least amount of turns. Ants on the graph need to move on each turn.

For example, consider the graph below:

```
   /--(3)---(4)
  /          |
(s)---(1)---(2)---(t)
       |          /
      (5)---(6)--/
```

Least amount of turns in the case of one ant would be using the shortest ("middle") path `s - 1 - 2 - t`,

but for 4 ants the least amount of turns would be accomplished only by using the paths `s - 3 - 4 - 2 - t` and `s - 1 - 5 - 6 - t` like so:

```
turn 1: antA s -> 1, antB s -> 3
turn 2: antA 1 -> 5, antB 3 -> 4, antC s -> 3, antD s -> 1
turn 3: antA 5 -> 6, antB 4 -> 2, antC 3 -> 4, antD 1 -> 5
turn 4: antA 6 -> t, antB 2 -> t, antC 4 -> 2, antD 5 -> 6
turn 5: antC 2 -> t, antD 6 -> t
```

### Program input
Input for the program is given in a text file in a specific order and format:

```
number_of_ants
vertex_ids
edges
```
+ the first line of the input is `number_of_ants`, an integer
+ `vertex_ids` are lines with arbitrary alphanumerical strings, followed by two space separated integers, which represent their coordinates (useful only when visualizing the graph). a `vertex_id` can't start with an `L`.
+ source and sink vertices are denoted by a preceding `##start` and `##end`, respectively
+ `edges` are two `vertex-ids` separated by a `-` (dash)
+ The input can have comments (lines that start with a `#`) anywhere, which are ignored by the parser

Example input:
```
2
1 0 2
##start
0 1 0
##end
4 1 4
2 2 1
# this is a comment
3 2 3
0-2
2-3
3-4
# this as well
4-1
0-1
```
This input tells us that we need to transport 2 ants through the following graph:
```
    (0) <---- start/source
   /   \
  /    (2)
(1)     |
  \    (3)
   \   /
    (4) <---- end/sink
```

### Program output
The program will output the input it received, followed by the ants' moves.

Moves of each ant will be printed in the format `L<ant_number>-<vertex_id>`.

Example output of the moves for the above graph:
```
L1-1 L2-2
L1-4 L2-3
L2-4
```

Note that using the left side for both ants would result in the same amount of turns, which is just as fine as using both paths:
```
L1-1
L1-4 L2-1
L2-4
```

## THE ALGORITHM
### Pathfinder
Turns out that the easiest approach for most students and for me as well was to tweak the [Edmonds-Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm).

In a nutshell, the EK algo performs a breadth-first search repeatedly on the graph, updating the graph's capacities on each run until the graph is fully saturated so that the sink can no longer be reached.

After each BFS iteration, we attempt to traverse any and all outgoing edges from the sink that have a negative flow (meaning that in the "correct" direction, the edge's flow must be positive, i.e. the edge is traversable). If the traversal along the edges with negative flow reaches the source, we have a path.

All paths found after a BFS flow-update belong to a *set* of paths. Every path is wrapped with a struct containing metadata about the path, such as the length of the path and indeed the set it belongs to.
During these backtracking sessions every visited node is also marked, just like in the breadth-first search algorithm, so we won't include any paths that would overlap in a set.

### Ant distribution
Determining which set of paths to use is easy: simply calculate the amount of turns for every set as follows:

1. Iterating through the paths in order going from shortest to longest, allocate ants for each path:
`<longest_path_length> - <current_path_length>`.

2. After calculating those differences for each path in the set and subtracting the sum of differences from the total ant count, the rest of the ants are allocated to all paths in the combo, cycling through them in order until no ants are left.

3. The formula for calculating the amount of turns it will take with the current path combo and the amount of ants allocated for each path is the maximum value of `<current_path_length> + <number_of_ants_on_current_path> - 2` for all paths in the combo.

For example, let's say that there are 40 ants and the path lengths in a set are:
  - path1: 4
  - path2: 6
  - path3: 6
  - path4: 9
  - path5: 12
  - path6: 15

1.
```
path1.ants = 15 - 4 = 11
path2.ants = 15 - 6 = 9
path3.ants = 15 - 6 = 9
path4.ants = 15 - 9 = 6
path5.ants = 15 - 12 = 3
path6.ants = 15 - 15 = 0
```
2.
```
ants_left = total_ants - allocated_ants = 40 - (11 + 9 + 9 + 6 + 3 + 0) = 40 - 38 = 2
path1.ants += 1 = 11 + 1 = 12
path2.ants += 1 = 9 + 1 = 10
```
3.
```
path1.turns = path1.len + path1.ants - 2 = 4 + 12 - 2 = 14
path2.turns = 10 + 6 - 2 = 14
path3.turns = 9 + 6 - 2 = 13
path4.turns = 6 + 9 - 2 = 13
path5.turns = 3 + 12 - 2 = 13
path6.turns = 15 + 0 - 2 = 13

turns = 14
```

## THOUGHTS
The project familiarizes the student with graph-theory and invites them to explore different algorithms best suited for flow optimization.
At first I misunderstood the goal of this project and I tried to implement a max flow graph search algorithm. Eventually I figured out that we are not trying to find the max flow, but something more.

I wasted a ton of time trying to figure out why the supposedly best choice algo (Edmonds-Karp) didn't yield results that worked, until I started to really think what's going on and what we're actually trying to achieve here.
It turned out that the EK algo assumes some graph attributes (e.g. vertices have infinite capacity) that don't apply to this project.

More than anything else, I learned that I should not trust blindly on suggestions like "the EK algo is the way to go here". Yeah, it eventually turned out to be a variation of EK, but before I had thought through the problem myself and tried to implement it without understanding what it produces or what we are even trying to produce, a lot of time and motivation was wasted.

Overall a great project that taught optimization, graphs and algorithms through research and of course writing them out and getting it to work. But also the toughest yet.
I completed over half of the next, supposedly "harder" project before I finished this one, while also doing extra-curricular side-projects. Definitely harder than it should be at this point of learning algorithms.
