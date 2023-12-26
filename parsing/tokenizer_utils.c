/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:30:47 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 14:42:09 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

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

int	select_word_token_type(t_parsing *parsing)
{
	int	token_type;

	token_type = CMD;
	if (deque_empty(parsing->tokens) || parsing->cmd_flag == 0)
	{
		parsing->cmd_flag = 1;
		token_type = CMD;
	}
	else if (deque_back(parsing->tokens) == REDIRECTION)
		token_type = FILENAME;
	else if (parsing->cmd_flag)
		token_type = ARGV;
	return (token_type);
}
