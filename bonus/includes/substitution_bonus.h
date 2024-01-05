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

extern int	g_errcode;

char	**ft_split_white(char const *s);
t_list	*expansion(char *str, t_envtree *env);
void	free_perfectly_split(char **strs);
int		ft_strjoin_in_depend(char **s1, char *content, size_t *s, size_t *idx);
int		remove_all_quotes(t_list *res, char **ref);
t_list	*interprete_words(t_list *contents, t_envtree *env);
char	**convert_word_lst_to_array(t_list *contents, t_envtree *env);
void	update_quote_info(char ch, char *quote);
int		substitute_dollar(char *content, t_envtree *env, char **ref);

#endif
