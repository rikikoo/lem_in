/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:35:22 by rkyttala          #+#    #+#             */
/*   Updated: 2021/06/03 19:28:00 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	vertex_parse(t_index *index, char *str, t_lem *lem, int v)
{
	char	**arr;
	int		i;
	int		j;

	if (!str)
		return (-1);
	arr = ft_strsplit(str, ' ');
	if (ft_arrlen((void **)arr) != 3)
		return (-1);
	i = 0;
	j = 0;
	while (ft_isdigit(arr[1][i]))
		i++;
	while (ft_isdigit(arr[2][j]))
		j++;
	if (arr[1][i] != '\0' || arr[2][j] != '\0' || i < 1 || j < 1)
		return (-1);
	if (v == 1)
		lem->sink = ft_strdup(arr[0]);
	else if (v == 0)
		lem->source = ft_strdup(arr[0]);
	set(index, arr[0], ft_atoi(arr[1]), ft_atoi(arr[2]));
	ft_liberator(4, &arr[0], &arr[1], &arr[2], &arr[3]);
	free(arr);
	return (0);
}

static t_input	*check_command(t_input *input, t_index *index, t_lem *lem)
{
	char	*str;
	char	**arr;
	int		i;

	str = input->line;
	arr = NULL;
	i = 0;
	if (ft_strlen(str) < 3 || (str[0] != '#' && str[1] != '#'))
		return (input->next);
	if (ft_strequ((str + 2), "start") && lem->source == NULL)
	{
		input = input->next;
		if (vertex_parse(index, input->line, lem, 0) < 0)
			return (NULL);
	}
	else if (ft_strequ((str + 2), "end") && lem->sink == NULL)
	{
		input = input->next;
		if (vertex_parse(index, input->line, lem, 1) < 0)
			return (NULL);
	}
	else
		return (NULL);
	return (input->next);
}

t_input	*get_vertices(t_input *input, t_index *index, t_lem *lem)
{
	while (1)
	{
		if (!input)
			return (NULL);
		if (ft_strchr(input->line, '#'))
		{
			input = check_command(input, index, lem);
			if (!input)
				return (NULL);
		}
		else if (ft_strchr(input->line, '-'))
			break ;
		else
		{
			if (vertex_parse(index, input->line, lem, 2) < 0)
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
