/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/14 00:01:05 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_paths(t_route *olap, t_route *dist, t_vertex *s, t_vertex *t)
{
	ft_printf("reversed, possibly overlapping paths:\n\n");
	while (olap->is_valid)
	{
		ft_printf("Route length: %i\n", olap->len);
		while (olap->path->src != s)
		{
			ft_printf("%s <- ", olap->path->to->id);
			olap->path = olap->path->prev_in_path;
		}
		ft_printf("%s <- %s\n\n", olap->path->to->id, olap->path->src->id);
		olap = olap->next;
	}

	ft_printf("distinct paths:\n\n");
	while (dist->is_valid) {
		ft_printf("Route length: %i\n", dist->len);
		while (dist->path->src != t)
		{
			ft_printf("%s -> ", dist->path->to->id);
			dist->path = dist->path->prev_in_path;
		}
		ft_printf("%s -> %s\n\n", dist->path->to->id, dist->path->src->id);
		dist = dist->next;
	}
}

/*
** lem_in is a program that finds all paths in an undirected graph for n ants
** to go through and prints out the moves the ants will take from source to sink
** with the least amount of moves.
** The number of ants, vertex names and coordinates and their edges are given
** as input in a specific format (see README).
** lem_in will exit and return an error if the format of the instructions is
** invalid or there isn't a connection between the source and the sink.
**
**	1. read instructions from STDIN
**	2. validate and store relevant information into appropriate structs
**	3. construct graph and find all paths
**	4. sort paths
**	5. distribute ants to paths and prepare output strings
**	6. print moves per turn
*/
int	main(int argc, char **argv)
{
	t_lem	lem;
	t_input	*input;
	t_index	*index;
	t_route	*overlap;
	t_route	*distinct;

	lem = init_lem();
	input = read_input();
	index = init_index();
	lem.error = parse_input(input, index, &lem);
	if (lem.error)
		return (die(&input, &index, &lem, NULL));
	overlap = find_paths(&lem, get(index, lem.source), get(index, lem.sink));
	if (lem.error)
		return (die(&input, &index, &lem, &overlap));
	overlap = sort_paths(overlap);
	distinct = find_paths(&lem, get(index, lem.sink), get(index, lem.source));
	if (!lem.error)
		distinct = sort_paths(distinct);
//	print_input(input);
//	print_moves(overlap, distinct, &lem);
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(overlap, distinct, get(index, lem.source),
		get(index, lem.sink));
	return (0);
}
