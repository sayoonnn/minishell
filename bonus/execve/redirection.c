/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:39:40 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 22:05:17 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cknopen(char *file_name, int io_fd[2], int type)
{
	if (type == GREAT || type == DGREAT)
	{
		if (!make_output(file_name, io_fd, type))
			return (false);
	}
	else
	{
		if (!make_input(file_name, io_fd, type))
			return (false);
	}
	return (true);
}

static int	is_ambiguous(char *before, t_list *lst)
{
	if (lst->head == NULL || lst->head->next != NULL)
	{
		ft_printf(2, "minishell: %s: ambiguous redirect\n", before);
		ft_lstclear(lst);
		return (true);
	}
	return (false);
}

int	handle_heredoc_redir(t_tree_node *pt, t_envtree *env)
{
	int		ret;
	t_list	*word_lst;

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
		word_lst = interprete_words(pt->right->contents, env);
		if (word_lst == NULL)
			return (false);
		ret = make_input(word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(word_lst);
		free(word_lst);
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
		if (!handle_other_redir(pt->left, env)
			|| !handle_other_redir(pt->right, env))
			return (false);
	}
	else if (pt->token_type == REDIRECTION_INFO && \
			pt->left->token_type != DLESS)
	{
		word_lst = interprete_words(pt->right->contents, env);
		if (word_lst == NULL)
			return (false);
		if (is_ambiguous(pt->right->contents->head->content, word_lst))
			return (false);
		ret = cknopen(word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(word_lst);
		free(word_lst);
	}
	return (ret);
}
