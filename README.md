# lem_in
a graph traversing algorithm implementation

## ABOUT
*lem_in* is a program that directs "ants" through an "antfarm" (i.e. through a graph's nodes/vertices).

## RULES
A node or an edge can be occupied by one ant at a time, excluding the source and sink nodes. In graph theory terms, all vertices and edges have a capacity of one. All of the ants must be transported through the graph using the least amount of turns. Ants on the graph need to move on each turn.

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
+ `vertex_ids` are arbitrary alphanumerical strings, followed by two space separated integers, which represent their coordinates (useful only when visualizing the graph). a `vertex_id` can't start with an 'L'.
+ source and sink vertices are denoted by a preceding `##start` and `##end`, respectively
+ `edges` are two `vertex-ids` separated by a '-' (dash)
+ The input can have comments (lines that start with a '#') anywhere, which are ignored by the parser

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
Turns out that the easiest approach for most students and for me as well was to tweak the [Edmonds-Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm).
In a nutshell, the EK algo performs a breadth-first search repeatedly on the graph, updating the graph's capacities on each run until the graph is fully saturated so that the sink can no longer be reached. The found paths are stored along the way.

My implementation does this repeated bfs from source to sink and then backwards, from sink to source, because the graph is bidirectional, hence the edges have a capacity for both directions. The backward-bfs also ensures we won't use overlapping paths, as the fw-bfs has now blocked the edges of the paths were traversed in both directions.

Using the first graph example again, this is how the path-finding algo progresses:

**1st run**
```
   /--(3)---(4)
  /          |
(s)>>>(1)>>>(2)>>>(t)
       |          /
      (5)---(6)--/
```
path found:
s - 1 - 2 - t

The found path is now blocked to the direction of the arrows.

**2nd run**
```
   >>>(3)>>>(4)
  >          v
(s)---(1)<<<(2)---(t)
       v          >
      (5)>>>(6)>>>
```
path found:
s - 3 - 4 - 2 - 1 - 5 - 6 - t

There are no more outgoing edges from the source vertex that have capacity, so the forward-bfs is finished. Now we find all paths from sink to source.

**3rd run**
```
   <<<(3)<<<(4)
  <          ^
(s)---(1)xxx(2)<<<(t)
       |          /
      (5)---(6)--/
```
path found:
t - 2 - 4 - 3 - s

Notice how from the 2nd run the edge `2-1` already has flow going through it in both directions, so it's untraversable.

**4th run**
```
   /--(3)---(4)
  /          |
(s)<<<(1)---(2)---(t)
       ^          <
      (5)<<<(6)<<<
```
path found:
t - 6 - 5 - 1 - s

Now all outgoing edges of the sink vertex are saturated and the bw-bfs ends.

Now the 4 found paths are sorted in ascending order of length and reversed so that all go from source to sink. Then each path is marked compatible with all other paths that they do not intersect/share an edge with.

```
path1:
s - 1 - 2 - t
compatible with no other path

path2:
s - 3 - 4 - 2 - t
compatible with path3

path3:
s - 1 - 5 - 6 - t
compatible with path2

path 4:
s - 3 - 4 - 2 - 1 - 5 - 6 - t
compatible with no other path
```

## ANT DISTRIBUTION
Starting from the shortest path, we try adding one (compatible) path at a time and calculate the amount of turns for every path combination.
Once the combo with the minimum amount of turns has been found, we print the moves out using those paths.

The formula for calculating the amount of ants to send down one path before the same amount of turns would be achieved by using also the next path is
`<next_path_length> - <current_path_length>`, i.e. the difference of the path lengths.

After calculating those differences for each following path in the current combination and subtracting the sum of differences from the total ant count, the rest of the ants are allocated to all paths in the combo, cycling through them in order until no ants are left.

The formula for calculating the amount of turns it will take with the current path combo and the amount of ants allocated for each path is the maximum value of `<current_path_length> + <number_of_ants_on_current_path> - 2` for all paths in the combo.

example, assuming we have 4 ants:
1. with path1 as our base path, try to allocate the differences of compatible paths --> there are none, so we allocate all ants to path 1 --> `turns = 4 (path length) + 4 (ants on the path) - 2 = 6`
2. using path2 as the base path, allocate difference of following paths --> `5 (path2 length) - 5 (path3 length) = 0`
3. allocate remaining ants (in this case all ants, since the paths are the same length) evenly to all paths --> `path2_ants = 2` `path3_ants = 2`
4. calculate turns with this path combo --> ` path2_turns = 5 + 2 - 2 = 5` `path3_turns = 5 + 2 - 2 = 5` --> max value is 5
5. path3 not comaptible with following paths --> `turns = 5 + 4 - 2 = 7`
6. path4 same as path3 --> `turns = 8 + 4 - 2 = 10`
7. path2 together with path3 yields the least amount of turns (5), so we will use them.

## THOUGHTS
The project familiarizes the student with graph-theory and invites them to explore different algorithms best suited for flow optimization.
At first I misunderstood the goal of this project and I tried to implement a max flow graph search algorithm. Eventually I figured out that we are not trying to find the max flow, but something more.

I wasted a ton of time trying to figure out why the supposedly best choice algo (Edmonds-Karp) didn't yield results that worked, until I started to really think what's going on and what we're actually trying to achieve here.
It turned out that the EK algo assumes some graph attributes that don't apply to this project, such as vertices having an infinite capacity.
Also EK implementations usually have the edges having a reverse edge and that they are used to update the residual graph, which all over-complicated the problem; in lem_in, we can only have 1 ant occupy an edge or a vertex at a time. We do not need reverse edges or residual graphs. Once an ant has passed through an edge, it's no longer usable in that direction.

More than anything else, I learned that I should not trust blindly on suggestions like "the EK algo is the way to go here". Yeah, it eventually turned out to be a variation of EK, but before I had thought through the problem myself and tried to implement it without understanding what it produces or what we are even trying to produce, a lot of time and motivation was wasted.

Overall a great project that taught about optimization, graphs and algorithms through research and of course writing them out and getting it to work. But also the toughest yet.
I completed over half of the next, supposedly "harder" project before I finished this one, while also doing extra-curricular side-projects. Definitely harder than it should be at this point of learning algorithms.
