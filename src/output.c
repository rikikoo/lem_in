/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/28 21:40:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints a move of an ant that hasn't reached the sink for ants up to @limit.
** returns the amount of ants moved.
**
** @out: pointer to an array of paths for each ant as strings
** @limit: the number of ants to move on this turn
** @moves: int array where each value represents the respective ants' position
**	on its path
** @total_ants: total amount of ants
*/
static int	ant_dispenser(char ***out, int limit, int *moves, int total_ants)
{
	int		ant;
	int		ret;
	char	*move;

	ant = 0;
	ret = 0;
	if (!limit)
		limit = total_ants;
	while (ant < limit)
	{
		move = out[ant][moves[ant]];
		if (move)
		{
			ret++;
			ft_putstr(move);
			if (ant < limit - 1)
				ft_putchar(' ');
			moves[ant]++;
		}
		ant++;
	}
	if (ret)
		ft_putchar('\n');
	return (ret);
}

/*
** calculates how many ants can be sent out per turn.
** fills @limits with ant limits per turn until all ants have been dispatched.
**
** @lem: pointer to a general runtime info struct
** @route: pointer to the head of a list of paths
** @turn: ant int representing the turn number
** @limits: a zero-initialized int array for the turn limits
*/
static void	set_limits(t_lem *lem, t_route *route, int turn, int *limits)
{
	t_route	*head;
	int		ants;
	int		ants_most;

	head = route;
	ants = 0;
	ants_most = head->ants;
	while (turn < ants_most)
	{
		while (route && route->set == lem->best_set)
		{
			if (route->ants)
			{
				route->ants--;
				ants++;
			}
			route = route->next;
		}
		limits[turn] = ants;
		if (limits[turn] > lem->ants)
			limits[turn] = lem->ants;
		turn++;
		route = head;
	}
}

/*
** sets the turns limits and calls ant_dispenser() until no ants couldn't be
** moved, i.e. until all ants have reached the sink
**
** @out: pointer to an array of ants' paths as strings
** @lem: pointer to a general runtime info struct
** @route: pointer to the head of a list of paths
** @moves: int array where each value represents the respective ants' position
**	on its path
*/
static int	print_moves(char ***out, t_lem *lem, t_route *route, int *moves)
{
	int	ants_left;
	int	turn;
	int	*turn_limits;

	if (lem->error || !out || !moves)
		return (-5);
	ants_left = lem->ants;
	turn = 0;
	turn_limits = (int *)ft_zeros(lem->turns);
	if (!turn_limits)
		return (-5);
	if (lem->turns <= 1)
		turn_limits[0] = 0;
	else
		set_limits(lem, route, turn, turn_limits);
	while (ants_left)
	{
		ants_left = ant_dispenser(out, turn_limits[turn], moves, lem->ants);
		turn++;
	}
	free(turn_limits);
	return (0);
}

/*
** copies the ants per path to @pants in order to preserve the original info.
*/
static void	fill_pants(t_route *route, int *pants, t_lem *lem)
{
	int	paths;

	if (!pants)
		return ;
	paths = 0;
	while (route && route->is_valid && route->set == lem->best_set)
	{
		paths++;
		pants[route->id - 1] = route->ants;
		route = route->next;
	}
	lem->max_flow = paths;
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
	int		*moves;

	if (!route || lem.error)
		return (-5);
	pants = (int *)ft_zeros(route->set);
	fill_pants(route, pants, &lem);
	out = prepare_output(route, lem, pants);
	fill_pants(route, pants, &lem);
	fill_output_arr(route, lem, out, pants);
	if (!pants || !out)
		lem.error = -5;
	if (!lem.error)
		print_input(input);
	moves = (int *)ft_zeros(lem.ants);
	if (!moves)
		return (-5);
	lem.error = print_moves(out, &lem, route, moves);
	free_output(out);
	free(pants);
	free(moves);
	return (lem.error);
}
