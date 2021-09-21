/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/21 22:55:33 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints an ant's move if it's possible.
** returns 1 if an ant reached the sink, 0 otherwise.
**
** @move: one ant's move as a pre-formatted string
** @ant: current ant's index
** @finished: a "boolean" array where the value is True for ants that have
**	reached the sink
** @last_ant: the ant's index which is the last to be printed on this turn
*/
static int	move_ant(char *move, int ant, int *finished, int last_ant)
{
	if (!move)
	{
		if (finished[ant])
			return (0);
		finished[ant] = 1;
		return (1);
	}
	ft_putstr(move);
	if (ant < last_ant - 1)
		ft_putchar(' ');
	return (0);
}

/*
** moves each ant that can move and returns the amount of ants that reached the
** sink on this turn
**
** @out: pointer to an array of paths that ants travel as strings
** @limit: the number of ants to move on this turn
** @moves: int array where each value represents the respective ants' position
**	on its path
** @finish: a "boolean" array where the value is True for ants that have reached
**	the sink
*/
static int	ant_dispenser(char ***out, int limit, int *moves, int *finished)
{
	int	ant;
	int	ret;

	ant = 0;
	ret = 0;
	while (ant < limit)
	{
		ret += move_ant(out[ant][moves[ant]], ant, finished, limit);
		if (out[ant][moves[ant]] != NULL)
			moves[ant]++;
		ant++;
	}
	ft_putchar('\n');
	return (ret);
}

/*
** set_limit checks if a path has already sent out all ants using it, and lowers
** the turn limit accordingly
*/
static int	set_limit(t_lem *lem, int turn, int *pants)
{
	int	limit;
	int	i;

	limit = turn * lem->last_index;
	if (limit > lem->ants)
		limit = lem->ants;
	i = 0;
	while (i < lem->last_index)
	{
		if (pants[i] == 0)
			limit--;
		else if (pants[i] > 0)
			pants[i]--;
		i++;
	}
	return (limit);
}

static void	print_moves(char ***out, t_lem *lem, int *pants)
{
	int	*moves;
	int	*finished;
	int	ants_left;
	int	turn;
	int	turn_limit;

	moves = (int *)ft_zeros(lem->ants);
	finished = (int *)ft_zeros(lem->ants);
	ants_left = lem->ants;
	turn = 0;
	if (lem->error || !out || !moves || !finished)
	{
		lem->error = -5;
		ants_left = 0;
	}
	while (ants_left)
	{
		turn++;
		turn_limit = set_limit(lem, turn, pants);
		ants_left -= ant_dispenser(out, turn_limit, moves, finished);
	}
	if (moves)
		free(moves);
	if (finished)
		free(finished);
}

/*
** outputs the input and then the ants' moves to STDOUT
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @input: pointer to a linked list containing the program input
*/
int	print_output(t_route *route, t_lem lem, t_input *input)
{
	char	***out;
	int		*pants;

	pants = (int *)ft_zeros(lem.last_index);
	if (!pants)
		return (-5);
	fill_pants(route, lem, pants);
	out = prepare_output_arr(route, lem, pants);
	fill_pants(route, lem, pants);
	fill_output_arr(route, lem, out, pants);
	if (!out)
		lem.error = -5;
	if (!lem.error)
		print_input(input);
	fill_pants(route, lem, pants);

	for (int i = 0; i < lem.last_index; i++) {
		ft_printf("%d ", pants[i]);
	}
	ft_printf("\n");
	exit(0);

	print_moves(out, &lem, pants);
	free_output(out);
	free(pants);
	return (lem.error);
}
