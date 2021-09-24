/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:11:49 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/22 16:44:50 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a zero/NULL initialized t_lem struct
*/
t_lem	init_lem(void)
{
	t_lem	lem;

	lem.ants = 0;
	lem.vertices = 0;
	lem.edges = 0;
	lem.source = NULL;
	lem.sink = NULL;
	lem.error = 0;
	lem.n_paths = 0;
	lem.max_flow = 0;
	lem.last_index = 0;
	lem.compmat = NULL;
	return (lem);
}

/*
** returns a pointer to hashtab, all vertex pointers initialized to NULL
*/
t_hashtab	*init_ht(void)
{
	t_hashtab	*ht;
	int			i;

	ht = (t_hashtab *)malloc(sizeof(t_hashtab));
	if (!ht)
		return (NULL);
	ht->vertices = (t_vertex **)malloc(sizeof(t_vertex *) * HT_SIZE);
	if (!ht->vertices)
		return (NULL);
	i = 0;
	while (i < HT_SIZE)
	{
		ht->vertices[i] = NULL;
		i++;
	}
	return (ht);
}

/*
** allocates memory for a new vertex and returns a pointer to it
**
** @key: the name/id of the vertex
** @x, @y: the coordinates of the vertex
*/
t_vertex	*new_vertex(const char *key, const int x, const int y)
{
	t_vertex	*vertex;

	vertex = (t_vertex *)malloc(sizeof(t_vertex));
	if (!vertex)
		return (NULL);
	vertex->id = ft_strdup(key);
	vertex->x = x;
	vertex->y = y;
	vertex->visited = 0;
	vertex->edge = NULL;
	vertex->next = NULL;
	return (vertex);
}

/*
** allocates memory for it and returns a pointer to a new edge
**
** @src: the edge's source vertex
** @to: the edge's sink vertex
*/
t_edge	*new_edge(t_vertex *src, t_vertex *to)
{
	t_edge	*edge;

	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->src = src;
	edge->to = to;
	edge->cap = 1;
	edge->next_adjacent = NULL;
	edge->prev_in_path = NULL;
	return (edge);
}

/*
** allocates memory for a new struct that'll contain a path + info about it
**
** @iteration: the number of the current path (starts initially from 1)
*/
t_route	*new_route(int iteration)
{
	t_route	*route;

	route = (t_route *)malloc(sizeof(t_route));
	if (!route)
		return (NULL);
	route->i = iteration;
	route->is_valid = 0;
	route->len = 0;
	route->ants = 0;
	route->compatible_with = NULL;
	route->path = NULL;
	route->next = NULL;
	return (route);
}
