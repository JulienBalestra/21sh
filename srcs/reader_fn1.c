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
	if (isatty(0))
		ft_putstr("^C");
	ft_putchar('\n');
	if (isatty(0))
		erase_line(get_columns());
	if (USE_CWD && (wd = create_cwd(NULL)))
	{
		ft_putstr(wd);
		ft_strdel(&wd);
		ft_putstr(END_PROMPT);
	}
	else
		ft_putstr(DEFAULT_PS1);
	if (isatty(0))
	{

	}
}