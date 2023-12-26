/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitude.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:37:01 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 22:37:02 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUDE_H
# define SUBSTITUDE_H

#include "minishell.h"

int		substitute_words(t_parsing *parsing, t_envtree *env, t_list *contents);
char	**convert_word_lst_to_array(t_list *lst);
int		substitute_words(t_parsing *parsing, t_envtree *env, t_list *contents);
int		convert_content_to_argv(t_parsing *ps, t_envtree *env, t_list *contents);
int		handle_special_dollar(t_parsing *parsing, char *word, size_t *idx);
int		handle_dollar_in_qts(t_parsing *ps, t_envtree *env, char *word, size_t *idx);
int		handle_dollar_in_wd(t_parsing *ps, t_envtree *env, char *word, size_t *idx);
int		handle_wd(t_parsing *ps, t_envtree *env, char *word, size_t *idx);
int		handle_word_with_qts(t_parsing *ps, t_envtree *env, char *word, size_t *idx);
int		free_new_word(char *word);
int		link_argv(t_parsing *parsing, char *argv);
int		link_argv_to_word_lst(t_parsing *parsing, char **strs, char *value);

#endif
