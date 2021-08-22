/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/22 20:09:38 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints an ant's move if it's possible.
** returns 0 if an ant was moved, 1 otherwise.
**
** @move: one ant's move as a pre-formatted string
** @ant: current ant's index
** @turn_limit: the number of ants possible to move on this turn
** @has_finished: a "boolean" array where the value is True for ants that have
**	reached the sink
*/
static int	print_a_move(char *move, int ant, int *has_finished)
{
	if (!move)
	{
		if (has_finished[ant])
			return (0);
		has_finished[ant] = 1;
		return (1);
	}
	ft_printf("%s", move);
	return (0);
}

/*
** iterates over all paths until all ants have moved to sink
**
** @out: pointer to an array of paths
** @lem: a general runtime info struct
** @mov: int array where each value represents the respective ants' position on
**	its path
** @fin: a "boolean" array where the value is True for ants that have reached
**	the sink
*/
static void	print_moves(char ***out, t_lem lem, int	*mov, int *fin)
{
	int	ant;
	int	turn;
	int	ants_left;
	int	turn_limit;

	turn = 0;
	ants_left = lem.ants;
	while (ants_left)
	{
		ant = -1;
		turn_limit = ++turn * lem.n_paths;
		if (turn_limit > lem.ants)
			turn_limit = lem.ants;
		while (++ant < turn_limit)
		{
			ants_left -= print_a_move(out[ant][mov[ant]], ant, fin);
			if (out[ant][mov[ant]] != NULL)
			{
				mov[ant]++;
				ft_putchar(' ');
			}
		}
		ft_putchar('\n');
	}
}

/*
** outputs the input and then the ants' moves to STDOUT
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @input: pointer to a linked list containing the program input
*/
void	print_output(t_route *route, t_lem lem, t_input *input)
{
	char	***out;
	int		*move_index;
	int		*finished_ants;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	free_route(&route);
	move_index = (int *)ft_zeros(lem.ants);
	finished_ants = (int *)ft_zeros(lem.ants);
	if (!out || !move_index || !finished_ants)
		return ;
	print_input(input);
	print_moves(out, lem, move_index, finished_ants);
	free_output(out);
	free(move_index);
	free(finished_ants);
}
