/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:45:24 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/30 20:45:25 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static size_t	ft_arrlen(char *arr[])
{
	size_t	i;

	i = 0;
	while (*arr++)
		i++;
	return (i);
}

void	ft_cd(char *arg[])
{
	char	buffer[PATH_MAX];
	int		ac;
	int		i;

	ac = ft_arrlen(arg);
	if (!getcwd(buffer, sizeof(buffer)))
		return ; // 에러처리 > 최종점검 필요
	if (ac == 1)
		return ;
	else if (ac == 2)
	{
		if (!ft_strncmp(arg[1], "..", 2))
		{
			i = ft_strlen(buffer) - 1;
			while (buffer[i] != '/')
				i--;
			buffer[i + 1] = 0;
			chdir(buffer);
			printf("%s\n", buffer);
		}
		else
			chdir(arg[1]);
	}
}

int main(int ac, char *av[]){
	(void)ac;
	ft_cd(&av[1]);
}
