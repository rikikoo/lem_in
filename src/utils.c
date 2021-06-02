/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/31 23:00:38 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** adds the source vertex id to the start of the previously malloc'd array
** and returns an otherwise empty array of char pointers.
** functions as a makeshift queue data structure.
*/
char	**wipe_array(char **arr, const int size, const char *source)
{
	int		i;

	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	arr[0] = ft_strdup(source);
	return (arr);
}

/*
** removes first item from queue and returns it (called by bfs)
*/
char	*pop_first(char ***arr)
{
	char	*popped;
	char	**tmp;

	if (!(*arr)[0])
		return (NULL);
	popped = ft_strdup((*arr)[0]);
	tmp = *arr;
	(*arr)++;
	if (*tmp != NULL)
	{
		free((*tmp));
		*tmp = NULL;
	}
	return (popped);
}

/*
** appends a new vertex to the end of the queue/prev list (called by bfs)
*/
void	arr_append(char ***arr, char *vertex)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		if (ft_strequ((*arr)[i], vertex))
			return ;
		i++;
	}
	(*arr)[i] = ft_strdup(vertex);
}

int	is_linked(t_edge *curr, t_vertex *prev_vertex, char *sink)
{
	t_edge	*prev;

	if (prev_vertex == NULL)
		return (0);
	prev = prev_vertex->edge;
	while (prev)
	{
		if ((ft_strequ(prev->to, curr->src) || ft_strequ(prev->to, sink)) && \
		curr->fwd_cap > 0 && prev->fwd_cap > 0)
		{
			return (1);
		}
		prev = prev->next;
	}
	return (0);
}
