/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:44:45 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:44:46 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

void		display_prompt(t_sh *shell)
{
	if (shell->ps1)
		ft_putstr(shell->ps1);
	else
		write(1, DEFAULT_PS2, LEN_PS2);
}

void		display_command_not_found(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void		display_permission_denied(const char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void		display_is_directory(const char *command)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void		display_not_such(char *who, char *where)
{
	ft_putstr_fd(who, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(where, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
