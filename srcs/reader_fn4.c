/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:40 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:42 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	*join_pses(t_sh *shell, char *buf)
{
	char	*tmp;
	char	*buf_ps2;
	int		i;

	i = 0;
	while (buf && buf[i])
	{
		process_opened(shell->opened, buf[i]);
		i++;
	}
	if (is_something_opened(shell->opened))
	{
		mock_ps1_by_ps2(shell);
		tmp = buf;
		buf_ps2 = get_line(shell);
		buf = ft_strjoin(buf, buf_ps2);
		free(tmp);
		free(buf_ps2);
		update_ps1(shell);
	}
	return (buf);
}

int		is_valid_term(t_sh *shell)
{
	char	*term_buffer;
	char	*term;
	int		is_tgetent;

	is_tgetent = 0;
	if ((term = get_env_value("TERM", shell->env)))
	{
		if (starts_with("xterm", term) &&
			((term_buffer = (char *)malloc(sizeof(char) * TERM_SIZE))))
		{
			is_tgetent = tgetent(term_buffer, term);
			free(term_buffer);
		}
	}
	return (is_tgetent);
}

char	*eof_read_returner(t_sh *shell, char *buf)
{
	if (shell->close_program == 1)
	{
		shell->close_program = 0;
		return (NULL);
	}
	return (buf);
}
