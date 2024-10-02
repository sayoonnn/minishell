/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 13:27:25 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/05 14:27:00 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	check_parenthesis(char *cmd, t_deque *tokens, int *cmd_flag, size_t *idx)
{
	size_t	len;
	int		token_type;
	int		check;
	char	*paren;

	check = 0;
	paren = "";
	if (!ft_strncmp(cmd + *idx, "(", 1))
		paren = ft_strdup("(");
	else if (!ft_strncmp(cmd + *idx, ")", 1))
		paren = ft_strdup(")");
	if (paren == NULL)
		return (1);
	len = ft_strlen(paren);
	if (len == 0)
		return (0);
	token_type = select_paren_token_type(paren);
	check = deque_push_back(tokens, token_type, paren);
	(*idx) += len;
	*cmd_flag = 0;
	return (check);
}

int	check_redirection(char *cmd, t_deque *tokens, size_t *idx)
{
	size_t	len;
	int		check;
	char	*rd;

	check = 0;
	rd = "";
	if (!ft_strncmp(cmd + *idx, "<<", 2))
		rd = ft_strdup("<<");
	else if (!ft_strncmp(cmd + *idx, ">>", 2))
		rd = ft_strdup(">>");
	else if (!ft_strncmp(cmd + *idx, "<", 1))
		rd = ft_strdup("<");
	else if (!ft_strncmp(cmd + *idx, ">", 1))
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

int	check_pipeline_list(char *cmd, t_deque *tokens, int *cmd_flag, size_t *idx)
{
	size_t	len;
	int		token_type;
	int		check;
	char	*opr;

	check = 0;
	opr = "";
	if (!ft_strncmp(cmd + *idx, "||", 2))
		opr = ft_strdup("||");
	else if (!ft_strncmp(cmd + *idx, "&&", 2))
		opr = ft_strdup("&&");
	else if (!ft_strncmp(cmd + *idx, "|", 1))
		opr = ft_strdup("|");
	if (opr == NULL)
		return (1);
	len = ft_strlen(opr);
	if (len == 0)
		return (0);
	token_type = select_opr_token_type(opr);
	check = deque_push_back(tokens, token_type, opr);
	(*idx) += len;
	*cmd_flag = 0;
	return (check);
}

int	check_word(char *cmd, t_deque *tokens, int *cmd_flag, size_t *idx)
{
	int		token_type;
	size_t	start;
	size_t	new_len;

	if (cmd[*idx] == 0 || is_white(cmd[*idx])
		|| is_operator(cmd, *idx) || is_parenthesis(cmd[*idx]))
		return (0);
	token_type = select_word_token_type(tokens, cmd_flag);
	new_len = 0;
	start = *idx;
	while (cmd[*idx] != 0 && !is_white(cmd[*idx])
		&& !is_operator(cmd, *idx) && !is_parenthesis(cmd[*idx]))
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
		if (check_parenthesis(cmd, parsing->tokens, &parsing->cmd_flag, &idx))
			return (1);
		if (check_redirection(cmd, parsing->tokens, &idx))
			return (1);
		if (check_pipeline_list(cmd, parsing->tokens, &parsing->cmd_flag, &idx))
			return (1);
		if (check_word(cmd, parsing->tokens, &parsing->cmd_flag, &idx))
			return (1);
	}
	return (0);
}
