/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:04:25 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/14 23:32:14 by rkyttala         ###   ########.fr       */
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

/*
** returns true if current edge source is the same as previous vertex outgoing
** edge's sink, i.e. if they are linked. returns false otherwise.
*/
int	is_linked(t_edge *curr, t_vertex *prev_vertex, const char *sink)
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
