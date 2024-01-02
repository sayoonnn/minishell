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

// static int	make_output(char *filename, int io_fd[2], int opt)
// {
// 	if (opt == GREAT)
// 	{
// 		if (io_fd[1] != STDOUT_FILENO)
// 			close(io_fd[1]);
// 		io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_TRUNC);
// 		if (io_fd[1] == -1)
// 			return (false);
// 	}
// 	else
// 	{
// 		if (io_fd[1] != STDOUT_FILENO)
// 			close(io_fd[1]);
// 		io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_APPEND);
// 		if (io_fd[1] == -1)
// 			return (false);
// 	}
// 	return (true);
// }

static int	make_output(char *filename, int io_fd[2], int opt)
{
	int	write_flag;

	write_flag = 0;
	if (io_fd[1] != STDOUT_FILENO)
		close(io_fd[1]);
	if (opt == GREAT)
		write_flag = O_TRUNC;
	else if (opt == DGREAT)
		write_flag = O_APPEND;
	io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | write_flag);
	if (io_fd[1] == -1)
		return (false);
	return (true);
}

// static int	make_input(char *filename, int io_fd[2], int opt)
// {
// 	if (opt == LESS)
// 	{
// 		if (io_fd[0] != STDIN_FILENO)
// 			close(io_fd[0]);
// 		io_fd[0] = open_in_file(filename);
// 		if (io_fd[0] == -1)
// 			return (false);
// 	}
// 	else
// 	{
// 		if (io_fd[0] != STDIN_FILENO)
// 			close(io_fd[0]);
// 		io_fd[0] = get_heredoc_fd(filename);
// 		if (io_fd[0] == -1)
// 			return (false);
// 	}
// 	return (true);
// }

static int	make_input(char *filename, int io_fd[2], int opt)
{
	if (io_fd[0] != STDIN_FILENO)
		close(io_fd[0]);
	if (opt == LESS)
		io_fd[0] = open_in_file(filename);
	else if (opt == DLESS)
		io_fd[0] = get_heredoc_fd(filename);
	if (io_fd[0] == -1)
		return (false);
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

	ret = false;
	if (pt == NULL)
		return (true);
	// if (pt->token_type == REDIRECTION_LIST)
	// {
	// 	ret = handle_heredoc_redir(pt->left, env);
	// 	if (ret == false)
	// 		return (ret);
	// 	ret = handle_heredoc_redir(pt->right, env);
	// 	if (ret == false)
	// 		return (ret);
	// }
	if (pt->token_type == REDIRECTION_LIST)
	{
		if (!handle_other_redir(pt->left, env)
			|| !handle_other_redir(pt->right, env))
			return (false);
	}
	else if (pt->token_type == REDIRECTION_INFO && pt->left->token_type == DLESS)
	{
		word_lst = interprete_words(pt->right->contents, env);
		if (word_lst == NULL)
			return (false);
		ret = make_input(word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(word_lst);
		if (!ret)
			return (ret);
	}
	return (true);
}

int	handle_other_redir(t_tree_node *pt, t_envtree *env)
{
	int		ret;
	t_list	*word_lst;

	ret = false;
	if (pt == NULL)
		return (true);
	if (pt->token_type == REDIRECTION_LIST)
	{
		if (!handle_other_redir(pt->left, env)
			|| !handle_other_redir(pt->right, env))
			return (false);
	}
	else if (pt->token_type == REDIRECTION_INFO && pt->left->token_type != DLESS)
	{
		word_lst = interprete_words(pt->right->contents, env);
		if (word_lst == NULL)
			return (false);
		if (is_ambiguous(pt->right->contents->head->content, word_lst))
			return (false);
		ret = cknopen(word_lst->head->content, pt->fd, pt->left->token_type);
		ft_lstclear(word_lst);
		if (!ret)
			return (ret);
	}
	return (true);
}
