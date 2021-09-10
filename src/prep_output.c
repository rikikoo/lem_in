/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:01:52 by rkyttala          #+#    #+#             */
/*   Updated: 2021/09/10 23:07:49 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** basically sprintf for a very specific job.
** returns a formatted string for the output array.
**
** @ant: the number of the ant as a string
** @vertex: the id of the vertex
*/
static char	*format_move(int ant, char *vertex)
{
	char	*move;
	char	*ant_str;
	int		ant_len;
	int		vertex_len;
	int		i;

	ant_str = ft_itoa(ant);
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
** returns a pointer to the filled array of strings.
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
** @out: pointer to an array of empty paths
*/
char	***fill_output_arr(t_route *route, t_lem *lem, char ***out)
{
	int		move;
	int		ant;
	t_route	*head;
	t_edge	*path_head;

	move = 0;
	ant = 0;
	head = route;
	while (++ant <= lem->ants)
	{
		path_head = route->path;
		while (++move <= route->len && route->path)
		{
			out[ant - 1][move - 1] = format_move(ant, route->path->to->id);
			route->path = route->path->prev_in_path;
		}
		route->path = path_head;
		if (ant % lem->n_paths > 0)
			route = route->next;
		else
			route = head;
		move = 0;
	}
	return (out);
}

/*
** creates an empty path (int i) for each ant and each move (int j) per path.
** every path is an array of strings.
** returns a pointer to the array of strings.
**
** @route: pointer to the head of a list of paths
** @lem: a general runtime info struct
*/
char	***prepare_output_arr(t_route *route, t_lem *lem)
{
	t_route	*head;
	char	***out;
	int		i;
	int		j;

	head = route;
	out = (char ***)malloc(sizeof(char **) * (lem->ants + 1));
	if (!out || !route)
		return (NULL);
	i = -1;
	while (++i < lem->ants)
	{
		out[i] = (char **)malloc(sizeof(char *) * (route->len + 1));
		if (!out[i])
			return (NULL);
		j = -1;
		while (++j <= route->len)
			out[i][j] = NULL;
		if ((i + 1) % lem->n_paths > 0)
			route = route->next;
		else
			route = head;
	}
	out[i] = NULL;
	return (out);
}
