/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:13:29 by rkyttala          #+#    #+#             */
/*   Updated: 2021/04/06 10:03:10 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

static t_link	*add_link(t_room *room, char *src, char *dst)
{
	t_link	*head;

	if (!room || !src || !dst)
		return (NULL);
	head = room->tube;
	while (room->tube->next != NULL)
		room->tube = room->tube->next;
	room->tube->next = new_link(src, dst);
	return (head);
}

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

int	get_tubes(t_input *input, t_index *index)
{
	char	**arr;
	t_room	*src;
	t_link	*tube;

	while (input->line != NULL)
	{
		arr = check_link(index, input->line);
		if (arr == NULL)
			return (-1);
		src = get(index, arr[0]);
		tube = src->tube;
		if (tube != NULL)
		{
			while (tube != NULL)
				tube = tube->next;
			tube = add_link(src, arr[0], arr[1]);
		}
		else
			tube = new_link(arr[0], arr[1]);
		src->tube = tube;
		input = input->next;
	}
	if (tube == NULL)
		return (-1);
	return (0);
}
