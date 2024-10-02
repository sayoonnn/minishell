/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:20:32 by devpark           #+#    #+#             */
/*   Updated: 2024/01/02 13:51:41 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"
#include "errors.h"

int	select_parse_tree_token_type(int token_type)
{
	if (token_type == REDIRECTION)
		return (REDIRECTION_LIST);
	else if (token_type == REDIRECTION_LIST)
		return (REDIRECTION_INFO);
	return (token_type);
}

t_tree_node	*create_tree_node(int token_type)
{
	t_tree_node	*syntax_node;

	syntax_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (syntax_node == NULL)
		return (NULL);
	syntax_node->token_type = select_parse_tree_token_type(token_type);
	syntax_node->contents = NULL;
	syntax_node->left = NULL;
	syntax_node->right = NULL;
	syntax_node->fd[0] = 0;
	syntax_node->fd[1] = 1;
	return (syntax_node);
}
