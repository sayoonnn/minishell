/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:17:54 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 22:09:08 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	print_syntax_token_error(char *content)
{
	printf("bash: syntax error near unexpected token `%s'", content);
	return (1);
}

int	print_syntax_unmatched_error(char ch)
{
	printf("bash: syntax error: not matched `%c'\n", ch);
	return (1);
}
