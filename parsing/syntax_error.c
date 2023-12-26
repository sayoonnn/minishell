/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:17:54 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 16:05:38 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	print_syntax_token_error(char *content)
{
	printf("bash: syntax error near unexpected token `%s'\n", content);
	err_code = 258 << 8;
	return (CODE_SYNTAX_ERROR);
}

int	print_syntax_unmatched_error(char ch)
{
	printf("bash: syntax error: not matched `%c'\n", ch);
	err_code = 258 << 8;
	return (CODE_SYNTAX_ERROR);
}
