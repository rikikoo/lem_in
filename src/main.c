/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:28:18 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/12 17:09:01 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** prints all paths if program got "--paths" as an argument
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
** checks @path's each vertex against @cmp's all vertices. if a match is
** encountered, @cmp cannot be used simultaneously with @path and 0 is returned,
** otherwise 1.
*/
static int	paths_are_distinct(t_path *path, t_path *cmp, t_vertex *sink)
{
	t_path	*cmp_head;

	cmp_head = cmp;
	while (path && path->edge->to != sink)
	{
		while (cmp && cmp->edge->to != sink)
		{
			if (cmp->edge->to == path->edge->to)
				return (0);
			cmp = cmp->next;
		}
		path = path->next;
		cmp = cmp_head;
	}
	return (1);
}

static int overlaps(t_route *route, t_lem lem)
{
	int		set;
	int		ret;
	t_route	*next;

	ret = 0;
	while (route && route->is_valid)
	{
		set = route->set;
		next = route->next;
		while (next && next->is_valid && next->set == set)
		{
			if (!paths_are_distinct(route->path, next->path, lem.sink))
			{
				ft_printf("overlapping paths within set %d: %d & %d\n", \
				set, route->id, next->id);
				ret = 1;
			}
			next = next->next;
		}
		route = route->next;
	}
	return (ret);
}

static void	remove_invalids(t_route *route)
{
	t_route	*tmp;
	t_route	*prev;

	prev = route;
	route = route->next;
	while (route)
	{
		while (route && !route->is_valid)
		{
			tmp = route;
			route = route->next;
			prev->next = route;
			free(tmp);
		}
		if (route)
		{
			prev = route;
			route = route->next;
		}
	}
}

/*
** lem_in is a program that finds all paths in an undirected graph for n ants
** to go through and prints out the moves the ants will take from source to sink
** with the least amount of moves.
** The number of ants, vertex names and coordinates and their edges are given
** as input in a specific format (see README).
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
	if ((argc > 1 && ft_strequ(argv[1], "--paths")) || overlaps(route, lem))
		print_paths(route, lem);
	else
		lem.error = print_output(find_best_set(route, &lem), lem, input);
	free_route(&route);
	free_input(&input);
	free_ht(&ht);
	return (lem.error);
}
