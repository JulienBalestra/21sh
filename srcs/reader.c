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
#include "libft.h"
#include "minishell.h"
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

t_term *create_link(t_term *prev)
{
	t_term *term;

	if ((term = (t_term *)malloc(sizeof(t_term))))
	{
		term->next = NULL;
		term->prev = prev;
		if (prev)
			prev->cursor = 0;
		term->cursor = 1;
		term->c = 0;
	}
	return (term);
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
	if ((str = ft_strnew((len))))
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

void free_term(t_term *term)
{
	t_term *tmp;

	while (term->next)
		term = term->next;
	while (term->prev)
	{
		tmp = term->prev;
		free(term);
		term = tmp;
	}
}

/*void reset_cursor(t_cline *line)
{
	int i;

	i = line->length + ft_strlen(PROMPT);
	while (i--)
	{
		ft_putstr_fd(tgetstr("le", NULL), 1);
		ft_putstr_fd(tgetstr("dc", NULL), 1);
	}
}*/

/*void restor_cursor(t_cline *cline)
{
	t_term *begin;

	if (!cline || !(begin = cline->last))
		return ;
	while (begin->next)
		begin = begin->next;
	while (begin)
	{
		if (begin->cursor)
			break ;
		ft_putstr_fd(tgetstr("le", NULL), 1);
		begin = begin->prev;
	}
}*/

void cpy_restor_cursor(t_term *term)
{
	/*if (!cline || !(term))
		return ;*/
	while (term->next)
		term = term->next;
	while (term)
	{
		if (term->cursor == 1)
			break ;
		ft_putstr_fd(tgetstr("le", NULL), 1);
		term = term->prev;
	}
}

void 	cpy_reset_cursor(size_t len)
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
	char *buf;
	t_term *term;

	buf = NULL;
	if ((term = create_link(NULL)))
	{
		cpy_reset_cursor(get_columns());
		display_prompt(shell, ps2);
		raw_terminal_mode(shell);
		while (read(0, &term->c, sizeof(long)))
		{
			ft_putchar((char)term->c);
			term->next = create_link(term);
			term = term->next;
			if (term->prev->c == '\n')
				break;
		}
		buf = tterm_to_str(term);
		cpy_reset_cursor(ft_strlen(buf) + len_prompt(shell));
		free_term(term);
		default_terminal_mode(shell);
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
