#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "../includes/minishell.h"

int is_std_redirect(char *s, int i)
{
	if (s[i] == '>' && (s[i - 1] == '2' && s[i - 2] == ' '))
		return (2);
	return (0);
}

int is_operand(char *s, int i)
{
	if (s[i] == '|')
		return (1);
	if (s[i] == '>')
	{
		if (s[i - 1] == '>')
			return (2);
		return (3);
	}
	if (s[i] == '<')
	{
		if (s[i - 1] == '<')
			return (4);
		return (5);
	}
	return (0);
}

void find_operand(char *input, int *tuple)
{
	size_t 	len;
	int 	ret;

	len = ft_strlen(input) - 1;
	tuple[0] = -1;
	tuple[1] = -1;
	while (len)
	{
		ret = is_operand(input, (int)len);
		if (ret)
		{
			tuple[0] = ret;
			tuple[1] = (int)len;
			break;
		}
		len--;
	}
}

char **cut_input(char *input, int *tuple)
{
	char **cut;

	if ((cut = (char **)malloc(sizeof(char *) * 3)))
	{
		if (tuple[0] == 2 || tuple[0] == 4)
			cut[0] = ft_strndup(input, (size_t)tuple[1]-1);
		else
			cut[0] = ft_strndup(input, (size_t)tuple[1]);
		cut[1] = ft_strdup(&input[tuple[1]+1]);
		cut[2] = NULL;
	}
	return (cut);
}

t_ast *ast_build(char *input)
{
	t_ast	*ast;
	int 	tuple[2];
	char	**cut;
	char	*clean;

	if ((ast = (t_ast *)malloc(sizeof(t_ast))))
	{
		find_operand(input, tuple);
		ast->op = tuple[0];
		ast->stdin = 0;
		ast->stdout = 1;
		if (ast->op == -1)
		{
			clean = ft_remove_useless(input, ' ');
			ast->cmd = ft_lz_strsplit(clean, ' ');
			free(clean);
			ast->left = NULL;
			ast->right = NULL;
		}
		else
		{
			ast->cmd = NULL;
			cut = cut_input(input, tuple);
			ast->left = ast_build(cut[0]);
			ast->right = ast_build(cut[1]);
			/*if (ast->op == 4)
				ft_putstr("build eof\n");
			else
				ast->right = ast_build(cut[1]);*/
			free(cut);
		}
	}
	free(input);
	return (ast);
}
