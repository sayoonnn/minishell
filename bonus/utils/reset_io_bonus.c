/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_io_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:32:49 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 13:22:47 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	reset_io(int save[2])
{
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	if (save[0] != 0)
		close(save[0]);
	if (save[1] != 1)
		close(save[1]);
}
