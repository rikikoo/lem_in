/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edges.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/06 19:30:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** appends new edge to the list of edges coming out of a vertex
**
** vertex: pointer to t_vertex where the edge starts
** src: name/id of the edge's source
** dst: name/id of the edge's sink
*/
static void	edge_append(t_vertex *src, t_vertex *dst)
{
	if (!src || !dst)
		return ;
	if (src->edge != NULL)
	{
		while (src->edge->next != NULL)
		{
			src->edge = src->edge->next;
		}
		src->edge->next = new_edge(src, dst);
	}
	else
		src->edge = new_edge(src, dst);
}

/*
** splits input line containing the two vertex ids into a string array,
** checks that the vertices exist. if yes, append an edge to both directions.
**
** index: pointer to hash table t_index
** line: raw line of program input
*/
static int	check_edge(t_index *index, char *line)
{
	char		**arr;
	t_vertex	*src;
	t_vertex	*dst;

	arr = ft_strsplit(line, '-');
	if (!arr || !arr[0] || !arr[1])
		return (0);
	src = get(index, arr[0]);
	dst = get(index, arr[1]);
	if (!src || !dst)
		return (0);
	edge_append(src, dst);
	edge_append(dst, src);
	ft_liberator(3, arr[0], arr[1], arr[2]);
	free(arr);
	return (1);
}

/*
** parses raw input for graph edges.
** returns number of edges on success, -1 otherwise.
**
** input: list of input lines, starting from the point where the edges begin
** index: pointer to hash table t_index
*/
int	get_edges(t_input *input, t_index *index)
{
	int			i;

	i = 0;
	while (input->line != NULL)
	{
		if (input->line[0] != '#')
		{
			if (!check_edge(index, input->line))
				return (-1);
			i++;
		}
		input = input->next;
	}
	return (i);
}
