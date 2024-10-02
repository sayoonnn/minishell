/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_argv_lst_to_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 21:48:16 by devpark           #+#    #+#             */
/*   Updated: 2023/12/29 22:19:57 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

static char	**make_string_array(t_list *argv_lst, int argv_cnt)
{
	char	**argvs;
	int		idx;
	t_node	*argv;
	t_node	*old;

	argvs = (char **)malloc(sizeof(char *) * (argv_cnt + 1));
	if (argvs == NULL)
		return (NULL);
	idx = 0;
	argv = argv_lst->head;
	while (argv != NULL)
	{
		old = argv;
		argvs[idx++] = argv->content;
		argv = argv->next;
		old->content = NULL;
		old->next = NULL;
		free(old);
	}
	argvs[idx] = NULL;
	free(argv_lst);
	return (argvs);
}

char	**convert_word_lst_to_array(t_list *contents, t_envtree *env)
{
	char	**argvs;
	int		argv_cnt;
	t_list	*argv_lst;

	argv_lst = interprete_words(contents, env);
	if (argv_lst == NULL)
		return (NULL);
	argv_cnt = ft_lstsize(argv_lst);
	argvs = make_string_array(argv_lst, argv_cnt);
	if (argvs == NULL)
	{
		ft_lstclear(argv_lst);
		free(argv_lst);
		return (NULL);
	}
	return (argvs);
}
