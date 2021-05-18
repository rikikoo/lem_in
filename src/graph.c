/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/18 18:54:22 by rkyttala         ###   ########.fr       */
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

static void	append(char ***arr, char *room)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
		i++;
	(*arr)[i] = ft_strdup(room);
}

static char	**bfs(t_index *index, t_lem *lem, char **prev)
{
	char	**queue;
	t_room	*curr;
	t_link	*tubes;

	queue = init_array(lem->rooms);
	if (!queue || !prev)
		return (0);
	append(&queue, lem->source);
	while (!ft_strequ(prev[i], lem->target))
	{
		curr = get(index, queue[i]);
		curr->visited = 1;
		append(&prev, curr->id);
		tubes = curr->tube;
		while (tubes != NULL)
		{
			curr = get(index, tubes->to);
			if (!curr->visited)
				append(&queue, curr->id);
			tubes = tubes->next;
		}
	}

}

int	edm_karp(t_index *index, t_lem *lem)
{
	prev = init_array(lem->rooms);
	while (ft_lstlen(prev) < lem->rooms)
		prev = bfs(index, lem, prev);
	return (0);
}
