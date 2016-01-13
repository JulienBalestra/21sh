#include "../includes/ast.h"
#include "../libft/includes/libft.h"
#include <stdlib.h>

void ast_clean(t_ast *ast)
{
	if (ast->left)
		ast_clean(ast->left);
	if (ast->right)
		ast_clean(ast->right);
	if (ast->cmd)
		ft_str2del(ast->cmd);
	free(ast);
}