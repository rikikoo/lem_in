/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/21 12:53:39 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define HT_SIZE 10000
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
** ants: # of ants we have to transport through the graph
** vertices: # of vertices in the graph
** edges: # of edges in the graph
** source: name/id of the source vertex
** sink: name/id of the sink vertex
*/
typedef struct s_lem
{
	int		ants;
	int		vertices;
	int		edges;
	char	*source;
	char	*sink;
}	t_lem;

/*
** linked list for the program's input, containing the data for constructing
** the graph
*/
typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}	t_input;

/*
** id: name of the vertex
** x, y: coordinates of the vertex (used only for visualizer)
** visited: boolean for breadth-first search algorithm
** edge: a pointer to the struct t_list, a list of outgoing edges.
** next: a pointer to another t_vertex whose id might have the same
** 	hashed value as this one.
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
** src: name/id of the edge's source vertex
** dst: name/id of the edge's destination vertex
** next: a pointer to the next edge that has the same source vertex
*/
typedef struct s_edge
{
	char			*src;
	char			*to;
	int				cost;
	struct s_edge	*next;
}	t_edge;

/*
** "hash table", aka an array of pointers to vertices
*/
typedef struct s_index
{
	struct s_vertex	**vertices;
}	t_index;

int			hashof(const char *key);
t_index		*init_index(void);
void		set(t_index *index, const char *key, const int x, const int y);
t_vertex	*get(t_index *index, char *key);
t_vertex	*new_vertex(const char *key, const int x, const int y);
int			parse_input(t_input *input, t_index *index, t_lem *lem);
int			get_edges(t_input *input, t_index *index);
int			edm_karp(t_index *index, t_lem *lem);

#endif
