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
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

char *get_eof(char *s)
{
	char *eof;
	char *tmp;
	int i;
	int k;

	i = 0;
	while (s[i] == ' ')
		i++;
	k = i;
	while (s[i] && s[i] != ' ')
		i++;
	tmp = ft_strndup(&s[k], (size_t)i - 1);
	eof = ft_strjoin(tmp, "\n");
	ft_strdel(&tmp);
	return (eof);
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

int is_warning_eof(char *line, char *entry, char *eof)
{
	if (! line)
	{
		ft_putstr_fd("warning: here-document at line 7 delimited by end-of-file ", 2);
		ft_putstr_fd("(wanted `", 2);
		eof[ft_strlen(eof) - 1] = '\0';
		ft_putstr_fd(eof, 2);
		ft_putstr_fd("')\n", 2);
		ft_strdel(&entry);
		return (1);
	}
	return (0);
}

char *build_eof_entry(char *eof)
{
	char *line;
	char *entry;
	char *tmp;

	line = NULL;
	entry = NULL;
	while (! line || ft_strcmp(line, eof) != 0)
	{
		ft_putstr("> ");
		if (entry)
		{
			tmp = entry;
			entry = ft_strjoin(tmp, line);
			ft_strdel(&tmp);
			ft_strdel(&line);
		}
		else
			entry = line;
		line = get_line(NULL);
		if (is_warning_eof(line, entry, eof))
			break;
	}
	ft_strdel(&line);
	ft_strdel(&eof);
	return (entry);
}

char **build_eof_tab(char *entry)
{
	char **eof_tab;

	if ((eof_tab = (char **)malloc(sizeof(char *) * 2)))
	{
		eof_tab[0] = ft_strdup(entry);
		eof_tab[1] = NULL;
	}
	return (eof_tab);
}