/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:27:25 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/02 12:35:59 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	check_redirection(char *cmd, t_deque *tokens, size_t *idx)
{
	size_t	len;
	int		check;
	char	*rd;

	check = 0;
	rd = "";
	if (ft_strncmp(cmd + *idx, "<<", 2) == 0)
		rd = ft_strdup("<<");
	else if (ft_strncmp(cmd + *idx, ">>", 2) == 0)
		rd = ft_strdup(">>");
	else if (ft_strncmp(cmd + *idx, "<", 1) == 0)
		rd = ft_strdup("<");
	else if (ft_strncmp(cmd + *idx, ">", 1) == 0)
		rd = ft_strdup(">");
	if (rd == NULL)
		return (1);
	len = ft_strlen(rd);
	if (len == 0)
		return (0);
	check = deque_push_back(tokens, REDIRECTION, rd);
	(*idx) += len;
	return (check);
}

int	check_pipeline(char *cmd, t_deque *tokens, int *cmd_flag, size_t *idx)
{
	size_t	len;
	int		check;
	char	*pipe;

	check = 0;
	pipe = "";
	if (ft_strncmp(cmd + *idx, "|", 1) == 0)
		pipe = ft_strdup("|");
	if (pipe == NULL)
		return (1);
	len = ft_strlen(pipe);
	if (len == 0)
		return (0);
	check = deque_push_back(tokens, PIPE, pipe);
	(*idx) += len;
	*cmd_flag = 0;
	return (check);
}

int	check_word(char *cmd, t_deque *tokens, int *cmd_flag, size_t *idx)
{
	int		token_type;
	size_t	start;
	size_t	new_len;

	if (cmd[*idx] == 0 || is_white(cmd[*idx]) || is_operator(cmd[*idx]))
		return (0);
	token_type = select_word_token_type(tokens, cmd_flag);
	new_len = 0;
	start = *idx;
	while (cmd[*idx] != 0 && !is_white(cmd[*idx]) && !is_operator(cmd[*idx]))
	{
		if (is_quote(cmd[*idx]))
			check_rquote(cmd, idx, &new_len);
		else
		{
			(*idx)++;
			new_len++;
		}
	}
	if (deque_push_back(tokens, token_type, ft_substr(cmd, start, new_len)))
		return (1);
	return (0);
}

int	tokenize(char *cmd, t_parsing *parsing)
{
	size_t	cmd_len;
	size_t	idx;

	cmd_len = ft_strlen(cmd);
	if (cmd == NULL || !cmd_len)
		return (1);
	idx = 0;
	while (idx < cmd_len)
	{
		if (is_white(cmd[idx]))
		{
			idx++;
			continue ;
		}
		if (check_redirection(cmd, parsing->tokens, &idx))
			return (1);
		if (check_pipeline(cmd, parsing->tokens, &parsing->cmd_flag, &idx))
			return (1);
		if (check_word(cmd, parsing->tokens, &parsing->cmd_flag, &idx))
			return (1);
	}
	return (0);
}
