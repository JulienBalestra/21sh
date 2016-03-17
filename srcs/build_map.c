/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_props.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubalest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:31:14 by jubalest          #+#    #+#             */
/*   Updated: 2015/12/03 15:31:18 by jubalest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_bin *create_link(char *name)
{
	t_bin *link;

	if ((link = (t_bin *)malloc(sizeof(t_bin))))
	{
		link->next = NULL;
		link->prev = NULL;
		link->name = ft_strdup(name);
	}
	return (link);
}

int is_executable(char *dir, char *name)
{
	struct stat	*st;
	char *full;

	full = ft_strjoin(dir, name);
	if (full && (st = (struct stat *)malloc(sizeof(struct stat))))
	{
		if (stat(full, st) == 0)
		{
			if (S_ISDIR(st->st_mode))
			{
				free(st);
				free(full);
				return (0);
			}
		}
		free(st);
		free(full);
		return (1);
	}
	return (0);
}

void 	fetch_binaries(t_sh *shell, char *dir)
{
	struct dirent	*elt;
	DIR		*directory;
	t_bin *link;

	if ((directory = opendir(dir)))
	{
		while ((elt = readdir(directory)))
		{
			if (elt->d_name[0] != '.' && is_executable(dir, elt->d_name))
			{
				if (shell->map == NULL)
					shell->map = create_link(elt->d_name);
				else
				{
					link = create_link(elt->d_name);
					shell->map->next = link;
					link->prev = shell->map;
					shell->map = link;
				}
			}
		}
		closedir(directory);
	}
}

void 	build_map(t_sh *shell)
{
	char 	*path_value;
	int		cur_path_len;
	char	*directory;

	if ((path_value = get_env_value("PATH", shell->env)))
	{
		cur_path_len = -1;
		while (cur_path_len != 0 && path_value)
		{
			cur_path_len = len_to_char(path_value, ':');
			directory = ft_strndup(path_value, (size_t)cur_path_len);
			fetch_binaries(shell, directory);
			ft_strdel(&directory);
			if (path_value[cur_path_len] != '\0')
				path_value = &path_value[cur_path_len + 1];
			else
				break ;
		}
		while (shell->map->prev)
			shell->map = shell->map->prev;
		shell->map = merge_sort_list_recursive(shell->map, shell);
	}
}
