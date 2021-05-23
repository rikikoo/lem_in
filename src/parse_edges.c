/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_edges.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/23 19:49:47 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to t_edge
**
** src: name/id of the edge's source
** dst: name/id of the edge's sink
*/
static t_edge	*new_edge(char *src, char *dst)
{
	t_edge	*edge;

	if (!src || !dst)
		return (NULL);
	edge = (t_edge *)malloc(sizeof(t_edge));
	if (!edge)
		return (NULL);
	edge->src = ft_strdup(src);
	edge->to = ft_strdup(dst);
	edge->cap = 2;
	edge->next = NULL;
	return (edge);
}

/*
** appends new edge to the list of edges coming out of a vertex
**
** room: pointer to t_vertex where the edge starts
** src: name/id of the edge's source
** dst: name/id of the edge's sink
*/
static void	append_edge(t_vertex *vertex, char *src, char *dst)
{
	if (!vertex || !src || !dst)
		return ;
	if (vertex->edge != NULL)
	{
		while (vertex->edge->next != NULL)
		{
			vertex->edge = vertex->edge->next;
		}
		vertex->edge->next = new_edge(src, dst);
	}
	else
		vertex->edge = new_edge(src, dst);
}

/*
** splits input line containing the two vertex ids into a string array,
** checks that the vertices exist and returns the array
**
** index: pointer to hash table t_index
** line: raw line of program input
*/
static char	**check_edge(t_index *index, char *line)
{
	char		**arr;
	t_vertex	*src;
	t_vertex	*dst;

	arr = ft_strsplit(line, '-');
	if (!arr[0] || !arr[1])
		return (NULL);
	src = get(index, arr[0]);
	dst = get(index, arr[1]);
	if (!src || !dst)
		return (NULL);
	return (arr);
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
	char		**arr;
	t_vertex	*src;
	int			i;

	i = 0;
	while (input->line != NULL)
	{
		arr = check_edge(index, input->line);
		if (arr == NULL)
			return (-1);
		src = get(index, arr[0]);
		append_edge(src, arr[0], arr[1]);
		i += 1;
		input = input->next;
	}
	ft_liberator(3, &arr[0], &arr[1], &arr[2]);
	free(arr);
	if (src->edge == NULL)
		return (-1);
	return (i);
}
