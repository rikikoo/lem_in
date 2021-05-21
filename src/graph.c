/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/21 12:30:02 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**init_array(int size)
{
	char	**arr;
	int		i;

	arr = (char **)malloc(sizeof(char *) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	return (arr);
}

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
		i++;
	(*arr)[i] = ft_strdup(vertex);
}

static char	**bfs(t_index *index, t_lem *lem, char **prev)
{
	char		**queue;
	t_vertex	*curr;
	t_edge		*edges;

	queue = init_array(lem->vertices);
	if (!queue || !prev)
		return (0);
	append(&queue, lem->source);
	while (!ft_strequ(prev[i], lem->sink))
	{
		curr = get(index, queue[i]);
		curr->visited = 1;
		append(&prev, curr->id);
		edges = curr->edge;
		while (edges != NULL)
		{
			curr = get(index, edges->to);
			if (!curr->visited)
				append(&queue, curr->id);
			edges = edges->next;
		}
	}

}

int	edm_karp(t_index *index, t_lem *lem)
{
	prev = init_array(lem->vertices);
	while (ft_lstlen(prev) < lem->vertices)
		prev = bfs(index, lem, prev);
	return (0);
}
