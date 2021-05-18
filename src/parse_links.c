/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/05/18 19:13:05 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** returns a pointer to t_link (edge struct)
**
** src: name/id of the edge's source
** dst: name/id of the edge's sink
*/
static t_link	*new_link(char *src, char *dst)
{
	t_link	*link;

	if (!src || !dst)
		return (NULL);
	link = (t_link *)malloc(sizeof(t_link));
	if (!link)
		return (NULL);
	link->src = ft_strdup(src);
	link->to = ft_strdup(dst);
	link->cost = -1;
	link->next = NULL;
	return (link);
}

/*
** appends new edge to the list of edges coming out of a vertex
**
** room: pointer to t_room where the edge starts
** src: name/id of the edge's source
** dst: name/id of the edge's sink
*/
static void	append_link(t_room *room, char *src, char *dst)
{
	if (!room || !src || !dst)
		return ;
	if (room->tube != NULL)
	{
		while (room->tube->next != NULL)
		{
			room->tube = room->tube->next;
		}
		room->tube->next = new_link(src, dst);
	}
	else
		room->tube = new_link(src, dst);
}

/*
** splits input line containing the two vertex ids into a string array,
** checks that the vertices exist and returns the array
**
** index: pointer to hash table t_index
** line: raw line of program input
*/
static char	**check_link(t_index *index, char *line)
{
	char	**arr;
	t_room	*src;
	t_room	*dst;

	arr = ft_strsplit(line, '-');
	if (!arr[0] || !arr[1])
		return (NULL);		// TODO: format error => proper free and exit
	src = get(index, arr[0]);
	dst = get(index, arr[1]);
	if (!src || !dst)
		return (NULL);		// TODO: format error => proper free and exit
	return (arr);
}

/*
** parses raw input for graph edges.
** returns number of edges on success, -1 otherwise.
**
** input: list of input lines, starting from the point where the edges begin
** index: pointer to hash table t_index
*/
int	get_tubes(t_input *input, t_index *index)
{
	char	**arr;
	t_room	*src;
	int		i;

	i = 0;
	while (input->line != NULL)
	{
		arr = check_link(index, input->line);
		if (arr == NULL)
			return (-1);
		src = get(index, arr[0]);
		append_link(src, arr[0], arr[1]);
		i += 1;
		input = input->next;
	}
	ft_liberator(3, &arr[0], &arr[1], &arr[2]);
	free(arr);
	if (src->tube == NULL)
		return (-1);
	return (i);
}
