/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/23 22:20:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** removes first item in queue and returns it
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
static void	append(char ***arr, char *vertex)
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
** bfs performs a "standard" breadth-first search and returns a path from
** source to sink, or NULL if sink could not be reached.
*/
static char	**bfs(t_index *index, t_lem *lem, char **queue, char **prev)
{
	t_vertex	*curr;
	t_edge		*edges;

	append(&queue, lem->source);
	while (!(*queue == NULL))
	{
		curr = get(index, pop_first(&queue));
		if (curr == NULL)
			break ;
		if (ft_strequ(lem->sink, curr->id))
			append(&prev, lem->sink);
		edges = curr->edge;
		while (edges != NULL)
		{
			curr = get(index, edges->to);
			if (!curr->visited)
			{
				curr->visited = 1;
				append(&queue, edges->to);
				append(&prev, edges->src);
			}
			edges = edges->next;
		}
	}
	return (prev);
}

int	edm_karp(t_index *index, t_lem *lem)
{
	char		**queue;
	char		**prev;

	queue = init_array(lem->vertices + 1);
	prev = init_array(lem->vertices);
	if (!queue || !prev)
		return (-1);
	prev = bfs(index, lem, queue, prev);

	for (int i = 0; prev[i] != NULL; i++) {
		ft_printf("%s\n", prev[i]);
	}

	return (0);
}
