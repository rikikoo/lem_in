/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/20 16:39:54 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints an ant's move if it's possible.
** returns 1 if an ant was moved, 0 otherwise.
**
** @move: one ant's move as a pre-formatted string
** @ant: current ant's index
** @turn_limit: current turn's nbr
*/
static int	print_a_move(char *move, int ant, int turn_limit)
{
	if (!move)
		return (0);
	ant++;
	if (ant % turn_limit > 0 && ant < turn_limit)
		ft_printf("%s ", move);
	else
		ft_printf("%s\n", move);
	return (1);
}

/*
** iterates over all paths until all ants have moved to sink
**
** @out: pointer to an array of paths
** @lem: a general runtime info struct
** @m_idx: an int array, where each value represents each ants' position on its
**	respective path
*/
static void	print_moves(char ***out, t_lem lem, int	*m_idx)
{
	int	ant;
	int	turn;
	int	ants_moved;
	int	turn_limit;

	ant = -1;
	turn = 1;
	ants_moved = 0;
	while (lem.ants)
	{
		turn_limit = turn * lem.n_paths;
		if (turn_limit > lem.ants)
			turn_limit = lem.ants;
		while (++ant < turn_limit)
		{
			ants_moved += print_a_move(out[ant][m_idx[ant]], ant, turn_limit);
			if (out[ant][m_idx[ant]] != NULL)
				m_idx[ant]++;
		}
		lem.ants -= (turn_limit - ants_moved);
		ant = -1;
		ants_moved = 0;
		turn++;
	}
}

/*
** outputs the input and then the ants' moves to STDOUT until no moves are left
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @input: pointer to a linked list containing the program input
*/
void	print_output(t_route *route, t_lem lem, t_input *input)
{
	char	***out;
	int		*move_index;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	free_route(&route);
	move_index = (int *)ft_zeros(lem.ants);
	if (!out || !move_index)
		return ;
	print_input(input);
	print_moves(out, lem, move_index);
	free_output(out);
	free(move_index);
}
