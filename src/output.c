/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/10 18:37:11 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*ant_move(char *ant, char *vertex)
{
	char	*move;
	int		ant_len;
	int		vertex_len;
	int		i;

	ant_len = ft_strlen(ant);
	vertex_len = ft_strlen(vertex);
	move = (char *)malloc(sizeof(char) * (ant_len + vertex_len + 3));
	if (!move)
		return (NULL);
	i = 0;
	move[i] = 'L';
	while (++i < (ant_len + 1))
		move[i] = ant[i - 1];
	move[i] = '-';
	while (++i < (ant_len + vertex_len + 2))
		move[i] = vertex[i - (ant_len + 2)];
	move[i] = '\0';
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
		while (++move < route->len)
			out[ant - 1][move - 1] = ant_move(ft_itoa(ant), route->path[move]);
		if (route->i % lem->max_flow)
			route = route->next;
		else
			route = head;
		ant++;
		move = 0;
	}
	return (out);
}

static char	***prepare_output_arr(t_route *route, t_lem *lem)
{
	char	***out;
	t_route	*longest;
	int		i;
	int		j;

	out = (char ***)malloc(sizeof(char **) * lem->ants);
	if (!out)
		return (NULL);
	longest = route;
	while (longest->next->is_valid)
		longest = longest->next;
	i = 0;
	while (i < lem->ants)
	{
		j = -1;
		out[i] = (char **)malloc(sizeof(char *) * longest->len);
		if (!out[i])
			return (NULL);
		while (++j < (longest->len - 1))
			out[i][j] = NULL;
		i++;
	}
	return (out);
}

int	print_moves(t_route *route, t_lem *lem)
{
	char	***out;
	int		ant;
	int		turn;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	if (!out)
		return (-1);
	ant = 1;
	turn = 1;
	while (1)
	{
		while (ant <= (lem->max_flow * turn) && ant <= lem->ants)
		{
			if (*(out[ant - 1]) != NULL)
			{
				if ((ant % lem->max_flow) > 0)
					ft_printf("%s ", *(out[ant - 1]));
				else
					ft_printf("%s\n", *(out[ant - 1]));
			}
			ant++;
		}
		if (turn > 5)
			break ;
		while (--ant >= 0)
			(out[ant - 1])++;
		ant = 1;
		turn++;
	}
	return (0);
}
