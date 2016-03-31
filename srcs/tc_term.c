/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:53:35 by jubalest          #+#    #+#             */
/*   Updated: 2016/03/31 14:53:36 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_term	*create_term_link(void)
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

char	*tterm_to_str(t_term *term)
{
	size_t	len;
	char	*str;
	int		i;

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
		while (term)
		{
			str[i] = (char)term->c;
			i++;
			term = term->next;
		}
	}
	return (str);
}

void	safe_free_term(t_term *term)
{
	t_term	*tmp;

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

size_t	get_columns(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}
