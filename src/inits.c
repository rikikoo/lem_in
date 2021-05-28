/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 13:11:49 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/27 16:40:42 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** t_lem is a struct containing
**	- the # of ants
**	- the # of vertices
**	- the # of edges
**	- source and sink ids
**	- flow of the graph, initialized to a large number
**
** returns a pointer to an initialized t_lem
*/
t_lem	*init_lem(void)
{
	t_lem	*lem;

	lem = (t_lem *)malloc(sizeof(t_lem));
	if (!lem)
		return (NULL);
	lem->ants = 0;
	lem->vertices = 0;
	lem->edges = 0;
	lem->max_flow = 0;
	lem->source = NULL;
	lem->sink = NULL;
	return (lem);
}

/*
** init_index returns a pointer to t_index, all pointers initialized to NULL
*/
t_index	*init_index(void)
{
	t_index	*index;
	int		i;

	index = (t_index *)malloc(sizeof(t_index));
	if (!index)
		return (NULL);
	index->vertices = (t_vertex **)malloc(sizeof(t_vertex *) * HT_SIZE);
	if (!index->vertices)
		return (NULL);
	i = 0;
	while (i < HT_SIZE)
	{
		index->vertices[i] = NULL;
		i++;
	}
	return (index);
}

/*
** returns an array of char pointers of the given size.
** functions as a makeshift queue data structure.
*/
char	**wipe_array(char **arr, const int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		arr[i] = NULL;
		i++;
	}
	return (arr);
}
