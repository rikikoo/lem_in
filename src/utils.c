/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/07/06 19:02:23 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	die(t_input **input, t_index **index, t_lem **lem, t_route **route)
{
	if (*input)
		free_input(input);
	if (*index)
		free_index(index);
	if (*lem)
		free_lem(lem);
	if (*route)
		free_route(route);
	ft_printf("\nE       R\n");
	ft_printf("  R   O  \n");
	ft_printf("    R    \n");
	ft_printf("  R   O  \n");
	ft_printf("E       R\n\n");
	return (-1);
}

/*
** adds the source vertex id to the start of the previously malloc'd array
** and returns an otherwise empty array of char pointers.
** functions as a makeshift queue data structure.
*/
char	**wipe_queue(t_vertex **queue, t_vertex *source, const int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	arr[0] = source;
	return (arr);
}

/*
** removes first item from queue and returns it (called by bfs)
*/
t_vertex	*pop_first(t_vertex ***queue)
{
	t_vertex	*popped;
	t_vertex	**tmp;

	if (!(*arr)[0])
		return (NULL);
	popped = (*arr)[0];
	tmp = *arr;
	(*arr)++;
	if (*tmp != NULL)
	{
		free(*tmp);
		*tmp = NULL;
	}
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
		if (prev->to == curr->src || prev->to == sink) && \
		curr->fwd_cap > 0 && prev->fwd_cap > 0)
		{
			return (1);
		}
		prev = prev->next;
	}
	return (0);
}
