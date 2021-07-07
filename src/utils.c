/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/07 15:11:54 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** adds the source vertex id to the start of the previously malloc'd array
** and returns an otherwise empty array of char pointers.
** functions as a makeshift queue data structure.
*/
t_vertex	**wipe_queue(t_vertex **queue, t_vertex *source, const int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		queue[i] = NULL;
		i++;
	}
	queue[0] = source;
	return (queue);
}

/*
** removes first item from queue and returns it (called by bfs)
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
** appends a new vertex to the end of the queue/prev list (called by bfs)
*/
void	arr_append(t_vertex ***arr, t_vertex *vertex)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		if ((*arr)[i] == vertex)
			return ;
		i++;
	}
	(*arr)[i] = vertex;
}

/*
** returns true if the current edge's source is the same as the previous
** edge's sink, i.e. if they are linked. returns false otherwise.
*/
int	is_linked(t_edge *curr, t_vertex *prev_vertex, t_vertex *sink)
{
	t_edge	*prev;

	if (prev_vertex == NULL)
		return (0);
	prev = prev_vertex->edge;
	while (prev)
	{
		if ((prev->to == curr->src || prev->to == sink) && \
		curr->fwd_cap > 0 && prev->fwd_cap > 0)
		{
			return (1);
		}
		prev = prev->next;
	}
	return (0);
}

void	print_input(t_input *input)
{
	while (input->next)
	{
		ft_printf("%s\n", input->line);
		input = input->next;
	}
	ft_putchar('\n');
}
