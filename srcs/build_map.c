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

void 	fetch_binaries(t_sh *shell, char *dir)
{
	struct dirent	*elt;
	DIR		*fd_file;
	t_bin *link;
	t_bin *start;

	fd_file = opendir(dir);
	//ft_putendl(dir);
	start = NULL;
	while ((elt = readdir(fd_file)))
	{
		if (elt->d_name && elt->d_name[0] != '.')
		{
			//ft_putendl(elt->d_name);
			if (start == NULL)
			{
				start = create_link(elt->d_name);
			}
			else
			{
				link = create_link(elt->d_name);
				start->next = link;
				link->prev = start;
				start = link;
			}
		}
		shell->map = start;
		/*while (start->prev)
		{
			start = start->prev;
		}
		shell->map = start;

		//merge_sort_list_recursive(shell->map, shell);

		while (shell->map->next)
		{
			ft_putendl(shell->map->name);
			shell->map = shell->map->next;
		}*/
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
	}
}
