/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:28:41 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/28 14:43:55 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_queue(char ***queue, int size)
{
	while (size)
	{
		free((*queue)[size]);
		size--;
	}
	free(*queue);
}

static t_route	*new_route(int vertices, int iteration)
{
	t_route	*route;
	int		i;

	route = (t_route *)malloc(sizeof(t_route));
	route->path = (char **)malloc(sizeof(char *) * (vertices + 1));
	if (!route || !route->path)
		return (NULL);
	i = 0;
	while (i <= vertices)
	{
		route->path[i] = NULL;
		i++;
	}
	route->i = iteration;
	route->next = NULL;
	return (route);
}

static int	send_flow(t_index *index, char **path)
{
	int 		i;
	int			flow;
	t_vertex	*vert;
	t_edge		*edge;

	i = 0;
	flow = 0;
	while (path[i + 1] != NULL)
	{
		vert = get(index, path[i]);
		edge = vert->edge;
		while (edge != NULL)
		{
			if (ft_strequ(edge->src, path[i]) && \
			ft_strequ(edge->to, path[i + 1]))
			{
				edge->fwd_cap -= 1;
				edge->rev_cap -= 1;
				break ;
			}
			edge = edge->next;
		}
		i++;
	}
	return (1);
}

static int	path_found(char *sink, char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strequ(path[i], sink))
			return (1);
		i++;
	}
	return (0);
}

int	edm_karp(t_index *index, t_lem *lem)
{
	char	**queue;
	t_route	*route;
	t_route	*head;
	int		i;

	queue = (char **)malloc(sizeof(char *) * (lem->vertices + 1));
	queue[lem->vertices] = NULL;
	i = 1;
	route = new_route(lem->vertices, i);
	head = route;
	if (!queue || !route)
		return (-1);
	while (1)
	{
		queue = wipe_array(queue, lem->vertices);
		route->path = bfs(index, lem, queue, route);
		if (!path_found(lem->sink, route->path))
			break ;
		lem->max_flow += send_flow(index, route->path);
		route->next = new_route(lem->vertices, ++i);
		route = route->next;
	}

	ft_printf("there should be %d routes...\n", lem->max_flow);
	while (head->next != NULL)
	{
		ft_printf("\n");
		for (i = 0; head->path[i] != NULL; i++)
		{
			ft_printf("%s\n", head->path[i]);
		}
		head = head->next;
	}
	free_queue(&queue, lem->vertices);
	return (0);
}
