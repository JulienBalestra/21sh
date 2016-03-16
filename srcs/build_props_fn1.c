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

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

t_env		*create_env_link(t_env *env, char *environ_entry)
{
	t_env	*link;
	int		len_until;

	if ((link = (t_env *)malloc(sizeof(t_env))))
	{
		len_until = len_to_char(environ_entry, '=');
		link->name = ft_strndup(environ_entry, (size_t)len_until);
		environ_entry = &environ_entry[len_until + 1];
		link->value = ft_strdup(environ_entry);
		link->next = NULL;
		if (env)
		{
			link->prev = env;
			env->next = link;
		}
		else
			link->prev = NULL;
		return (link);
	}
	return (NULL);
}

t_env		*build_env_list(char **environ)
{
	t_env	*env;

	env = NULL;
	if (ft_str2len(environ) == 0)
	{
		env = manage_empty_environ();
	}
	else
	{
		while (*environ)
		{
			if (ft_strncmp("OLDPWD", *environ, 6) != 0)
				env = create_env_link(env, *environ);
			environ++;
		}
	}
	return (get_start(env));
}

t_con		*create_console(void)
{
	t_con *console;

	if ((console = (t_con *)malloc(sizeof(t_con))))
	{
		console->total_lines = 1;
		console->line_position = 1;
		console->char_position = 0;
	}
	return (console);
}
