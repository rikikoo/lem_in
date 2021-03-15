/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:41:11 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/15 15:41:08 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_index			*init_index(void)
{
	t_index			*iptr;
	unsigned int	i;

	if (!(iptr = (t_index *)malloc(sizeof(t_index))))
		return (NULL);
	if (!(iptr->kw = (t_pair **)malloc(sizeof(t_pair *) * SIZE)))
		return (NULL);
	i = 0;
	while (i < SIZE)
	{
		iptr->kw[i] = NULL;
		i++;
	}
	return (iptr);
}

unsigned int	hashof(const char *key)
{
	unsigned int	val;
	unsigned int	i;

	val = 0;
	i = 0;
	while (i < ft_strlen(key))
	{
		val *= (89 + key[i]);
		i++;
	}
	return (val % SIZE);
}

t_pair			*set_pair(const char *key, char *val)
{
	t_pair	*ptr;

	if (!(ptr = (t_pair *)malloc(sizeof(t_pair))))
		return (NULL);
	ptr->room = ft_strdup(key);
	ptr->xy = ft_strdup(val);
	return (ptr);
}

void			insert(t_index *iptr, const char *key, char *val)
{
	unsigned int	i;

	i = hashof(key);
	if (iptr->kw[i] == NULL)
	{
		iptr->kw[i] = set_pair(key, val);
		if (!iptr->kw[i])
			return ;
	}
}
