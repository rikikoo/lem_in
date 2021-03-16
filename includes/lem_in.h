/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkyttala <rkyttala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:29:14 by rkyttala          #+#    #+#             */
/*   Updated: 2021/03/16 14:09:50 by rkyttala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define SIZE 10000

# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct	s_lem
{
	int	ants;
	int	start;
	int	finish;
}				t_lem;

typedef	struct	s_room
{
	char			*name;
	char			*xy;
	int				checked;
	int				occupied;
	struct s_room	*next;
}				t_room;

typedef struct	s_link
{
	int				src;
	int				dst;
	struct s_link	*next;
}				t_link;

typedef struct	s_index
{
	struct s_room	**rooms;
}				t_index;

t_index			init_index(void);
char			*valueof(t_index *index, const char *key);
void			insert(t_index *index, const char *key, const char *val);
void			parse_line(char *input);

#endif
