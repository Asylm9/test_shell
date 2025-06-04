#include "minishell.h"

int	init_struct_pipe(t_ast *ast)
{
	t_command	*cmd;
	t_command	*cmd_deux;
	t_ast		*cmd_ast;
	t_ast		*cmd_deux_ast;

	if (!ast)
		return (1);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	cmd->cmd_name = "ls";
	cmd->args = "-l";
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd_deux = malloc(sizeof(t_command));
	if (!cmd_deux)
	{
		free(cmd);
		return (1);
	}
	cmd_deux->cmd_name = "wc";
	cmd_deux->args = "-l";
	cmd_deux->redirections = NULL;
	cmd_deux->next = NULL;
	cmd_ast = malloc(sizeof(t_ast));
	if (!cmd_ast)
	{
		free(cmd);
		free(cmd_deux);
		return (1);
	}
	cmd_ast->type = WORD;
	cmd_ast->cmd = cmd;
	cmd_ast->left = NULL;
	cmd_ast->right = NULL;
	cmd_deux_ast = malloc(sizeof(t_ast));
	if (!cmd_deux_ast)
	{
		free(cmd);
		free(cmd_deux);
		free(cmd_ast);
		return (1);
	}
	cmd_deux_ast->type = WORD;
	cmd_deux_ast->cmd = cmd_deux;
	cmd_deux_ast->left = NULL;
	cmd_deux_ast->right = NULL;
	ast->type = PIPE;
	ast->cmd = NULL;
	ast->left = cmd_ast;
	ast->right = cmd_deux_ast;
	return (0);
}
void	print_ast(t_ast *ast)
{
	printf("Type: %d\n", ast->type);
	if (!ast)
		return ;
	if (ast->type == WORD && ast->cmd)
	{
		if (ast->cmd->cmd_name == NULL)
			printf("Command name: NULL\n");
		else
			printf("Command name: %s\n", ast->cmd->cmd_name);
		if (ast->cmd->args)
		{
			printf("Arguments:\n");
			printf("  Arg : %s\n", ast->cmd->args);
		}
		else
			printf("No arguments\n");
	}
	else if (ast->type == PIPE)
		printf("Pipe\n");
	else if (ast->type == REDIR_IN)
		printf("Redirect In\n");
	else if (ast->type == REDIR_OUT)
		printf("Redirect Out\n");
	else if (ast->type == REDIR_APPEND)
		printf("Redirect Append\n");
	else if (ast->type == REDIR_HEREDOC)
		printf("Redirect Heredoc\n");
	if (ast->left)
		print_ast(ast->left);
	else
		printf("No left child\n");
	if (ast->right)
		print_ast(ast->right);
	else
		printf("No right child\n");
}

int	main(void)
{
	t_ast *ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (1);

	if (init_struct_pipe(ast) != 0)
	{
		free(ast);
		return (1);
	}

	print_ast(ast);
	// Free allocated memory
	if (ast->left && ast->left->cmd)
	{
		free(ast->left->cmd);
	}
	if (ast->right && ast->right->cmd)
	{
		free(ast->right->cmd);
	}
	free(ast->left);
	free(ast->right);
	free(ast);

	return (0);
}