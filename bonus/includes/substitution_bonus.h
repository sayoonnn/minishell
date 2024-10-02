/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:37:01 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:41:30 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_BONUS_H
# define SUBSTITUTION_BONUS_H
# include "parse_tree_bonus.h"
# include "env_tree_bonus.h"
# include "types_bonus.h"

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
int		substitute_dollar_heredoc(char *content, t_envtree *env, char **ref);
char	*remove_quote(char *str);
void	tokenize_and_add(t_deque *tmp, char *str);
int		is_there_white(char *str);
int		get_sublen(char *str, char cur);
void	sum_lst(t_list *dst, t_list *src);
t_list	*make_pattern_match_list(char *pattern);
int		is_there_wild(char *str);
t_list	*substitute_wilds(t_list *lst);
void	trim_quote(t_list *ret, char *str, int is_quoted, int *is_wild);
void	split_n_add(t_list *ret, char *str);
void	join_str_to_lastnode(t_list *res, char *str);
int		ft_strjoin_with_value(char **refine, char *value);

#endif
