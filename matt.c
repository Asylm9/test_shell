/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:10:00 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/10 18:07:59 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	print_token(t_token *tok_lst)
{
	int	i;

	i = 1;
	while (tok_lst)
	{
		if (tok_lst->value != NULL)
			printf("Token %d type : %d value : %s\n", i, tok_lst->type,
				tok_lst->value);
		if (tok_lst->expand == EXPAND && tok_lst->value != NULL)
			printf("Token %d expand : EXPAND\n", i);
		else if (tok_lst->expand == NO_EXPAND)
			printf("Token %d expand : NO_EXPAND\n", i);
		tok_lst = tok_lst->next;
		i++;
	}
}

// int	count_cmds(t_token *tok_lst)
// {
// 	int	count;
//
// 	count = 0;
// 	while (tok_lst)
// 	{
// 		if (tok_lst->type == COMMAND)
// 			count++;
// 		tok_lst = tok_lst->next;
// 	}
// 	return (count);
// }
//
// int	parse_ast(t_token *tok_lst, t_ast *ast)
// {
// 	t_ast	*new_ast;
// 	int		arg_count;
// 	int		i;
// 	char	**new_args;
//
// 	arg_count = count_cmds(tok_lst);
// 	if (arg_count > 0)
// 	{
// 		ast->cmd = malloc(sizeof(t_command));
// 		if (!ast->cmd)
// 			return (1);
// 	}
// 	else
// 		ast->cmd = NULL;
// 	while (tok_lst)
// 	{
// 		if (tok_lst->type == COMMAND)
// 		{
// 			ast->cmd->cmd_name = strdup(tok_lst->value);
// 			if (!ast->cmd->cmd_name)
// 				return (1);
// 			ast->type = COMMAND;
// 		}
// 		else if (tok_lst->type == ARGUMENT)
// 		{
// 			if (ast->cmd->args == NULL)
// 			{
// 				ast->cmd->args = malloc(sizeof(char *) * 2);
// 				if (!ast->cmd->args)
// 					return (1);
// 				ast->cmd->args[0] = ft_strdup(tok_lst->value);
// 				if (!ast->cmd->args[0])
// 					return (1);
// 				ast->cmd->args[1] = NULL;
// 			}
// 			else
// 			{
// 				for (i = 0; ast->cmd->args[i]; i++)
// 					;
// 				new_args = realloc(ast->cmd->args, sizeof(char *) * (i + 2));
// 				if (!new_args)
// 					return (1);
// 				new_args[i] = strdup(tok_lst->value);
// 				if (!new_args[i])
// 					return (1);
// 				new_args[i + 1] = NULL;
// 				ast->cmd->args = new_args;
// 			}
// 		}
// 		else if (tok_lst->type == PIPE)
// 		{
// 			if (ast->right == NULL)
// 			{
// 				ast->right = malloc(sizeof(t_ast));
// 				if (!ast->right)
// 					return (1);
// 				ast->right->type = PIPE;
// 				ast->right->cmd = NULL;
// 				ast->right->left = NULL;
// 				ast->right->right = NULL;
// 			}
// 			else
// 			{
// 				new_ast = malloc(sizeof(t_ast));
// 				if (!new_ast)
// 					return (1);
// 				new_ast->type = PIPE;
// 				new_ast->cmd = NULL;
// 				new_ast->left = ast->right;
// 				new_ast->right = NULL;
// 				ast->right = new_ast;
// 			}
// 		}
// 		else if (tok_lst->type == REDIR_IN || tok_lst->type == REDIR_OUT
// 			|| tok_lst->type == REDIR_APPEND || tok_lst->type == REDIR_HEREDOC)
// 		{
// 			if (ast->right == NULL)
// 			{
// 				ast->right = malloc(sizeof(t_ast));
// 				if (!ast->right)
// 					return (1);
// 				ast->right->type = tok_lst->type;
// 				ast->right->cmd = NULL;
// 				ast->right->left = NULL;
// 				ast->right->right = NULL;
// 			}
// 			else
// 			{
// 				new_ast = malloc(sizeof(t_ast));
// 				if (!new_ast)
// 					return (1);
// 				new_ast->type = tok_lst->type;
// 				new_ast->cmd = NULL;
// 				new_ast->left = ast->right;
// 				new_ast->right = NULL;
// 				ast->right = new_ast;
// 			}
// 		}
// 		tok_lst = tok_lst->next;
// 	}
// 	printf("AST created successfully.\n");
// 	return (0);
// }
//
// void	print_ast(t_ast *ast)
// {
// 	printf("Type: %d\n", ast->type);
// 	if (!ast)
// 		return ;
// 	if (ast->type == COMMAND && ast->cmd)
// 	{
// 		if (ast->cmd->cmd_name == NULL)
// 			printf("Command name: NULL\n");
// 		else
// 			printf("Command name: %s\n", ast->cmd->cmd_name);
// 		if (ast->cmd->args)
// 		{
// 			printf("Arguments:\n");
// 			for (int i = 0; ast->cmd->args[i]; i++)
// 				printf("  Arg %d: %s\n", i + 1, ast->cmd->args[i]);
// 		}
// 		else
// 			printf("No arguments\n");
// 	}
// 	else if (ast->type == PIPE)
// 		printf("Pipe\n");
// 	else if (ast->type == REDIR_IN)
// 		printf("Redirect In\n");
// 	else if (ast->type == REDIR_OUT)
// 		printf("Redirect Out\n");
// 	else if (ast->type == REDIR_APPEND)
// 		printf("Redirect Append\n");
// 	else if (ast->type == REDIR_HEREDOC)
// 		printf("Redirect Heredoc\n");
// 	if (ast->left)
// 		print_ast(ast->left);
// 	else
// 		printf("No left child\n");
// 	printf("Right child:\n");
// 	printf("ast right value: %p\n", (void *)ast->right);
// 	if (ast->right->cmd)
// 		print_ast(ast->right);
// 	else
// 		printf("No right child\n");
// }

