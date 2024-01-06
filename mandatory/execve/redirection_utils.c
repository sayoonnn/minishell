/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:57:04 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 21:57:05 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_first(t_tree_node *pt, t_envtree *env)
{
	if (pt == NULL)
		return (true);
	if (pt->token_type == CMD)
		return (handle_heredoc_redir(pt->right, env));
	if (!handle_heredoc_first(pt->left, env))
		return (false);
	if (!handle_heredoc_first(pt->right, env))
		return (false);
	return (true);
}

int	handle_other_redirs(t_tree_node *pt, t_envtree *env)
{
	if (pt == NULL)
		return (true);
	if (pt->token_type == CMD)
		return (handle_other_redir(pt->right, env));
	if (!handle_other_redirs(pt->left, env))
		return (false);
	if (!handle_other_redirs(pt->right, env))
		return (false);
	return (true);
}

static int	is_ambiguous(char *before, t_list *lst)
{
	if (lst->head == NULL || lst->head->next != NULL)
	{
		ft_printf(2, "minishell: %s: ambiguous redirect\n", before);
		ft_lstclear(lst);
		free(lst);
		return (true);
	}
	return (false);
}

int	handle_heredoc_redir(t_tree_node *pt, t_envtree *env)
{
	int		ret;
	char	*tmp;

	ret = true;
	if (pt == NULL)
		return (true);
	if (pt->token_type == REDIRECTION_LIST)
	{
		if (!handle_heredoc_redir(pt->left, env)
			|| !handle_heredoc_redir(pt->right, env))
			return (false);
	}
	else if (pt->token_type == REDIRECTION_INFO && \
			pt->left->token_type == DLESS)
	{
		tmp = remove_quote(pt->right->contents->head->content);
		ret = make_input(tmp, pt->fd, pt->left->token_type, env);
		free(tmp);
	}
	return (ret);
}

int	handle_other_redir(t_tree_node *pt, t_envtree *env)
{
	int		ret;
	t_list	*word_lst;

	ret = true;
	if (pt == NULL)
		return (true);
	if (pt->token_type == REDIRECTION_LIST)
	{
		if (!handle_other_redir(pt->left, env) \
		|| !handle_other_redir(pt->right, env))
			return (false);
	}
	else if (pt->token_type == REDIRECTION_INFO \
			&& pt->left->token_type != DLESS)
	{
		word_lst = interprete_words(pt->right->contents, env);
		if (is_ambiguous(pt->right->contents->head->content, word_lst))
			return (false);
		ret = cknopen(word_lst->head->content, pt->fd, \
		pt->left->token_type, env);
		ft_lstclear(word_lst);
		free(word_lst);
	}
	return (ret);
}
