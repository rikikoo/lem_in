/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/11/28 18:30:47 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** adds the @source vertex pointer to the start of @queue and returns an
** otherwise NULL'd array of t_vertex pointers of the size @size
*/
t_vertex	**wipe_queue(
			t_vertex **queue,
			t_vertex *source,
			const int size,
			const int iter
			)
{
	int	i;

	i = 0;
	while (i < size)
	{
		queue[i] = NULL;
		i++;
	}
	queue[0] = source;
	queue[0]->visited = iter;
	return (queue);
}

/*
** "removes" first item from @queue (by incrementing the pointer) and returns it
*/
t_vertex	*pop_first(t_vertex ***queue)
{
	t_vertex	*popped;

	if (!(*queue)[0])
		return (NULL);
	popped = (*queue)[0];
	(*queue)++;
	return (popped);
}

/*
** if not already in @queue, places @vertex to @pos.
** if @pos < 0 or @pos > number of queued items, appends to the end of @queue.
*/
void	enqueue(t_vertex **queue, t_vertex *vertex, int pos)
{
	int			i;
	t_vertex	*tmp;
	t_vertex	*tmp2;

	i = 0;
	while (queue[i] != NULL)
	{
		if (queue[i] == vertex)
			return ;
		i++;
	}
	tmp = queue[i];
	queue[i] = vertex;
	if (pos >= 0 && pos < i)
	{
		i = pos;
		while (queue[++i] != NULL)
		{
			tmp2 = queue[i];
			queue[i] = tmp;
			tmp = tmp2;
		}
		queue[i] = tmp;
	}
}

/*
** prepends @edge to the front of @path
*/
void	search_edge_prepend(t_edge **search_edges, t_edge *edge)
{
	t_edge	*tmp;

	if (edge)
	{
		tmp = *search_edges;
		*search_edges = edge;
		(*search_edges)->next_on_path = tmp;
	}
}
