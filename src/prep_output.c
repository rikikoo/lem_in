/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:01:52 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/22 15:16:59 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** basically sprintf for a very specific job.
** returns a formatted string for the output array.
**
** @ant_str: the number of the ant as a string
** @vertex: the id of the vertex
*/
static char	*format_move(char *ant_str, char *vertex)
{
	char	*move;
	int		ant_len;
	int		vertex_len;
	int		i;

	ant_len = ft_strlen(ant_str);
	vertex_len = ft_strlen(vertex);
	move = (char *)malloc(sizeof(char) * (ant_len + vertex_len + 3));
	if (!move)
		return (NULL);
	i = 0;
	move[i] = 'L';
	while (++i <= ant_len)
		move[i] = ant_str[i - 1];
	move[i] = '-';
	while (++i < (ant_len + vertex_len + 2))
		move[i] = vertex[i - (ant_len + 2)];
	move[i] = '\0';
	free(ant_str);
	return (move);
}

/*
** copies the found paths which are sorted from shortest to longest into the
** empty output array in order for every ant, so that once the longest path
** has been copied, the next ant's path will be the shortest again, and so on.
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @out: pointer to an array of empty paths
** @pants: int array storing the number of ants per path
*/
void	fill_output_arr(t_route *route, t_lem lem, char ***out, int *pants)
{
	int		ant;
	int		move;
	t_route	*head;
	t_edge	*path_head;

	if (!out)
		return ;
	ant = -1;
	head = route;
	while (++ant < lem.ants)
	{
		move = -1;
		path_head = route->path;
		while (route->path && ++move < route->len)
		{
			// ft_printf("route i: %d  ant: %d  move: %d\n", route->i, ant, move);
			out[ant][move] = format_move(ft_itoa(ant + 1), route->path->to->id);
			route->path = route->path->prev_in_path;
		}
		route->path = path_head;
		pants[route->i - 1]--;
		route = route->next;
		while (pants[route->i - 1] < 0)
			route = route->next;
		if (!route || pants[route->i - 1] == 0 || route->i >= lem.last_index)
			route = head;
	}
}

/*
** creates an empty path for each ant and each move per path.
** every path is an array of strings.
** returns a pointer to the array of strings.
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @pants: int array storing the number of ants per path
*/
char	***prepare_output_arr(t_route *route, t_lem lem, int *pants)
{
	t_route	*head;
	char	***out;
	int		ant;
	int		move;

	head = route;
	out = (char ***)malloc(sizeof(char **) * (lem.ants + 1));
	if (!out || !route || !pants || lem.error)
		return (NULL);
	ant = -1;
	while (++ant < lem.ants)
	{
		out[ant] = (char **)malloc(sizeof(char *) * (route->len + 1));
		if (!out[ant])
			return (NULL);
		move = -1;
		while (++move <= route->len)
			out[ant][move] = NULL;
		pants[route->i - 1]--;
		route = route->next;
		while (route && pants[route->i - 1] < 0)
			route = route->next;
		if (!route || pants[route->i - 1] == 0 || route->i >= lem.last_index)
			route = head;
	}
	out[ant] = NULL;
	return (out);
}
