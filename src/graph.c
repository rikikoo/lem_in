/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/02 18:38:14 by rkyttala         ###   ########.fr       */
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

static char	**bfs(t_index *index, t_lem *lem, char **prev)
{
	char	**queue;
	t_room	*curr;
	t_link	*tubes;
	int		i;
	int		j;

	queue = init_array(lem->rooms);
	if (!queue || !prev)
		return (0);
	i = 0;
	queue[i] = ft_strdup(lem->source);
	while (i < lem->rooms)
	{
		j = i + 1;
		curr = get(index, queue[i]);
		curr->visited = 1;
		prev[i] = ft_strdup(curr->id);
		tubes = curr->tube;
		while (tubes != NULL)
		{
			curr = get(index, tubes->to);
			if (!curr->visited)
				queue[i + j] = ft_strdup(curr->id);
			tubes = tubes->next;
			j++;
		}
		i = j;
	}
	i = 0;
	while (queue[i] != NULL)
	{
		free(queue[i]);
		i++;
	}
	free(queue);
	free(curr);
	return (prev);
}

int	edm_karp(t_index *index, t_lem *lem)
{
	prev = init_array(lem->rooms);
	while (ft_lstlen(prev) < lem->rooms)
		prev = bfs(index, lem, prev);
	return (0);
}
