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
#include <unistd.h>
#include <signal.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

static	int g_catch_signal;
static	char *g_prompt;

void	signal_callback_handler(int sig_num)
{
	g_catch_signal = sig_num;
	if (isatty(0))
	{
		ft_putstr("^C\n");
		erase_line(get_columns());
		if (g_prompt)
			ft_putstr(g_prompt);
	}
}

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

char	*get_line_from_user(t_sh *shell)
{
	char	*buf;
	long	key;
	t_term	*end;

	buf = NULL;
	if ((end = create_term_link()))
	{
		init_current_console(shell, end);
		signal(SIGINT, signal_callback_handler);
		while (((key = 0)) || read(0, &key, sizeof(long)))
		{
			g_catch_signal = process_signal(shell, g_catch_signal, end);
			if (tc_continue_process_key(shell, end, key) == 0)
				break ;
		}
		buf = tterm_to_str(end);
		end_of_reading(shell, buf);
		buf = join_pses(shell, buf);
		if (!buf || buf[0] == '\0' || is_only_spaces(buf))
			return (recurse_get_line(shell, buf, end));
		add_to_history(shell, end);
	}
	return (process_if_exist(shell, buf));
}

char	*get_line_from_user_eof(t_sh *shell)
{
	char	*buf;
	long	key;
	t_term	*end;

	buf = NULL;
	if ((end = create_term_link()))
	{
		init_current_console(shell, end);
		g_catch_signal = 0;
		g_prompt = shell->ps1;
		signal(SIGINT, signal_callback_handler);
		while (((key = 0)) || read(0, &key, sizeof(long)))
		{
			g_catch_signal = process_signal(shell, g_catch_signal, end);
			if (tc_continue_process_key(shell, end, key) == 0)
				break ;
		}
		buf = tterm_to_str(end);
		end_of_reading(shell, buf);
	}
	if (shell->close_program == 1)
	{
		shell->close_program = 0;
		return (NULL);
	}
	return (buf);
}

char	*get_line_from_pipe(t_sh *shell)
{
	char	*buf;
	char	*left;
	ssize_t	ret;
	int		limit;

	buf = ft_strnew(READ);
	left = NULL;
	limit = 0;
	while ((ret = read(0, buf, READ)) && limit++ < MAX_READ)
	{
		buf[ret] = '\0';
		if (left && buf[0])
			buf = compile(left, buf);
		if (is_real_line(buf))
			return (buf);
		else if (is_enter(buf))
			again(buf);
		else if (is_print_buf(buf))
			left = move_and_clean(buf);
		else
			break ;
	}
	return (end_of_file_recvd(shell, buf, left, limit));
}

char	*get_line(t_sh *shell)
{
	char	term_buffer[TERM_SIZE];
	int		is_tgetent;

	is_tgetent = tgetent(term_buffer, get_env_value("TERM", shell->env));
	if (isatty(0) && is_tgetent)
	{
		g_catch_signal = 0;
		g_prompt = shell->ps1;
		if (shell->ddl_eof)
			return (get_line_from_user_eof(shell));
		return (get_line_from_user(shell));
	}
	else if (isatty(0) && shell->ddl_eof == 0)
		return (get_line_side_effect(shell));
	else
		return (get_line_from_pipe(shell));
}
