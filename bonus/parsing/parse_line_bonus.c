/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 15:11:21 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

char	*print_token_type(int token_type)
{
	if (token_type == CMD)
		return ("CMD");
	else if (token_type == ARGV)
		return ("ARGV");
	else if (token_type == FILENAME)
		return ("FILENAME");
	else if (token_type == PIPE)
		return ("PIPELINE");
	else if (token_type == REDIRECTION)
		return ("REDIRECTION");
	else if (token_type == LIST)
		return ("LIST");
	else if (token_type == SUBSHELL)
		return ("SUBSHELL");
	else if (token_type == LPAREN)
		return ("LPAREN");
	else if (token_type == RPAREN)
		return ("RPAREN");
	else if (token_type == REDIRECTION_LIST)
		return ("REDIRECTION_LIST");
	else if (token_type == REDIRECTION_INFO)
		return ("REDIRECTION_INFO");
	else if (token_type == CMD_INFO)
		return ("CMD_INFO");
	else if (token_type == DLESS)
		return ("DLESS");
	else if (token_type == DGREAT)
		return ("DGREAT");
	else if (token_type == LESS)
		return ("LESS");
	else if (token_type == GREAT)
		return ("GREAT");
	else if (token_type == AND)
		return ("AND");
	else if (token_type == OR)
		return ("OR");
	return (NULL);
}

void	traverse_parse_tree(t_tree_node **root)
{
	if (*root == NULL)
		return ;
	printf("TOKEN_TYPE : %s\n", print_token_type((*root)->token_type));
	if ((*root)->token_type == SUBSHELL)
	{
		printf("(\n");
		traverse_parse_tree(&(*root)->mid);
		printf(")\n");
	}
	else if ((*root)->token_type == CMD_INFO)
	{
		t_node *ptr = (*root)->contents->head;
		while (ptr != NULL)
		{
			printf("%s ", ptr->content);
			ptr = ptr->next;
		}
		printf("\n");
	}
	if ((*root)->left)
		traverse_parse_tree(&(*root)->left);
	if ((*root)->right)
		traverse_parse_tree(&(*root)->right);
}

int	parse_line(char *line, t_parsing *parsing)
{
	int	flag;

	if (*line == 0)
		return (false);
	if (tokenize(line, parsing))
		exit(1);
	flag = analyze_syntax(&parsing->root, parsing);
	if (flag == 1)
		exit(1);
	if (flag == 258)
	{
		clean_parsing_tools(parsing);
		free(line);
		return (false);
	}
	return (true);
}
