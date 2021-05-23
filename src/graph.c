/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/23 13:34:05 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*pop_first(char ***arr)
{
	char	*popped;
	char	***tmp;

	popped = ft_strdup((*arr)[0]);
	tmp = arr;
	(*arr)++;
	free((*tmp)[0]);
	return (popped);
}

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

static char	**bfs(t_index *index, t_lem *lem, char **queue, char **prev)
{
	t_vertex	*curr;
	t_edge		*edges;

	append(&queue, lem->source);
	while (!(queue[0] == NULL))
	{
		curr = get(index, pop_first(&queue));
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

	queue = init_array(lem->vertices);
	prev = init_array(lem->vertices);
	if (!queue || !prev)
		return (-1);
	prev = bfs(index, lem, queue, prev);

	for (int i = 0; prev[i] != NULL; i++) {
		ft_printf("%s\n", prev[i]);
	}

	return (0);
}
