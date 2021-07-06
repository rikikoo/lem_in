/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:11:49 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/06 18:53:56 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to a zero/NULL initialized t_lem
*/
t_lem	*init_lem(void)
{
	t_lem	*lem;

	lem = (t_lem *)malloc(sizeof(t_lem));
	if (!lem)
		return (NULL);
	lem->ants = 0;
	lem->vertices = 0;
	lem->edges = 0;
	lem->max_flow = 0;
	lem->source = NULL;
	lem->sink = NULL;
	return (lem);
}

/*
** init_index returns a pointer to t_index, all vertex pointers NULL initialized
*/
t_index	*init_index(void)
{
	t_index	*index;
	int		i;

	index = (t_index *)malloc(sizeof(t_index));
	if (!index)
		return (NULL);
	index->vertices = (t_vertex **)malloc(sizeof(t_vertex *) * HT_SIZE);
	if (!index->vertices)
		return (NULL);
	i = 0;
	while (i < HT_SIZE)
	{
		index->vertices[i] = NULL;
		i++;
	}
	return (index);
}

/*
** allocates memory for a new vertex and returns a pointer to it
**
** key: the name/id of the vertex
** x, y: the coordinates of the vertex
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
** allocates memory for and returns a pointer to t_edge
**
** src: the edge's source vertex
** dst: the edge's sink vertex
*/
t_edge	*new_edge(t_vertex *src, t_vertex *dst)
{
	t_edge	*edge;

	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->src = src;
	edge->to = dst;
	edge->fwd_cap = 1;
	edge->next = NULL;
	return (edge);
}

/*
** returns a struct containing room for a path as a pointer to vertex names &
** info about the path (if path reaches sink or not, length of the path, etc.)
*/
t_route	*new_route(t_vertex *source, int vertices, int iteration)
{
	t_route	*route;
	int		i;

	route = (t_route *)malloc(sizeof(t_route));
	route->path = (t_vertex **)malloc(sizeof(t_vertex *) * (vertices + 1));
	if (!route || !route->path)
		return (NULL);
	i = 0;
	while (i <= vertices)
	{
		route->path[i] = NULL;
		i++;
	}
	route->path[0] = source;
	route->i = iteration;
	route->is_valid = 0;
	route->len = 0;
	route->next = NULL;
	return (route);
}
