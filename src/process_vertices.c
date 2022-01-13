/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_vertices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2022/01/13 19:15:37 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** vertex info is given in the form "id coord_x coord_y" followed by a newline.
** vertex_parse() splits the three attributes into their own strings, validates
** each one and stores them into the hash table.
**
** @str: current input line string
** @v: deteremines whether str contains source (0), sink (1) or intermediate (2)
** 	vertex info
*/
static int	vertex_parse(t_hashtab *ht, char *str, t_lem *lem, int v)
{
	char	**arr;
	int		error;
	int		i;

	if (!str)
		return (-1);
	error = 0;
	arr = ft_strsplit(str, ' ');
	if (ft_arrlen((void **)arr) != 3 || arr[0][0] == 'L' || \
	!ft_digits_only(arr[1]) || !ft_digits_only(arr[2]))
		error = -1;
	if (!error)
	{
		set(ht, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
		if (v == 1)
			lem->sink = get(ht, arr[0]);
		else if (v == 0)
			lem->source = get(ht, arr[0]);
	}
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (error);
}

/*
** source and sink are denoted in a preceding line by "##start" or "##end".
** other lines that start with a '#' are comments, thus skipped.
*/
static t_input	*check_comment(t_input *input, t_hashtab *ht, t_lem *lem)
{
	char	*str;
	int		i;

	str = input->line;
	i = 0;
	if (ft_strequ(str, "##start") && lem->source == NULL)
	{
		input = input->next;
		if (vertex_parse(ht, input->line, lem, 0) < 0)
			return (NULL);
	}
	else if (ft_strequ(str, "##end") && lem->sink == NULL)
	{
		input = input->next;
		if (vertex_parse(ht, input->line, lem, 1) < 0)
			return (NULL);
	}
	else if ((ft_strequ(str, "##end") && lem->sink != NULL) || \
	(ft_strequ(str, "##start") && lem->source != NULL))
		return (NULL);
	else
		lem->vertices--;
	return (input->next);
}

/*
** loop through input lines until a line with a '-' (dash) is encountered.
** the lines until that point should contain all vertex names, their coordinates
** and identify source and sink vertices.
**
** @input: pointer to list of instructions
** @ht: pointer to hash table of vertices
** @lem: pointer to a general runtime info struct
*/
t_input	*get_vertices(t_input *input, t_hashtab *ht, t_lem *lem)
{
	while (1)
	{
		if (!input)
			return (NULL);
		if (input->line[0] == '#')
		{
			input = check_comment(input, ht, lem);
			if (!input)
				return (NULL);
		}
		else if (ft_strchr(input->line, '-'))
			break ;
		else
		{
			if (vertex_parse(ht, input->line, lem, 2) < 0)
				return (NULL);
			input = input->next;
		}
		lem->vertices += 1;
	}
	if (lem->source != NULL && lem->sink != NULL)
		return (input);
	else
		return (NULL);
}
