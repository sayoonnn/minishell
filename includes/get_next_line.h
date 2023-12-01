/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:13:49 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/10 21:14:45 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# if BUFFER_SIZE < 0
#  error BUFFER_SIZE must be positve
# endif

char	*get_next_line(int fd);
char	*ft_makestr(int fd, char *string, char *buffer);
int		gnl_strlen(const char *s);
void	*gnl_memcpy(void *dst, void *src, int n);
char	*gnl_strjoin(char *s1, char *s2, int s2_len);
char	*gnl_memchr(char *s, int c, int n);
char	*gnl_strdup(char *s, int c);

#endif