void	free_tok_lst(t_token *list)
{
	t_token	*temp;

	while (list->next)
	{
		temp = list->next;
		list->next = temp->next;
		free(temp->value);
		free(temp);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tok_lst;
	t_token	*temp;
	t_ast	*ast;

	if (ac > 1)
	{
		fprintf(stderr, "Usage: %s\n", av[0]);
		return (1);
	}
	while (1)
	{
		input = readline("Minishell> ");
		add_history(input);
		printf("Input: %s\n", input);
		if (create_token_list(&tok_lst))
		{
			free(input);
			return (1);
		}
		printf("Token list created successfully.\n");
		if (tokenize_input(tok_lst, input))
		{
			// FREE TOK_LST
			free(input);
			return (1);
		}
		printf("Tokenization successful.\n");
		free(input);
		print_token(tok_lst);
		temp = expand_list(tok_lst, envp);
		print_token(temp);
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			perror("malloc");
			free(tok_lst);
			return (1);
		}
		free_tok_lst(tok_lst);
		free_tok_lst(temp);
		// free(input);
		// parse_ast(tok_lst, ast);
		printf("AST:\n");
		// printf("%d\n", execve("/bin/ls", (char *[]){"ls", "-l", NULL},
		// NULL));
		// print_ast(ast);
	}
}

// execve("/bin/cat", args, NULL);

// export plusieurs variables d'environnement d'un coup
// pour les binaires 1 string par flag

/*
	Parse()
		Readline()
		Tokenize()
			Create_tok_lst()
				Init_token()
				Add_token()
			Fill_token()
		Expand_tok_lst()
			Expand_token()
				Expand_var()
		Create_AST()
			Count_pipes()
			Create_pipes_nodes()
				Init_pipe_node()
			Create_cmd_nodes()
				Init_cmd_node()
				Fill_cmd()
*/