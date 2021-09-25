/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/25 20:57:13 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints an ant's move if it's possible.
** returns 1 if an ant reached the sink, 0 otherwise.
**
** @path_of_ant: one ant's path as an array of strings
** @ant: current ant's index
** @moves: array of ints representing the current move's index of each ant
** @limit: the ant's index which is the last to be printed on this turn
*/
static int	move_ant(char **path_of_ant, int ant, int *moves, int limit)
{
	char	*move;

	move = path_of_ant[moves[ant]];
	if (!move)
		return (0);
	ft_putstr(move);
	if (ant < limit - 1)
		ft_putchar(' ');
	if (path_of_ant[moves[ant] + 1] == NULL)
	{
		return (1);
	}
	return (0);
}

/*
** moves each ant that can move and returns the amount of ants that reached the
** sink on this turn
**
** @out: pointer to an array of paths for each ant as strings
** @limit: the number of ants to move on this turn
** @moves: int array where each value represents the respective ants' position
**	on its path
*/
static int	ant_dispenser(char ***out, int limit, int *moves)
{
	int	ant;
	int	ret;

	ant = 0;
	ret = 0;
	while (ant < limit)
	{
		ret += move_ant(out[ant], ant, moves, limit);
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
	int	tmp_limit;
	int	i;

	limit = turn * lem->max_flow;
	if (limit > lem->ants)
		limit = lem->ants;
	i = 0;
	tmp_limit = limit;
	while (i < tmp_limit)
	{
		if (!pants[i % lem->max_flow])
			limit--;
		else
			pants[i % lem->max_flow]--;
		i++;
	}
	return (limit);
}

static void	print_moves(char ***out, t_lem *lem, int *pants)
{
	int	*moves;
	int	ants_left;
	int	turn;
	int	turn_limit;

	moves = (int *)ft_zeros(lem->ants);
	ants_left = lem->ants;
	turn = 0;
	if (lem->error || !out || !moves)
	{
		lem->error = -5;
		ants_left = 0;
	}
	while (ants_left)
	{
		turn++;
		turn_limit = set_limit(lem, turn, pants);
		ants_left -= ant_dispenser(out, turn_limit, moves);
		if (turn == 30)
			break ;
	}
	if (moves)
		free(moves);
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

	pants = (int *)ft_zeros(lem.max_flow);
	if (!pants || lem.error)
		return (-5);
	fill_pants(route, lem, pants);
	out = prepare_output_arr(route, lem, pants);
	fill_pants(route, lem, pants);
	fill_output_arr(route, lem, out, pants);

	// debug start
	for (int i = 0; out[i] != NULL; i++) {
		ft_printf("Ant #%d's path:\n", i + 1);
		for (int j = 0; out[i][j] != NULL; j++) {
			ft_printf("%s ", out[i][j]);
		}
		ft_putstr("\n\n");
	}
	// debug end

	if (!out)
		lem.error = -5;
	if (lem.error)	// change to !lem.error when not debugging
		print_input(input);
	fill_pants(route, lem, pants);

	// debug start
	ft_printf("max flow: %d\n\n", lem.max_flow);
	for (int i = 0; i < lem.max_flow; i++) {
		ft_printf("%d ", pants[i]);
	}
	ft_printf("\n\n");
//	exit(0);
	// debug end

	print_moves(out, &lem, pants);
	free_output(out);
	free_compmat(&lem);
	free(pants);
	return (lem.error);
}
