/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/12 23:45:00 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** makes edge(src->dst)'s rev pointer point to edge(dst->src) and vice versa
**
** @src: pointer to the edge's source vertex
** @dst: pointer to the edge's sink vertex
*/
static void	link_reverse_edges(t_vertex *src, t_vertex *dst)
{
	t_edge	*fwd_edge;
	t_edge	*bwd_edge;

	fwd_edge = src->edge;
	bwd_edge = dst->edge;
	while (fwd_edge->to != dst)
		fwd_edge = fwd_edge->next_adjacent;
	while (bwd_edge->to != src)
		bwd_edge = bwd_edge->next_adjacent;
	dst->edge->reverse = fwd_edge;
	src->edge->reverse = bwd_edge;
}

/*
** appends new edge to the list of edges coming out of a vertex
**
** @src: pointer to the edge's source vertex
** @dst: pointer to the edge's sink vertex
*/
static void	edge_append(t_vertex *src, t_vertex *dst)
{
	t_edge	*edge;

	edge = src->edge;
	if (edge != NULL)
	{
		while (edge->next_adjacent != NULL)
		{
			edge = edge->next_adjacent;
		}
		edge->next_adjacent = new_edge(src, dst);
	}
	else
		src->edge = new_edge(src, dst);
}

/*
** splits input line containing the two vertex ids into a string array,
** checks that the vertices exist. if yes, append an edge to both directions.
**
** @index: pointer to the hash table
** @line: raw line of program input
*/
static int	check_edge(t_index *index, char *line)
{
	char		**arr;
	t_vertex	*src;
	t_vertex	*dst;

	arr = ft_strsplit(line, '-');
	if (ft_arrlen((void **)arr) != 2)
		return (0);
	src = get(index, arr[0]);
	dst = get(index, arr[1]);
	if (!src || !dst)
		return (0);
	edge_append(src, dst);
	edge_append(dst, src);
	link_reverse_edges(src, dst);
	ft_liberator(2, &arr[0], &arr[1]);
	free(arr);
	return (1);
}

/*
** parses raw input for graph edges.
** returns number of edges on success, -1 otherwise.
**
** @input: list of input lines, starting from the point where the edges begin
** @index: pointer to hash table t_index
*/
int	get_edges(t_input *input, t_index *index)
{
	int	edges;

	edges = 0;
	while (input->line != NULL)
	{
		if (input->line[0] != '#')
		{
			if (!check_edge(index, input->line))
				return (-1);
			edges++;
		}
		input = input->next;
	}
	return (edges);
}
