/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/14 00:52:35 by rkyttala         ###   ########.fr       */
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
**	2. validate and store graph information
**	3. saturate graph by doing repeated searches forward
**	4. find distinct, non-overlapping paths by doing a reverse BFS on the graph
**	5. distribute ants to paths and prepare output strings
**	6. print moves per turn
*/
int	main(int argc, char **argv)
{
	t_lem		lem;
	t_hashtab	*ht;
	t_input		*input;
	t_route		*olap;
	t_route		*dist;

	lem = init_lem();
	ht = init_ht();
	input = read_input();
	lem.error = parse_input(input, ht, &lem);
	if (lem.error)
		return (die(&input, &ht, &lem, NULL));
	olap = sort_paths(find_paths(&lem, get(ht, lem.source), get(ht, lem.sink)));
	if (lem.error)
		return (die(&input, &ht, &lem, &olap));
	dist = sort_paths(find_paths(&lem, get(ht, lem.sink), get(ht, lem.source)));
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(olap, dist, get(ht, lem.source), get(ht, lem.sink));
	else
	{
//		print_input(input);
//		print_moves(overlap, distinct, &lem);
	}
	return (0);
}
