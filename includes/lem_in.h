/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/14 18:06:42 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** HT_SIZE: hash table size, or the amount of buckets used by t_hashtab
*/
# define HT_SIZE 65535

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
** @ants: nbr of ants we have to transport through the graph
** @vertices: nbr of vertices in the graph
** @edges: nbr of edges in the graph
** @source: pointer to the source vertex
** @sink: pointer to the sink vertex
** @error: stores an error code (negative integer) in case an error occurs
** @n_paths: initially the total number of paths found, later overwritten by the
**	number of paths the ants will be distributed to
*/
typedef struct s_lem
{
	int				ants;
	int				vertices;
	int				edges;
	struct s_vertex	*source;
	struct s_vertex	*sink;
	int				error;
	int				n_paths;
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
** @x, @y: coordinates of the vertex (used only for visualizer)
** @visited: corresponding value for each bfs iteration
** @edge: a pointer to the struct t_list, a list of outgoing edges.
** @next: a pointer to another t_vertex whose id might have the same
** 	hashed value as the one being examined
*/
typedef struct s_vertex
{
	char			*id;
	int				x;
	int				y;
	int				visited;
	struct s_edge	*edge;
	struct s_vertex	*next;
}	t_vertex;

/*
** @src: the edge's source vertex
** @dst: the edge's destination vertex
** @cap: capacity of the edge, 0 or 1
** @next_adjacent: a pointer to the next edge that has the same source vertex
** @prev_in_path: a pointer to the edge before the current one on a path (the
**	path will be stored in reverse order, from sink to source)
*/
typedef struct s_edge
{
	struct s_vertex	*src;
	struct s_vertex	*to;
	int				cap;
	struct s_edge	*next_adjacent;
	struct s_edge	*prev_in_path;
}	t_edge;

/*
** @i: route's ordinal number, used to compare whether a vertex has been visited
**	during a breadth-first search iteration
** @is_valid: marked True (1) if the path in this instance reached the sink
** @len: length of this path
** @path: pointer to the head of the path
** @next: next route/path
*/
typedef struct s_route
{
	int				i;
	int				is_valid;
	int				len;
	int				ants;
	int				*compatible_with;
	struct s_edge	*path;
	struct s_route	*next;
}	t_route;

/*
** "hash table", aka an array of pointers to vertices
*/
typedef struct s_hashtab
{
	struct s_vertex	**vertices;
}	t_hashtab;

t_lem		init_lem(void);
t_hashtab	*init_ht(void);
t_input		*read_input(void);
t_vertex	*new_vertex(const char *key, const int x, const int y);
t_edge		*new_edge(t_vertex *src, t_vertex *dst);
t_input		*get_vertices(t_input *input, t_hashtab *ht, t_lem *lem);
t_vertex	*get(t_hashtab *ht, const char *key);
void		set(t_hashtab *ht, const char *key, const int x, const int y);
int			get_edges(t_input *input, t_hashtab *ht);
int			parse_input(t_input *input, t_hashtab *ht, t_lem *lem);
t_route		*new_route(int iteration);
t_route		*find_paths(t_lem *lem, t_vertex *s, t_vertex *t);
t_vertex	**wipe_queue(t_vertex **queue, t_vertex *source, const int size);
t_vertex	*pop_first(t_vertex ***queue);
void		queue_append(t_vertex ***queue, t_vertex *vertex);
void		path_prepend(t_edge **path, t_edge *edge);
t_route		*sort_paths(t_route *route);
t_route		*find_distinct(t_route *route, t_route *bw_route, t_lem *lem);
t_route		*path_reverse(t_route *route);
t_route		*join_paths(t_route *r0, t_route *r1);
t_route		*next_compatible(t_route *route);
void		remove_duplicate_paths(t_route *route, t_lem *lem);
void		distribute_ants(t_route *route, int limit, int ants, int *pants);
void		store_ant_count(t_route *route, int *pants, int limit, int n_paths);
int			sort_ants(t_route *route, t_lem *lem, int ants, int *pants);
char		***prepare_output_arr(t_route *route, t_lem lem);
char		***fill_output_arr(t_route *route, t_lem lem, char ***out);
int			print_output(t_route *route, t_lem lem, t_input *input);
void		free_input(t_input **input);
void		free_ht(t_hashtab **ht);
void		free_route(t_route **route);
void		free_output(char ***out);
int			die_if_error(int error, t_input **input, t_hashtab **ht, \
			t_route **route);

#endif
