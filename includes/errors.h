/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:31:45 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/19 17:31:46 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_NO_DIR_FILE	"No such file or directory"
# define ERR_CMD_NOT_FOUND	"command not found"

# define CODE_CMD_NOT_FOUND 127
# define CODE_PERM_DENIED	126

extern int	errno;

#endif
