/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:37:01 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/02 12:43:25 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H
# include "parse_tree.h"
# include "env_tree.h"
# include "types.h"

# define WORD 0
# define QUOTE 1

extern int	g_errcode;

char	**ft_split_white(char const *s);
t_list	*expansion(char *str, t_envtree *env);
void	free_perfectly_split(char **strs);
int		ft_strjoin_in_depend(char **s1, char *content, size_t *s, size_t *idx);
t_list	*interprete_words(t_list *contents, t_envtree *env);
char	**convert_word_lst_to_array(t_list *contents, t_envtree *env);
void	update_quote_info(char ch, char *quote);
int		substitute_dollar(char *content, t_envtree *env, char **ref);
char	*remove_quote(char *str);
void	tokenize_and_add(t_deque *tmp, char *str);
int		is_there_white(char *str);
int		get_sublen(char *str, char cur);
void	sum_lst(t_list *dst, t_list *src);
int		substitute_dollar_heredoc(char *content, t_envtree *env, char **ref);
int		ft_strjoin_with_value(char **refine, char *value);

#endif
