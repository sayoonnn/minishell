/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:29:01 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/20 18:29:05 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static char	**insert_arr(char **dst, char **src, int idx)
{
	size_t	dst_len;
	size_t	src_len;
	int		i;
	int		j;
	char	*tmp;

	dst_len = ft_arrlen(dst);
	src_len = ft_arrlen(src);
	tmp = malloc(sizeof(char *) * (dst_len + src_len + 1));
	if (!tmp)
		exit(1);
	i = 0;
	while (i < idx)
		tmp[i] = dst[i++];
	j = 0;
	while (j < src_len)
		tmp[i++] = src[j++];
	free(dst[idx++]);
	while (idx < dst_len)
		tmp[i++] = dst[idx++];
	free(dst);
	free(src);
	return (tmp);
}

static char	*substitude_str(char *full, char *str, t_envtree *env)
{
	int		i;

	while (str[i] != 0 && str[i] != '\'' && str[i] != '"')

}

static void find_dollar(t_tree_node *root, t_envtree *env)
{
	size_t		i;
	size_t		j;
	int			in_sqoute;
	int			in_dqoute;
	char		**contents;

	i = 0;
	contents = root->contents;
	while (contents[i])
	{
		j = 0;
		while (contents[i][j])
		{
			if (contents[i][j] == '$' && !in_sqoute && !in_dqoute \
			&& contents[i][j + 1] != '?')
				root->contents = insert_arr(contents, );
			else if (contents[i][j] == '$' && !in_sqoute && in_dqoute \
			&& contents[i][j + 1] != '?')
				// 문자열 치환만
			else
			
			j++;
		}
		i++;
	}
}

void	sub_dollar(t_tree_node *root, t_envtree *env)
{
	if (!root)
		return ;
	if (root->token_type == CMD_INFO)
		// clghks
	else if (root->token_type == FILENAME)
		//clghks
	sub_dollar(root->left, env);
	sub_dollar(root->right, env);
}
