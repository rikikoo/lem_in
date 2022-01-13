/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/13 18:24:47 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints all paths if program got "--paths" as an argument
**
** TODO:
**	- separate sets with colorful headers
**	- remove route validity check
*/
static void	print_paths(t_route *route, t_lem lem)
{
	if (lem.error)
		return ;
	while (route)
	{
		if (route->is_valid)
		{
			ft_printf("Path %d in set %d length: %i\n", \
			route->id, route->set, route->len);
			while (route->path->edge->to != lem.sink)
			{
				ft_printf("%s -> ", route->path->edge->src->id);
				route->path = route->path->next;
			}
			ft_printf("%s -> %s\n\n", route->path->edge->src->id, \
				route->path->edge->to->id);
		}
		route = route->next;
	}
}

void	print_input(t_input *input)
{
	while (input->next)
	{
		ft_putendl(input->line);
		input = input->next;
	}
	ft_putchar('\n');
}

/*
** lem_in is a program that finds all paths in an undirected graph for n ants
** to go through and prints out the moves the ants will take from source to sink
** with the least amount of moves.
** lem_in will exit and return an error value and message if the input format is
** invalid or there isn't a connection between the source and the sink.
**
**	1. read instructions from STDIN
**	2. validate and store graph information
**	3. saturate graph by doing repeated searches, updating edge capacities after
**		each run
**	4. calculate how many paths are needed and prepare output strings
**	5. print ant movements
*/
int	main(int argc, char **argv)
{
	t_lem		lem;
	t_hashtab	*ht;
	t_input		*input;
	t_route		*route;

	lem = init_lem();
	ht = init_ht();
	input = read_input();
	lem.error = parse_input(input, ht, &lem);
	route = saturate_graph(&lem);
	die_if_error(lem.error, &input, &ht, &route);
	remove_invalids(route);
	sort_paths(route, &lem);
	if (argc > 1 && ft_strequ(argv[1], "--paths"))
		print_paths(route, lem);
	else
		lem.error = print_output(find_best_set(route, &lem), lem, input);
	free_route(&route);
	free_input(&input);
	free_ht(&ht);
	return (lem.error);
}
