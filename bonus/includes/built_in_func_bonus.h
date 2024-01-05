/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:27:06 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:42:16 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_FUNC_BONUS_H
# define BUILT_IN_FUNC_BONUS_H

int		ft_cd(char *arg[]);
int		ft_echo(char *arg[]);
int		ft_env(t_envnode *envp);
int		ft_exit(char **argv, int is_pipe);
int		ft_export(char *arg[], t_envtree *env);
int		print_exports(t_envnode *tree);
void	add_value(t_envtree *env, char *key, char *value);
void	check_n_add(char *key, char *value, t_envtree *env);
int		check_is_valid(char *key);
int		ft_pwd(void);
int		ft_unset(t_envtree *env, char *arg[]);

#endif
