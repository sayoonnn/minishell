/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:17:54 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/05 13:23:40 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors_bonus.h"

int	print_syntax_token_error(char *content)
{
	ft_printf(2, "minishell: syntax error near unexpected token `%s'\n", \
	content);
	g_errcode = CODE_SYNTAX_ERROR;
	return (CODE_SYNTAX_ERROR);
}

int	print_syntax_unmatched_error(char ch)
{
	ft_printf(2, "minishell: syntax error: not matched `%c'\n", ch);
	g_errcode = CODE_SYNTAX_ERROR;
	return (CODE_SYNTAX_ERROR);
}
