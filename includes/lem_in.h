/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/15 15:41:14 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define SIZE 10000

# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef	struct	s_pair
{
	char			*room;
	char			*xy;
	struct s_dict	*next;
}				t_pair;

typedef struct	s_index
{
	struct s_pair	**kw;
}				t_index;

void			parse_line(char *input);

#endif
