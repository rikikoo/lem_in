/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 19:47:06 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 17:28:35 by rkyttala         ###   ########.fr       */
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
		while (route && route->id <= lem->max_flow)
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
	fill_pants(route, route->set, pants, &lem);
	out = prepare_output(route, lem, pants, route->set);
	fill_pants(route, route->set, pants, &lem);
	fill_output_arr(route, lem, out, pants);


	// debug start
	t_route *head;
	head = route;
	ft_printf("ants: %d\tmax flow: %d\tbest set: %d\n", lem.ants, lem.max_flow, route->set);
	for (int i = 0; i < lem.max_flow; i++) {
		ft_printf("%d ", route->ants);
		route = route->next;
	}
	ft_printf("\n\n");
	route = head;

	for (int i = 0; out[i] != NULL; i++) {
		ft_printf("Ant #%d's path:\n", i + 1);
		for (int j = 0; out[i][j] != NULL; j++) {
			ft_printf("%s ", out[i][j]);
		}
		ft_putstr("\n\n");
	}
	exit(0);
	// debug end


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
