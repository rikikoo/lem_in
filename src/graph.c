/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/29 12:54:22 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
		arr[i] = NULL
		i++;
	}
	return (arr);
}

static char	**enqueue(char **queue, int i, t_room *room)
{

}

static char	**bfs(t_link *index, t_lem *lem, char *src, char *target)
{
	char	**queue;
	char	**prev;
	t_room	*curr;
	t_room	*next;
	int		i;

	queue = init_array(lem->rooms);
	prev = init_array(lem->rooms);
	if (!queue || !prev)
		return (-1);
	i = 0;
	queue[i] = ft_strdup(lem->source);
	while (i < lem->rooms)
	{
		curr = get(index, queue[i]);
		curr->visited = 1;
		while (curr->tube != NULL)
		{
			next = get(index, curr->tube->to);
			if (!next->visited)
			{
				queue[i] = ft_strdup(next->id);
			}
			i++;
		}
	}
}

static void	print_links(t_index *index, t_lem *lem)
{
	t_room *room;
	t_link *link;

	ft_printf("Number of ants: %i\n", lem->ants);
	ft_printf("Number of rooms: %i\n", lem->rooms);
	ft_printf("Number of tubes: %i\n\n", lem->tubes);
	for (int i = 0; i < HT_SIZE; i++) {
		if (index->rooms[i] != NULL)
		{
			room = index->rooms[i];
			while (room != NULL)
			{
				if (room->tube != NULL)
				{
					link = room->tube;
					while (link != NULL)
					{
						ft_printf("Found a link! %s -> %s\n", \
						link->src, link->to);
						link = link->next;
					}
				}
				room = room->next;
			}
		}
	}
}

int	edm_karp(t_index *index, t_lem *lem)
{
//	print_links(index, lem);
	return (0);
}
