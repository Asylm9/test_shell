/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:10:00 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/04 21:20:46 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(t_token *tok_lst, const char *input)
{
	int		start;
	int		end;
	int		i;
	char	quote;

	start = 0;
	end = 0;
	while (input[start])
	{
		while (input[start] && input[start] == ' ')
			start++;
		if (input[start] == '\0')
			break ;
		end = start;
		while (input[end] && input[end] != ' ' && input[end] != '|'
			&& input[end] != '<' && input[end] != '>')
			end++;
		if (input[start] == '"' || input[start] == '\'')
		{
			quote = input[start++];
			while (input[end] && input[end] != quote)
				end++;
			if (input[end] == '\0')
				return (1);
		}
		tok_lst->value = ft_substr(input, start, end - start);
		if (!tok_lst->value)
			return (1);
		if (input[end] == '|')
			tok_lst->type = PIPE;
		else if (input[end] == '<')
		{
			if (input[end + 1] == '<')
			{
				tok_lst->type = REDIR_HEREDOC;
				end++;
			}
			else
				tok_lst->type = REDIR_IN;
		}
		else if (input[end] == '>')
		{
			if (input[end + 1] == '>')
			{
				tok_lst->type = REDIR_APPEND;
				end++;
			}
			else
				tok_lst->type = REDIR_OUT;
		}
		else
		{
			tok_lst->type = WORD;
			if (input[end] == '\'')
				tok_lst->expand = NO_EXPAND;
			else
				tok_lst->expand = EXPAND;
		}
		tok_lst->next = malloc(sizeof(t_token));
		if (!tok_lst->next)
			return (1);
		i = end;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		tok_lst = tok_lst->next;
		start = end + 1;
	}
	tok_lst->next = NULL;
	return (0);
}

int	expand_token(t_token *tok_lst, char **env)
{
	// This function would handle the expansion of tokens based on the environment variables.
	// For now, we will just return 0 to indicate success.
	(void)tok_lst;
	(void)env;
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

// 	count = 0;
// 	while (tok_lst)
// 	{
// 		if (tok_lst->type == COMMAND)
// 			count++;
// 		tok_lst = tok_lst->next;
// 	}
// 	return (count);
// }

// int	parse_ast(t_token *tok_lst, t_ast *ast)
// {
// 	t_ast	*new_ast;
// 	int		arg_count;
// 	int		i;
// 	char	**new_args;

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

int	main(int ac, char **av)
{
	const char	*input;
	t_token		*tok_lst;
	t_ast		*ast;

	if (ac > 1)
	{
		fprintf(stderr, "Usage: %s\n", av[0]);
		return (1);
	}
	tok_lst = malloc(sizeof(t_token));
	if (!tok_lst)
	{
		perror("malloc");
		return (1);
	}
	tok_lst->next = NULL;
	while (1)
	{
		input = readline("Minishell> ");
		add_history(input);
		printf("Input: %s\n", input);
		tokenize_input(tok_lst, input);
		print_token(tok_lst);
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			perror("malloc");
			free(tok_lst);
			return (1);
		}
		// parse_ast(tok_lst, ast);
		printf("AST:\n");
		// print_ast(ast);
	}
}

// execve("/bin/cat", args, NULL);
