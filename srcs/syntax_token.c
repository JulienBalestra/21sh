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

#include <stdlib.h>
#include "libft.h"
#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

int 		syn_semi_col(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == ';')
		{
			return (0);
		}
		if (i != 0 && str[i] == ';' && next_char_is(&str[i + 1], ';'))
		{
			return (0);
		}
		if (str[ft_strlen(str) - 1] == ';')
			return (0);
		i++;
	}
	return (1);
}

int			syn_right(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (i == 0 && str[i] == '>')
		{
			return (0);
		}
		if ( i < len - 2 && str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		{
			return (0);
		}
		if (str[len - 1] == '>')
			return (0);
		i++;
	}
	return (1);
}

int			syn_pipe(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (i == 0 && str[i] == '|')
		{
			return (0);
		}
		if (str[i] == '|' && next_char_is(&str[i + 1], '|'))
		{
			return (0);
		}
		if (str[len - 1] == '|')
			return (0);
		i++;
	}
	return (1);
}

int			syn_left(char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (i == 0 && str[i] == '<')
		{
			return (0);
		}
		if ( i < len - 2 && str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			return (0);
		}
		if (str[len - 1] == '<')
			return (0);
		i++;
	}
	return (1);
}