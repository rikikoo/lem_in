/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/15 16:50:41 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** basically sprintf for a very specific job.
** returns a formatted string for the output array.
**
** ant: the number of the ant as a string
** vertex: the id of the vertex
*/
static char	*format_move(int ant, char *vertex)
{
	char	*move;
	char	*ant_str;
	int		ant_len;
	int		vertex_len;
	int		i;

	ant_str = ft_itoa(ant);
	ant_len = ft_strlen(ant_str);
	vertex_len = ft_strlen(vertex);
	move = (char *)malloc(sizeof(char) * (ant_len + vertex_len + 3));
	if (!move)
		return (NULL);
	i = 0;
	move[i] = 'L';
	while (++i < (ant_len + 1))
		move[i] = ant_str[i - 1];
	move[i] = '-';
	while (++i < (ant_len + vertex_len + 2))
		move[i] = vertex[i - (ant_len + 2)];
	move[i] = '\0';
	free(ant_str);
	return (move);
}

/*
** copies the found paths which are sorted from shortest to longest into the
** empty output array in order for every ant, so that once the longest path
** has been copied, the next ant's path will be the shortest again, and so on.
** returns a pointer to the filled array.
**
** route: pointer to the head of a list of paths
** lem: pointer to a general runtime info struct
** out: pointer to an array of empty paths, prepared by prepare_output_arr()
*/
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
			out[ant - 1][move - 1] = format_move(ant, route->path[move]);
		if (ant % lem->max_flow > 0)
			route = route->next;
		else
			route = head;
		ant++;
		move = 0;
	}
	return (out);
}

/*
** creates an empty path for each ant. every path is an array of strings
** and their length is as long as the longest found path.
** returns a pointer to the newly allocated array of strings in an array.
**
** route: pointer to the head of a list of paths
** lem: pointer to a general runtime info struct
*/
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
		out[i] = (char **)malloc(sizeof(char *) * longest->len + 1);
		if (!out[i])
			return (NULL);
		while (++j < (longest->len))
			out[i][j] = NULL;
		i++;
	}
	return (out);
}

/*
** prints an ant's move if it's possible.
** returns 2 if there are moves left but rooms are occupied,
** returns 1 if all ants were moved and returns 0 when there are no moves left.
**
** move: one ant's move as a pre-formatted string
** lem: pointer to a general runtime info struct
** ant: current ant's nbr
** turn: current turn's nbr
*/
static int	print_a_move(char *move, t_lem *lem, int ant, int turn)
{
	int	turn_limit;

	if (!move)
		return (0);
	if ((turn * lem->max_flow) < lem->ants)
		turn_limit = turn * lem->max_flow;
	else
		turn_limit = lem->ants;
	if ((ant % turn_limit) > 0 && ant < turn_limit)
		ft_printf("%s ", move);
	else if ((ant % turn_limit) == 0)
		ft_printf("%s\n", move);
	if ((ant % turn_limit) == 0 && ant < lem->ants)
		return (-1);
	else
		return (1);
}

/*
** outputs the ants' moves to STDOUT until no moves are left
**
** route: pointer to the head of a list of paths
** lem: pointer to a general runtime info struct
*/
int	print_moves(t_route *route, t_lem *lem)
{
	char	***out;
	int		ant;
	int		moves_left;
	int		turn;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	if (!out)
		return (-1);
	moves_left = 1;
	turn = 0;
	while (moves_left)
	{
		ant = 0;
		turn++;
		while (ant < lem->ants)
		{
			moves_left = print_a_move(*out[ant], lem, ant + 1, turn);
			ant++;
			if (moves_left == -1)
				break ;
		}
		while (--ant >= 0)
			out[ant] = out[ant] + (*out[ant] != NULL);
	}
	return (0);
}
