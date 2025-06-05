#include "minishell.h"

int	init_struct_pipe(t_ast *first_node)
{
	t_command	*cmd;
	t_command	*cmd_second;
	t_ast		*cmd_ast;
	t_ast		*cmd_second_ast;

	if (!first_node)
		return (1);
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	cmd->cmd_name = "ls";
	cmd->args = malloc(3 * sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (1);
	}
	cmd->args[0] = "ls";
	cmd->args[0] = "-l";
	cmd->args[1] = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	cmd_second = malloc(sizeof(t_command));
	if (!cmd_second)
	{
		free(cmd);
		return (1);
	}
	cmd_second->cmd_name = "wc";
	cmd_second->args = malloc(3 * sizeof(char *));
	if (!cmd_second->args)
	{
		free(cmd);
		free(cmd_second);
		return (1);
	}
	cmd_second->args[0] = "wc";
	cmd_second->args[1] = "-l";
	cmd_second->args[2] = NULL;
	cmd_second->redirections = NULL;
	cmd_second->next = NULL;
	cmd_ast = malloc(sizeof(t_ast));
	if (!cmd_ast)
	{
		free(cmd);
		free(cmd_second);
		return (1);
	}
	cmd_ast->type = WORD;
	cmd_ast->cmd = cmd;
	cmd_ast->left = NULL;
	cmd_ast->right = NULL;
	cmd_second_ast = malloc(sizeof(t_ast));
	if (!cmd_second_ast)
	{
		free(cmd);
		free(cmd_second);
		free(cmd_ast);
		return (1);
	}
	cmd_second_ast->type = WORD;
	cmd_second_ast->cmd = cmd_second;
	cmd_second_ast->left = NULL;
	cmd_second_ast->right = NULL;
	first_node->type = PIPE;
	first_node->cmd = NULL;
	first_node->left = cmd_ast;
	first_node->right = cmd_second_ast;
	return (0);
}

int	init_struct_double_pipe(t_ast *first_node)
{
	t_command	*cmd;
	t_command	*cmd_second;
	t_command	*cmd_third;
	t_ast		*cmd_first_ast;
	t_ast		*cmd_second_ast;
	t_ast		*cmd_third_ast;
	t_ast		*second_node;

	if (!first_node)
		return (1);
	// First cmd
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (1);
	cmd->cmd_name = "ls";
	cmd->args = malloc(3 * sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (1);
	}
	cmd->args[0] = "ls";
	cmd->args[1] = "-l";
	cmd->args[2] = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	// Second cmd
	cmd_second = malloc(sizeof(t_command));
	if (!cmd_second)
	{
		free(cmd);
		return (1);
	}
	cmd_second->cmd_name = "wc";
	cmd_second->args = malloc(3 * sizeof(char *));
	if (!cmd_second->args)
	{
		free(cmd);
		free(cmd_second);
		return (1);
	}
	cmd_second->args[0] = "wc";
	cmd_second->args[1] = "-l";
	cmd_second->args[2] = NULL;
	cmd_second->redirections = NULL;
	cmd_second->next = NULL;
	// Third cmd
	cmd_third = malloc(sizeof(t_command));
	if (!cmd_third)
	{
		free(cmd);
		free(cmd_second);
		return (1);
	}
	cmd_third->cmd_name = "grep";
	cmd_third->args = malloc(3 * sizeof(char *));
	if (!cmd_third->args)
	{
		free(cmd);
		free(cmd_second);
		free(cmd_third);
		return (1);
	}
	cmd_third->args[0] = "grep";
	cmd_third->args[1] = "test";
	cmd_third->args[2] = NULL;
	cmd_third->redirections = NULL;
	cmd_third->next = NULL;
	// First cmd ast
	cmd_first_ast = malloc(sizeof(t_ast));
	if (!cmd_first_ast)
	{
		free(cmd);
		free(cmd_second);
		return (1);
	}
	cmd_first_ast->type = WORD;
	cmd_first_ast->cmd = cmd;
	cmd_first_ast->left = NULL;
	cmd_first_ast->right = NULL;
	// Second cmd ast
	cmd_second_ast = malloc(sizeof(t_ast));
	if (!cmd_second_ast)
	{
		free(cmd);
		free(cmd_second);
		free(cmd_first_ast);
		return (1);
	}
	cmd_second_ast->type = WORD;
	cmd_second_ast->cmd = cmd_second;
	cmd_second_ast->left = NULL;
	cmd_second_ast->right = NULL;
	// Third cmd ast
	cmd_third_ast = malloc(sizeof(t_ast));
	if (!cmd_third_ast)
	{
		free(cmd);
		free(cmd_second);
		free(cmd_first_ast);
		free(cmd_second_ast);
		return (1);
	}
	cmd_third_ast->type = WORD;
	cmd_third_ast->cmd = cmd_third;
	cmd_third_ast->left = NULL;
	cmd_third_ast->right = NULL;
	// Second pipe node
	second_node = malloc(sizeof(t_ast));
	if (!second_node)
	{
		free(cmd);
		free(cmd_second);
		free(cmd_first_ast);
		free(cmd_second_ast);
		free(cmd_third_ast);
		return (1);
	}
	second_node->type = PIPE;
	second_node->cmd = NULL;
	second_node->left = cmd_second_ast;
	second_node->right = cmd_third_ast;
	// First pipe node
	first_node->type = PIPE;
	first_node->cmd = NULL;
	first_node->left = cmd_first_ast;
	first_node->right = second_node;
	return (0);
}

void	print_ast(t_ast *ast)
{
	printf("Type:\n");
	if (!ast)
		return ;
	if (ast->type == WORD && ast->cmd)
	{
		if (ast->cmd->cmd_name == NULL)
			printf("	Command:\n		Name: NULL\n");
		else
			printf("	Command:\n		Name: %s\n", ast->cmd->cmd_name);
		if (ast->cmd->args)
		{
			printf("		Arguments:\n");
			for (int i = 0; ast->cmd->args[i]; i++)
			{
				printf("			%s\n", ast->cmd->args[i]);
			}
		}
		else
			printf("No arguments\n");
	}
	else if (ast->type == PIPE)
		printf("	Pipe\n");
	else if (ast->type == REDIR_IN)
		printf("	Redirect In\n");
	else if (ast->type == REDIR_OUT)
		printf("	Redirect Out\n");
	else if (ast->type == REDIR_APPEND)
		printf("	Redirect Append\n");
	else if (ast->type == REDIR_HEREDOC)
		printf("	Redirect Heredoc\n");
	if (ast->left)
	{
		printf("Left child:\n");
		print_ast(ast->left);
	}
	// else
	// 	printf("No left child\n");
	if (ast->right)
	{
		printf("Right child:\n");
		print_ast(ast->right);
	}
	// else
	// 	printf("No right child\n");
}

int	main(void)
{
	t_ast *ast;
	t_ast *ast_double_pipe;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (1);
	ast_double_pipe = malloc(sizeof(t_ast));
	if (!ast_double_pipe)
	{
		free(ast);
		return (1);
	}

	if (init_struct_pipe(ast) != 0)
	{
		free(ast);
		return (1);
	}

	print_ast(ast);

	if (init_struct_double_pipe(ast_double_pipe) != 0)
	{
		free(ast);
		free(ast_double_pipe);
		return (1);
	}
	printf("\nDouble Pipe AST:\n");
	print_ast(ast_double_pipe);

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