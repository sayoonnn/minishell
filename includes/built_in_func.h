/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:27:06 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 20:27:08 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_FUNC_H
# define BUILT_IN_FUNC_H

# include "env_tree.h"

int		ft_echo(char *arg[]);
int		ft_env(t_envnode *envp);
int		ft_export(t_envnode *env, char *str);
void	ft_exit(void);
int		ft_pwd(void);
int		ft_unset(t_envnode *env, char *str);

#endif
