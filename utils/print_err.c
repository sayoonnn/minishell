/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:43:34 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 15:44:50 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void	print_err(char *pname, char *str_err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, pname, ft_strlen(pname));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	write(STDERR_FILENO, "\n", 1);
}

void	print_err_builtin(char *func_name ,char *pname, char *str_err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, func_name, ft_strlen(func_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, pname, ft_strlen(pname));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str_err, ft_strlen(str_err));
	write(STDERR_FILENO, "\n", 1);
}
