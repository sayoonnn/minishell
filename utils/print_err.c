/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:43:34 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/04 19:43:36 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_enoent(char *pname, char *dirname)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, pname, ft_strlen(pname));
	write(STDERR_FILENO, ": ", 2);
	perror(dirname);
}
