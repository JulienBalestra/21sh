/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:45:55 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:45:56 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

char	*pre_format(char *buf)
{
	char	*str1;
	char	*str2;

	ft_remove_endchar(buf, '\n');
	convert_chars(buf);
	str1 = ft_remove_useless(buf, ' ');
	ft_remove_endchar(str1, ';');
	str2 = ft_remove_useless(str1, ' ');
	ft_strdel(&str1);
	return (str2);
}

int		find_exploitable(char *str)
{
	if (!str)
		return (1);
	if (syn_semi_col(str) == 0)
		return (1);
	if (syn_right(str) == 0)
		return (2);
	if (syn_pipe(str) == 0)
		return (3);
	if (syn_left(str) == 0)
		return (4);
	return (0);
}

int		correct_syntax(t_sh *shell)
{
	char	*formatted;
	int		ret;

	formatted = pre_format(shell->stdin_buf);
	ret = find_exploitable(formatted);
	ft_strdel(&shell->stdin_buf);
	if (ret == 1)
		ft_putendl_fd("syntax error near unexpected token `;'", 2);
	else if (ret == 2)
		ft_putendl_fd("syntax error near unexpected token `>'", 2);
	else if (ret == 3)
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
	else if (ret == 4)
		ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	else
		shell->stdin_buf = formatted;
	if (ret)
	{
		ft_strdel(&formatted);
		shell->l_ret = 2;
	}
	return (ret);
}
