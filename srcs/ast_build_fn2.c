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

void trigger_operator_with_recurse(t_ast *ast, char *input, int *tuple, t_sh *shell)
{
	char **cut;
	char *tmp;
	char *eof_entry;

	ast->cmd = NULL;
	cut = cut_input(input, tuple);
	if (ast->op == 4)
	{
		tmp = get_eof(cut[1]);
		eof_entry = build_eof_entry(tmp, shell);
		ast->left = ast_build(eof_entry, 1, shell);
		ast->right = ast_build(ft_strjoin(cut[0], &cut[1][skip_eof(cut[1])]), 0, shell);
		free(cut[0]);
		free(cut[1]);
	}
	else if (ast->op == 11)
	{
		tmp = cut[0];
		cut[0] = ft_strjoin(cut[0], " 2>&1 ");
		ft_strdel(&tmp);
		if (cut[1] && cut[1][0] == '&')
			cut[1][0] = ' ';
		ast->op = 1;
		ast->left = ast_build(cut[0], 0, shell);
		ast->right = ast_build(cut[1], 0, shell);
	}
	else
	{
		ast->left = ast_build(cut[0], 0, shell);
		ast->right = ast_build(cut[1], 0, shell);
	}
	free(cut);
}
/*
int 	catch_n_process_pipe_stderr(t_ast *ast, char *str, int index)
{
	if (ft_strcmp(str, "&") == 0)
	{
		ast->from = 2;
		ast->to = 1;
		ft_putstr("\nok\n");
		return (1);
	}
	return (0);
}*/

int 	catch_n_process_redirection(t_ast *ast, char *str)
{
	size_t i;
	size_t k;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0)
		return (0);
	if (str[i++] != '>')
		return (0);
	if (str[i++] != '&')
		return (0);
	k = i;
	if (str[i] == '-' && str[i + 1] == '\0')
	{
		ast->from = ft_atoi(str);
		ast->to = -1;
		return (1);
	}
	while (ft_isdigit(str[i]))
		i++;
	if (i < ft_strlen(str) || i == k )
		return (0);
	ast->from = ft_atoi(str);
	ast->to = ft_atoi(&str[k]);
	// TODO from / to are int *
	return (1);
}

void	manage_redirection(t_ast *ast)
{
	char **cmd;
	int i;
	size_t len;

	i = 0;
	cmd = ast->cmd;
	while (cmd && cmd[i])
	{
		if (catch_n_process_redirection(ast, ast->cmd[i]))
		{
			len = ft_str2len(cmd);
			ft_strdel(&cmd[i]);
			ft_str2defrag(cmd, len);
		}
		else
			i++;
	}
}

void trigger_command(t_ast *ast, char *input, int eof)
{
	char *tmp;

	if (eof)
		ast->cmd = build_eof_tab(input);
	else
	{
		tmp = ft_remove_useless(input, ' ');
		ast->cmd = ft_lz_strsplit(tmp, ' ');
		manage_redirection(ast);
		free(tmp);
	}
	ast->left = NULL;
	ast->right = NULL;
}