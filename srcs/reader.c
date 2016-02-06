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

void	again(char *buf, t_sh *shell)
{
	if (isatty(0) && shell)
		display_prompt(shell);
	else if (isatty(0))
		ft_putstr("> ");
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
		term->c = 0;
		term->cursor = 0;
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

char 	*get_line_from_user(t_sh *shell)
{
	char *buf;
	t_term *term;

	buf = NULL;
	if ((term = create_link(NULL)))
	{
		display_prompt(shell);
		raw_terminal_mode();
		while (read(0, &term->c, 1))
		{
			ft_putchar((char)term->c);
			term->next = create_link(term);
			term = term->next;
			if (term->prev->c == '\n')
				break;
		}
		default_terminal_mode();
		buf = tterm_to_str(term);
		free_term(term);
	}
	return (buf);
}

char	*get_line_from_pipe(t_sh *shell)
{
	char	*buf;
	char	*left;
	ssize_t	ret;

	if (isatty(0) && shell)
		display_prompt(shell);
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
			again(buf, shell);
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

char	*get_line(t_sh *shell)
{
	if (isatty(0))
		return get_line_from_user(shell);
	else
		return get_line_from_pipe(shell);
}
