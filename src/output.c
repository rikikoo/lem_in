/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/17 23:11:17 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints an ant's move if it's possible.
** returns -1 if there are moves left but rooms are occupied,
** returns 1 if an ant was moved,
** returns 0 when there are no moves left.
**
** @move: one ant's move as a pre-formatted string
** @lem: pointer to a general runtime info struct
** @ant: current ant's nbr
** @turn: current turn's nbr
*/
static int	print_a_move(char *move, t_lem lem, int ant, int turn)
{
	int	turn_limit;

	if (!move)
		return (0);
	if ((turn * lem.n_paths) < lem.ants)
		turn_limit = turn * lem.n_paths;
	else
		turn_limit = lem.ants;
	if ((ant % turn_limit) > 0 && ant < turn_limit)
		ft_printf("%s ", move);
	else if ((ant % turn_limit) == 0)
		ft_printf("%s\n", move);
	if ((ant % turn_limit) == 0 && ant < lem.ants)
		return (-1);
	else
		return (1);
}

static char	**print_output(char ***out, t_lem lem)
{
	int		ant;
	int		moves_left;
	int		turn;
	char	**head;

	moves_left = 1;
	turn = 0;
	head = *out;
	while (moves_left)
	{
		ant = -1;
		turn++;
		while (++ant < lem.ants)
		{
			moves_left = print_a_move(*out[ant], lem, ant + 1, turn);
			if (moves_left == -1)
				break ;
		}
		while (--ant >= 0)
			out[ant] = out[ant] + (*out[ant] != NULL);
	}
	return (head);
}

/*
** outputs the ants' moves to STDOUT until no moves are left
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
*/
void	print_moves(t_route *route, t_lem lem, t_input *input)
{
	char	***out;

	out = fill_output_arr(route, lem, prepare_output_arr(route, lem));
	if (!out)
		return ;
	print_input(input);
	*out = print_output(out, lem);
//	free_output(&out);
}
