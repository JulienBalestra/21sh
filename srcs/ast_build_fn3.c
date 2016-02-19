/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 18:08:12 by jubalest          #+#    #+#             */
/*   Updated: 2016/01/21 18:08:13 by jubalest         ###   ########.fr       */
/*                                                                            */
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

/* ************************************************************************** */

void mock_ps1_by_ps2(t_sh *shell)
{
	ft_strdel(&shell->ps1);
	shell->ps1 = ft_strdup(DEFAULT_PS2);
	shell->len_ps1 = LEN_PS2;
}

char *join_free_start(char *start, char *end)
{
	char *tmp;

	tmp = start;
	start = ft_strjoin(start, end);
	ft_strdel(&tmp);
	return (start);
}

int skip_eof(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}
