/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/13 19:23:21 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** appends a new edge to the list of edges coming out of a vertex
**
** @src: pointer to the edge's source vertex
** @to: pointer to the edge's sink vertex
*/
static int	edge_append(t_vertex *src, t_vertex *to)
{
	t_edge	*edge;

	edge = src->edge;
	if (edge != NULL)
	{
		while (edge->next_adjacent != NULL)
		{
			edge = edge->next_adjacent;
		}
		edge->next_adjacent = new_edge(src, to);
		if (!edge->next_adjacent)
			return (-5);
	}
	else
	{
		src->edge = new_edge(src, to);
		if (!src->edge)
			return (-5);
	}
	return (0);
}

/*
** splits input line containing the two vertex ids into an array of strings and
** checks that those vertices exist. if yes, append an edge to both directions.
**
** @ht: pointer to the vertex hash table
** @line: raw line of program input
*/
static int	check_edge(t_hashtab *ht, char *line)
{
	char		**arr;
	t_vertex	*src;
	t_vertex	*to;
	int			error;
	int			i;

	error = 0;
	arr = ft_strsplit(line, '-');
	if (ft_arrlen((void **)arr) != 2)
		error = -1;
	if (!error)
	{
		src = get(ht, arr[0]);
		to = get(ht, arr[1]);
		if (!src || !to)
			error = -3;
		else if (edge_append(src, to) < 0 || edge_append(to, src) < 0)
			error = -5;
	}
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (error);
}

/*
** parses raw input for graph edges. Skips comment lines (that start with '#').
** returns number of edges on success, -1 otherwise.
**
** @input: list of input lines, starting from the line where edge data begins
** @ht: pointer to the vertex hash table
*/
int	get_edges(t_input *input, t_hashtab *ht)
{
	int	edges;
	int	ret;

	edges = 0;
	while (input->line != NULL)
	{
		if (input->line[0] != '#')
		{
			ret = check_edge(ht, input->line);
			if (ret < 0)
				return (ret);
			edges++;
		}
		input = input->next;
	}
	return (edges);
}
