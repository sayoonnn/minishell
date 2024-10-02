/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:30:47 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/02 12:37:09 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	check_rquote(char *cmd, size_t *idx, size_t *new_len)
{
	char	quote;
	size_t	tmp_idx;
	size_t	len;

	tmp_idx = *idx;
	quote = cmd[*idx];
	len = 0;
	tmp_idx++;
	len++;
	while (cmd[tmp_idx] != 0 && cmd[tmp_idx] != quote)
	{
		tmp_idx++;
		len++;
	}
	if (cmd[tmp_idx] == quote)
		len++;
	(*idx) += len;
	(*new_len) += len;
	return (0);
}

int	select_paren_token_type(char *paren)
{
	int	token_type;

	token_type = CMD;
	if (!ft_strncmp(paren, "(", 1))
		token_type = LPAREN;
	else if (!ft_strncmp(paren, ")", 1))
		token_type = RPAREN;
	return (token_type);
}

int	select_opr_token_type(char *operator)
{
	int	token_type;

	token_type = CMD;
	if (!ft_strncmp(operator, "||", 2))
		token_type = LIST;
	else if (!ft_strncmp(operator, "&&", 2))
		token_type = LIST;
	else if (!ft_strncmp(operator, "|", 1))
		token_type = PIPE;
	return (token_type);
}

int	select_word_token_type(t_deque *tokens, int *cmd_flag)
{
	int	token_type;

	token_type = CMD;
	if (!deque_empty(tokens) && deque_back(tokens) == REDIRECTION)
		token_type = FILENAME;
	else if (*cmd_flag == 0)
	{
		*cmd_flag = 1;
		token_type = CMD;
	}
	else if (*cmd_flag)
		token_type = ARGV;
	return (token_type);
}
