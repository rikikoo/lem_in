/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/18 19:32:11 by rkyttala         ###   ########.fr       */
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
** rooms: # of vertices in the graph
** tubes: # of edges in the graph
** source: name/id of the source vertex
** target: name/id of the sink vertex
*/
typedef struct s_lem
{
	int		ants;
	int		rooms;
	int		tubes;
	char	*source;
	char	*target;
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
** id: name of the room/vertex
** x, y: coordinates of the vertex (used only for visualizer)
** visited: boolean for breadth-first search algorithm
** tube: a pointer to the struct t_list, a list of outgoing tubes/edges.
** next: a pointer to another t_room whose id might have the same
** 	hashed value as this one.
*/
typedef struct s_room
{
	char			*id;
	int				x;
	int				y;
	int				visited;
	struct s_link	*tube;
	struct s_room	*next;
}	t_room;

/*
** src: name/id of the edge's source vertex
** dst: name/id of the edge's sink vertex
** next: a pointer to the next edge that has the same source vertex
*/
typedef struct s_link
{
	char			*src;
	char			*to;
	int				cost;
	struct s_link	*next;
}	t_link;

/*
** "hash table", aka an array of pointers to vertices
*/
typedef struct s_index
{
	struct s_room	**rooms;
}	t_index;

int		hashof(const char *key);
t_index	*init_index(void);
void	set(t_index *index, const char *key, const int x, const int y);
t_room	*get(t_index *index, char *key);
t_room	*new_room(const char *key, const int x, const int y);
int		parse_input(t_input *input, t_index *index, t_lem *lem);
int		get_tubes(t_input *input, t_index *index);
int		edm_karp(t_index *index, t_lem *lem);

#endif
