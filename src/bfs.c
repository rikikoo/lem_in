/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:32:03 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/28 14:36:19 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** removes first item from queue and returns it
*/
static char	*pop_first(char ***arr)
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
** appends a new vertex to the end of the queue/prev list
*/
static void	arr_append(char ***arr, char *vertex)
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
** bfs performs a breadth-first search and returns the found path
*/
char	**bfs(t_index *index, t_lem *lem, char **queue, t_route *route)
{
	t_vertex	*vertex;
	t_edge		*edge;
	char		**path;

	path = route->path;
	arr_append(&queue, lem->source);
	while (!(*queue == NULL))
	{
		vertex = get(index, pop_first(&queue));
		if (vertex == NULL)
			break ;
		edge = vertex->edge;
		while (edge != NULL)
		{
			vertex  = get(index, edge->to);
			if (!ft_strequ(edge->to, lem->source) && \
			vertex->visited < route->i && edge->fwd_cap > 0)
			{
				vertex->visited += 1;
				arr_append(&queue, edge->to);
				arr_append(&path, edge->src);
				if (ft_strequ(lem->sink, edge->to))
				{
					arr_append(&path, lem->sink);
					return (route->path);
				}
			}
			edge = edge->next;
		}
	}
	return (route->path);
}
