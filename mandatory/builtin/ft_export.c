/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:21:01 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 20:21:02 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	tmp = ft_substr(str, 0, i);
	if (!tmp)
		exit(1);
	return (tmp);
}

static char	*get_value(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strchr(str, '+');
	if (!tmp)
		tmp = ft_strchr(str, '=');
	if (!tmp)
		return (NULL);
	ret = ft_substr(tmp, 0, ft_strlen(tmp));
	if (!ret)
		exit(1);
	return (ret);
}

static int	print_err_and_free(char *key, char *value)
{
	ft_printf(2, "minishell: export: `%s': %s\n", key, ERR_IDENIFIER);
	free(key);
	free(value);
	return (fail);
}

int	ft_export(char *arg[], t_envtree *env)
{
	char	*key;
	char	*value;
	int		ret;
	int		i;

	ret = success;
	if (arg[1] == NULL)
		return (print_exports(env->root));
	i = 0;
	while (arg[++i])
	{
		key = get_key(arg[i]);
		value = get_value(arg[i]);
		if (!check_is_valid(key))
		{
			ret = print_err_and_free(key, value);
			continue ;
		}
		check_n_add(key, value, env);
		free(key);
		if (value)
			free(value);
	}
	return (ret);
}
