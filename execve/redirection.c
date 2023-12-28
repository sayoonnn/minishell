/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:39:40 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/20 15:39:41 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_output(char *filename, int io_fd[2], int opt)
{
	if (opt == GREAT)
	{
		if (io_fd[1] != STDOUT_FILENO)
			close(io_fd[1]);
		io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_TRUNC);
		if (io_fd[1] == -1)
			return (false);
	}
	else
	{
		if (io_fd[1] != STDOUT_FILENO)
			close(io_fd[1]);
		io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_APPEND);
		if (io_fd[1] == -1)
			return (false);
	}
	return (true);
}

static int	make_input(char *filename, int io_fd[2], int opt)
{
	if (opt == LESS)
	{
		if (io_fd[0] != STDIN_FILENO)
			close(io_fd[0]);
		io_fd[0] = open_in_file(filename);
		if (io_fd[0] == -1)
			return (false);
	}
	else
	{
		if (io_fd[0] != STDIN_FILENO)
			close(io_fd[0]);
		io_fd[0] = get_heredoc_fd(filename);
		if (io_fd[0] == -1)
			return (false);
	}
	return (true);
}

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
		print_err(before, "ambiguous redirect");
		ft_lstclear(lst);
		return (true);
	}
	return (false);
}

int	handle_heredoc_redir(t_parsing *ps, t_envtree *env, t_tree_node *pt)
{
	int	ret;

	ret = false;
	if (pt == NULL)
		return (true);
	if (pt->token_type == REDIRECTION_LIST)
	{
		pt->left->fd[0] = 0;
		pt->left->fd[1] = 1;
		ret = handle_heredoc_redir(ps, env, pt->left);
		if (ret == false)
			return (ret);
		ret = handle_heredoc_redir(ps, env, pt->right);
		if (ret == false)
			return (ret);
	}
	else if (pt->token_type == REDIRECTION_INFO && pt->left->token_type == DLESS)
	{
		substitute_words(ps, env, pt->right->contents);
		if (is_ambiguous(pt->right->contents->head->content, ps->word_lst))
			return (false);
		ret = make_input(ps->word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(ps->word_lst);
		if (!ret)
			return (ret);
	}
	return (true);
}

int	handle_other_redir(t_parsing *ps, t_envtree *env, t_tree_node *pt)
{
	int	ret;

	ret = false;
	if (pt == NULL)
		return (true);
	if (pt->token_type == REDIRECTION_LIST)
	{
		if (pt->left->left->token_type != DLESS)
		{
			pt->left->fd[0] = 0;
			pt->left->fd[1] = 1;
			ret = handle_other_redir(ps, env, pt->left);
			if (ret == false)
				return (ret);
		}
		ret = handle_other_redir(ps, env, pt->right);
		if (ret == false)
			return (ret);
	}
	else if (pt->token_type == REDIRECTION_INFO && pt->left->token_type != DLESS)
	{
		substitute_words(ps, env, pt->right->contents);
		if (is_ambiguous(pt->right->contents->head->content, ps->word_lst))
			return (false);
		ret = cknopen(ps->word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(ps->word_lst);
		if (!ret)
			return (ret);
	}
	return (true);
}
