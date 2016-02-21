/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:08 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:10 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int		is_enter(char *buf)
{
	if (buf && ft_strlen(buf) == 1 && buf[0] == '\n')
		return (1);
	return (0);
}

int		is_only_spaces(char *buf)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(buf);
	if (len == 1 && ! ft_isblank(buf[i]))
		return (1);
	while (i < len - 1)
	{
		if (ft_isblank(buf[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int		existing_line(t_sh *shell)
{
	if (shell->stdin_buf == NULL)
	{
		shell->close_program = 1;
		return (0);
	}
	else if (is_only_spaces(shell->stdin_buf))
	{
		//DEBUG
		ft_putstr_fd("only_spaces", shell->debug_fd);
		//DEBUG
		free(shell->stdin_buf);
		shell->stdin_buf = NULL;
		return (0);
	}
	return (1);
}

int		is_real_line(char *buf)
{
	size_t	len;
	size_t	i;

	i = 0;
	if ((len = ft_nstrlen(buf)))
	{
		while (buf[i] && buf[i] != '\n')
		{
			i++;
		}
		if (i == len - 1 && (buf[0] != '\n'))
			return (1);
	}
	return (0);
}
