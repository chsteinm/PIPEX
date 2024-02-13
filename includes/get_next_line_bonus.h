/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:22:58 by chrstein          #+#    #+#             */
/*   Updated: 2024/02/06 17:23:00 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "./libft/libft.h"

# include <unistd.h>
# include <stdlib.h>

typedef struct s_struct
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	char	*tmp_tmp;
	char	*buf_ptr;
	ssize_t	bytes_read;
}	t_struct;

char	*get_next_line(int fd);

#endif
