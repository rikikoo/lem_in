/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2021/08/21 20:03:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints all paths if program got "--paths" as an argument
**
** if there wasn't a 25 line restriction, both paths would be freed here
*/
static void	print_paths(t_route *olap, t_route *disj, t_vertex *s, t_vertex *t)
{
	ft_printf("**** Reversed, likely overlapping paths: ****\n\n");
	while (olap->is_valid)
	{
		ft_printf("Path length: %i\n", olap->len);
		while (olap->path->src != s)
		{
			ft_printf("%s <- ", olap->path->to->id);
			olap->path = olap->path->prev_in_path;
		}
		ft_printf("%s <- %s\n\n", olap->path->to->id, olap->path->src->id);
		olap = olap->next;
	}
	ft_printf("**** Disjoint paths: ****\n\n");
	while (disj->is_valid)
	{
		ft_printf("Path length: %i\n", disj->len);
		while (disj->path->src != t)
		{
			ft_printf("%s -> ", disj->path->to->id);
			disj->path = disj->path->prev_in_path;
		}
		ft_printf("%s -> %s\n\n", disj->path->to->id, disj->path->src->id);
		disj = disj->next;
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
**	3. saturate graph by doing repeated searches forward, updating flow after
**		each run
**	4. find disjoint, non-overlapping paths by doing a reverse BFS on the graph
**	5. calculate how many paths are needed and prepare output strings
**	6. print ant movements
*/
int	main(int argc, char **argv)
{
	t_lem		lem;
	t_hashtab	*ht;
	t_input		*input;
	t_route		*olap;
	t_route		*disj;

	lem = init_lem();
	ht = init_ht();
	input = read_input();
	olap = NULL;
	lem.error = parse_input(input, ht, &lem);
	if (lem.error)
		return (die(&input, &ht, &lem, &olap));
	olap = sort_paths(find_paths(&lem, lem.source, lem.sink));
	if (lem.error)
		return (die(&input, &ht, &lem, &olap));
	disj = sort_paths(find_paths(&lem, lem.sink, lem.source));
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(olap, disj, lem.source, lem.sink);
	else
		print_output(sort_ants(olap, disj, &lem), lem, input);
	free_input(&input);
	free_ht(&ht);
	return (0);
}
