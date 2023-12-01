/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:59:00 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 18:59:04 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <limits.h>
#include <unistd.h>
#include <stdio.h>

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		return (1);
	printf("%s\n", path);
	return (0);
}
