/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:25:36 by magoosse          #+#    #+#             */
/*   Updated: 2025/03/13 18:39:57 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 700000
# endif

# if BUFFER_SIZE > 8000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include "libft.h"
# include <fcntl.h>  //open
# include <stdint.h> //SIZE_MAX
# include <stdio.h>  //printf
# include <stdlib.h> //malloc free
# include <unistd.h> //read
// GNL
char	*devers(char *stash, char *filled);
char	*fill_stash(int fd, char *stash);
char	*fill_line(char *stash);
char	*cut_stash(char *stash, char *line);
char	*get_next_line(int fd);
// Utils
void	ft_free(void *str);
int		is_line(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);

#endif
