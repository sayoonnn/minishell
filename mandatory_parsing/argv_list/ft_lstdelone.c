/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:29:15 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 20:54:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

void	ft_lstdelone(t_argv *argv, int status)
{
	if (!status)
		free(argv->content);
	free(argv);
}
