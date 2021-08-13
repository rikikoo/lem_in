/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/13 15:07:12 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** adds the source vertex pointer to the start of the previously malloc'd array
** and returns an otherwise NULL'd array of t_vertex pointers
*/
t_vertex	**wipe_queue(t_vertex **queue, t_vertex *source, const int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		queue[i] = NULL;
		i++;
	}
	queue[0] = source;
	queue[0]->visited = 1;
	return (queue);
}

/*
** removes first item from @queue and returns it
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
** if not already in queue @arr, appends @vertex to the end of it
*/
void	queue_append(t_vertex ***arr, t_vertex *vertex)
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
** sets @edge to the front of @path
*/
void	path_prepend(t_edge **path, t_edge *edge)
{
	t_edge	*tmp;

	tmp = *path;
	*path = edge;
	(*path)->prev_in_path = tmp;
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
