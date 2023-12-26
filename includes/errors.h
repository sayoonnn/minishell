/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:31:45 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 15:45:18 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_NO_DIR_FILE	"No such file or directory"
# define ERR_CMD_NOT_FOUND	"command not found"

# define CODE_AMBIGUOUS_RD	1
# define CODE_PERM_DENIED	126
# define CODE_CMD_NOT_FOUND 127
# define CODE_SYNTAX_ERROR 	258

# include <unistd.h>

void	print_err(char *pname, char *dirname);
void	print_err_builtin(char *func_name ,char *pname, char *str_err);
int		print_syntax_token_error(char *content);
int		print_syntax_unmatched_error(char ch);

extern int	err_code;

#endif
