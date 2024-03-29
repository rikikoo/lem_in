/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 23:51:41 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** HT_SIZE: hash table size, or the amount of buckets used by t_hashtab
*/
# define HT_SIZE 1024

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
** @source, @sink: pointers to the source and sink vertex
** @ants: nbr of ants we have to transport through the graph
** @vertices: nbr of vertices in the graph
** @edges: nbr of edges in the graph
** @error: stores an error code (negative integer) in case an error occurs
** @path_sets: the number of path combinations/sets found
** @turns: number of turns calculated for the set that the ants eventually use
** @best_set: id number of the set of paths that the ants will use
** @max_flow: the number of paths in the best set
*/
typedef struct s_lem
{
	struct s_vertex	*source;
	struct s_vertex	*sink;
	int				ants;
	int				vertices;
	int				edges;
	int				error;
	int				path_sets;
	int				turns;
	int				best_set;
	int				max_flow;
}	t_lem;

/*
** linked list for the program's input, containing the data for constructing
** the graph. each list element contains a single line of input.
*/
typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}	t_input;

/*
** @id: name of the vertex
** @x, @y: coordinates of the vertex (used only in a visualizer)
** @visited: holds a corresponding value for each bfs iteration
** @valid: an alternate "visited" value for the path storing function
** @edge: a pointer to struct t_edge, i.e. an adjacency list of outgoing edges
** @next: a pointer to another t_vertex whose id might have the same
** 	hashed value as the one being examined
*/
typedef struct s_vertex
{
	char			*id;
	int				x;
	int				y;
	int				visited;
	int				valid;
	struct s_edge	*edge;
	struct s_vertex	*next;
}	t_vertex;

/*
** @src: the edge's source vertex
** @dst: the edge's destination vertex
** @has_cap: boolean, True (1) if edge has capacity (is traversable during BFS)
** @flow: flow of an edge, ranging from -1 to 1 (inclusive)
** @next_adjacent: a pointer to the next edge that has the same source vertex
** @next_on_path: a pointer to the following edge on a found path
*/
typedef struct s_edge
{
	struct s_vertex	*src;
	struct s_vertex	*to;
	int				has_cap;
	int				flow;
	struct s_edge	*next_adjacent;
	struct s_edge	*next_on_path;
}	t_edge;

/*
** t_route is a wrapper struct for each path and contains metadata about it
**
** @id: ordinal number of the path in a set
** @is_valid: true (1) if the path goes from source to sink, otherwise false (0)
** @len: length of the path (number of vertices on this path - 1)
** @set: number of the BFS iteration during which this route was found
** @ants: number of ants allocated for this path
** @path: pointer to the first edge of a list of edges from source to sink
** @next: next route
*/
typedef struct s_route
{
	int				id;
	int				is_valid;
	int				len;
	int				set;
	int				ants;
	struct s_path	*path;
	struct s_route	*next;
}	t_route;

/*
** @edge: pointer to an edge on this path
** @next: next edge on this path
*/
typedef struct s_path
{
	struct s_edge	*edge;
	struct s_path	*next;
}	t_path;

/*
** "hash table", aka an array of pointers to vertices
*/
typedef struct s_hashtab
{
	struct s_vertex	**vertices;
}	t_hashtab;

/*
** INPUT READING
*/
t_lem		init_lem(void);
t_hashtab	*init_ht(void);
t_input		*read_input(void);

/*
** INPUT PARSING
*/
int			parse_input(t_input *input, t_hashtab *ht, t_lem *lem);
t_vertex	*new_vertex(const char *key, const int x, const int y);
t_edge		*new_edge(t_vertex *src, t_vertex *dst);
t_input		*get_vertices(t_input *input, t_hashtab *ht, t_lem *lem);
int			get_edges(t_input *input, t_hashtab *ht);
t_vertex	*get(t_hashtab *ht, const char *key);
void		set(t_hashtab *ht, const char *key, const int x, const int y);

/*
** GRAPH SEARCH
*/
t_route		*saturate_graph(t_lem *lem);
t_route		*new_route(int id);
t_vertex	**wipe_queue(t_vertex **queue, t_vertex *src, int size, int iter);
t_vertex	*pop_first(t_vertex ***queue);
void		enqueue(t_vertex **queue, t_vertex *vertex, int pos);
void		search_edge_prepend(t_edge **search_edges, t_edge *edge);

/*
** PATH STORING
*/
t_path		*path_prepend(t_path *path, t_edge *edge);
t_edge		*get_rev_edge(t_edge *edge);
t_route		*follow_flow(t_lem *lem, t_route *route, t_edge *edge, int iter);
void		remove_invalids(t_route *route);
void		sort_paths(t_route *route, t_lem *lem);

/*
** ANT DISTRIBUTION
*/
t_route		*find_best_set(t_route *route, t_lem *lem);
int			calculate_diff(t_route *route, int ants, int set);
void		distribute_ants(t_route *route, int ants, int set);
int			calculate_turns(t_route *route, int set);

/*
** OUTPUT
*/
char		***prepare_output(t_route *route, t_lem lem, int *pants);
void		fill_output_arr(t_route *route, t_lem lem, char ***out, int *pants);
void		print_input(t_input *input);
int			print_output(t_route *route, t_lem lem, t_input *input);

/*
** FREE MEMORY
*/
void		free_input(t_input **input);
void		free_output(char ***out);
void		free_ht(t_hashtab **ht);
void		free_route(t_route **route);
int			die_if_error(int errno, t_input **input, t_hashtab **ht, \
				t_route **route);

#endif
