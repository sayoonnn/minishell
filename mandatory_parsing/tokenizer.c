/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:27:25 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 22:41:22 by jonghopa         ###   ########.fr       */
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

int	check_pipeline(char *cmd, t_data *data, size_t *idx)
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
	check = deque_push_back(data->tokens, PIPELINE, pipe);
	(*idx) += len;
	data->cmd_flag = 0;
	return (check);
}

int	check_word(char *cmd, t_data *data, size_t *idx)
{
	int		token_type;
	size_t	new_len;

	if (cmd[*idx] == 0 || is_white(cmd[*idx]) || is_operator(cmd[*idx]))
		return (0);
	token_type = select_word_token_type(data);
	new_len = 0;
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
	if (deque_push_back(data->tokens, token_type, make_word(cmd, idx, new_len)))
		return (1);
	return (0);
}

int	tokenize(char *cmd, t_data *data)
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
		if (check_redirection(cmd, data->tokens, &idx))
			return (1);
		if (check_pipeline(cmd, data, &idx))
			return (1);
		if (check_word(cmd, data, &idx))
			return (1);
	}
	return (0);
}
