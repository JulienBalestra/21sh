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
#include <term.h>
#include <sys/ioctl.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	*compile(char *left, char *buf)
{
	char	*tmp;

	tmp = buf;
	buf = ft_strjoin(left, buf);
	free(tmp);
	ft_strdel(&left);
	return (buf);
}

void	again(char *buf)
{
	ft_strclr(buf);
}

char	*move_and_clean(char *buf)
{
	char	*left;

	left = ft_strdup(buf);
	ft_strclr(buf);
	return (left);
}

void	signal_callback_handler(int sig_num)
{
	char	*wd;

	(void)sig_num;
	ft_putchar('\n');
	if (USE_CWD && (wd = create_cwd(NULL)))
	{
		ft_putstr(wd);
		ft_strdel(&wd);
		write(1, "> ", 2);
	}
	else
		ft_putstr(PROMPT);
}

t_term *create_link(void)
{
	t_term *link;

	if ((link = (t_term *)malloc(sizeof(t_term))))
	{
		link->next = NULL;
		link->prev = NULL;
		link->cursor = 0;
		link->c = 0;
	}
	return (link);
}

char *tterm_to_str(t_term *term)
{
	size_t len;
	char *str;
	int i;

	len = 0;
	while (term->next)
		term = term->next;
	while (term->prev)
	{
		term = term->prev;
		len++;
	}
	if ((str = ft_strnew((len + 1))))
	{
		i = 0;
		while (term->next)
		{
			str[i] = (char)term->c;
			i++;
			term = term->next;
		}
	}
	return (str);
}

void safe_free_term(t_term *term)
{
	t_term *tmp;

	if (term)
	{
		while (term->next)
			term = term->next;
		while (term)
		{
			tmp = term->prev;
			term->cursor = 0;
			term->c = 0;
			free(term);
			term = tmp;
		}
	}
}

void 	reset_cursor(size_t len)
{
	char *le;
	char *dc;

	while(len)
	{
		le = tgetstr("le", NULL);
		dc = tgetstr("dc", NULL);
		if (! le || ! dc)
			return;
		ft_putstr_fd(le, 1);
		ft_putstr_fd(dc, 1);
		len--;
	}
}

size_t			get_columns(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

char 	*get_line_from_user(t_sh *shell, int ps2)
{
	char 	*buf;
	long	key;
	t_term *end;

	buf = NULL;
	key = 0;
	if ((end = create_link()))
	{
		reset_cursor(get_columns());
		display_prompt(shell, ps2);
		raw_terminal_mode(shell);
		end->cursor = 1;
		end->c = '\n';
		while (read(0, &key, sizeof(long)))
		{
			if (tc_continue_process_key(shell, end, key) == 0)
				break;
			key = 0;
		}
		buf = tterm_to_str(end);
		reset_cursor(ft_strlen(buf) + len_prompt(shell));
		safe_free_term(end); //TODO
		default_terminal_mode(shell);
		display_prompt(shell, ps2);
		ft_putendl(buf);
		if (! buf || buf[0] == '\0')
		{
			ft_strdel(&buf);
			return get_line_from_user(shell, ps2);
		}
	}
	return (buf);
}

char	*get_line_from_pipe(t_sh *shell)
{
	char	*buf;
	char	*left;
	ssize_t	ret;

	buf = ft_strnew(READ);
	left = NULL;
	signal(SIGINT, signal_callback_handler);
	while ((ret = read(0, buf, READ)))
	{
		buf[ret] = '\0';
		if (left && buf[0])
			buf = compile(left, buf);
		if (is_real_line(buf))
			return (buf);
		else if (is_enter(buf))
			again(buf);
		else
			left = move_and_clean(buf);
	}
	if (left)
		free(left);
	free(buf);
	if (shell)
		shell->exit = 1;
	return (NULL);
}

char	*get_line(t_sh *shell, int ps2)
{
	if (isatty(0))
		return get_line_from_user(shell, ps2);
	else
		return get_line_from_pipe(shell);
}
