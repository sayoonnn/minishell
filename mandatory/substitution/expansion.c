/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:30 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/04 15:38:31 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	get_sublen(char *str, char cur)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == cur && is_quote(cur))
			break ;
		else if (!is_quote(cur) && is_quote(*str))
			break ;
		str++;
		size++;
	}
	return (size);
}

void	add_to_lst(t_list *tmp, char *str)
{
	int		start;
	int		len;
	char	*sub_str;

	start = 0;
	while (*(str + start))
	{
		len = get_sublen(str + start + is_quote(*(str + start)), *(str + start));
		if (is_quote(*(str + start)))
			len += 2;
		sub_str = ft_substr(str, start, len);
		ft_lstadd_back(tmp, ft_lstnew(sub_str));
		start += len;
	}
}

t_list	*expansion(char *str, t_envtree *env)
{
	t_list	*word_split;
	t_list	*ret;
	t_node	*word;
	char	*refined;

	word_split = ft_lstcreate();
	ret = ft_lstcreate();
	add_to_lst(word_split, str);
	word = word_split->head;
	while (word != NULL)
	{
		refined = ft_strdup("");
		if (!substitute_dollar(word_split->head->content, env, &refined))
			exit(1);
		if (!remove_all_quotes(ret, &refined))
			exit(1);
		word = word->next;
	}
	ft_lstclear(word_split);
	free(word_split);
	return (ret);
}

int main()
{
	char *str = "'$A'\"$B\"$C$D'\"$F\"'";
	extern char	**environ;
	t_envtree *env = init_envp(environ);
	t_list *tmp = expansion(str, env);
	t_node *t = tmp->head;

	while (t != NULL)
	{
		printf("%s\n", t->content);
		t = t->next;
	}
}