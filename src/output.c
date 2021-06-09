/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/09 17:29:09 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ant_move(char *ant, char *vertex)
{
	char	*move;
	int		ant_len;
	int		vertex_len;

	ant_len = ft_strlen(ant);
	vertex_len = ft_strlen(vertex);
	move = (char *)malloc(sizeof(char) * (ant_len + vertex_len + 3));
	if (!move)
		return (NULL);
	move[0] = 'L';
	move[ant_len + vertex_len + 3] = '\0';
	move = ft_strcpy(move + 1, ant);
	*(move + ant_len + 1) = '-';
	move = ft_strcpy(move + ant_len + 2, vertex);
	free(ant);
	return (move);
}

static char	***fill_output_arr(t_route *route, t_lem *lem, char ***out)
{
	int		ant_path;
	int		move;
	int		ant;
	t_route	*head;

	if (!route || !lem || !out)
		return (NULL);
	ant_path = 0;
	move = 0;
	ant = 1;
	head = route;
	while (ant <= lem->ants)
	{
		while (move < route->len)
		{
			out[ant - 1][move] = ant_move(ft_itoa(ant), route->path[move]);
			move++;
		}
		if (route->i % lem->max_flow)
			route = route->next;
		else
			route = head;
		ant++;
	}
	return (out);
}

static char	***prepare_output_arr(t_route *route, t_lem *lem)
{
	char	***out;
	t_route	*longest;
	int		i;

	out = (char ***)malloc(sizeof(char **) * lem->ants);
	if (!out)
		return (NULL);
	longest = route;
	while (longest->next->is_valid)
		longest = longest->next;
	i = 0;
	while (i < lem->ants)
	{
		out[i] = (char **)malloc(sizeof(char *) * longest->len + 1);
		if (!out[i])
			return (NULL);
		i++;
	}
	out[i] = NULL;
	return (out);
}

int	print_moves(t_route *route, t_lem *lem)
{
	char	***out;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	if (!out)
		return (-1);
	ft_printf("%s\n", out[0][0]);
	return (0);
}
