/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:10:00 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/06 17:57:11 by magoosse         ###   ########.fr       */
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
		{
			tok_lst->type = PIPE;
			tok_lst->expand = NO_EXPAND;
		}
		else if (input[end] == '<')
		{
			if (input[end + 1] == '<')
			{
				tok_lst->type = REDIR_HEREDOC;
				end++;
			}
			else
				tok_lst->type = REDIR_IN;
			tok_lst->expand = NO_EXPAND;
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
			tok_lst->expand = NO_EXPAND;
		}
		else
		{
			tok_lst->type = WORD;
			if (input[end] == '\'' || !is_env_var(tok_lst->value))
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

char	*expand_var(char *str)
{
	int		i;
	char	*var;
	char	*result;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	var = ft_substr(str, 0, i);
	result = getenv(var + 1);
	free(var);
	return (result);
}

char	*expand_token(char *input)
{
	char	*result;
	char	*buffer;
	char	*tmp;
	int		pos;
	int		start;

	result = ft_calloc(1, 1);
	buffer = NULL;
	tmp = NULL;
	pos = 0;
	start = 0;
	while (input[pos] != '\0')
	{
		if (input[pos] == '$')
		{
			buffer = ft_substr(input, start, pos - start);
			if (tmp)
				free(tmp);
			tmp = ft_strjoin(result, buffer);
			free(buffer);
			buffer = expand_var(input + pos);
			if (buffer)
			{
				free(result);
				result = ft_strjoin(tmp, expand_var(input + pos));
			}
			pos++;
			while ((ft_isalnum(input[pos]) || input[pos] == '_') && input[pos])
				pos++;
			start = pos;
		}
		else
			pos++;
	}
	buffer = ft_substr(input, start, pos - start);
	if (is_env_var(input))
	{
		free(result);
		result = ft_strjoin(tmp, buffer);
	}
	else
	{
		free(result);
		free(tmp);
		return (buffer);
	}
	free(tmp);
	free(buffer);
	return (result);
}

t_token	*expand_list(t_token *tok_lst, char **env)
{
	t_token	*current;
	t_token	*head;
	char	*expanded_value;
	int		i;

	i = 0;
	current = malloc(sizeof(t_token));
	if (!current)
		return (NULL);
	head = current;
	while (tok_lst)
	{
		current->expand = NO_EXPAND;
		if (tok_lst->expand == NO_EXPAND)
		{
			current->value = ft_strdup(tok_lst->value);
			if (!current->value)
			{
				free(current);
				return (NULL);
			}
			current->type = tok_lst->type;
		}
		else
		{
			printf("%s test2\n", tok_lst->value);
			current->value = expand_token(tok_lst->value);
			current->type = tok_lst->type;
		}
		current->next = malloc(sizeof(t_token));
		current = current->next;
		tok_lst = tok_lst->next;
	}
	printf("Head value : %s\n", head->value);
	return (head);
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
	tok_lst = malloc(sizeof(t_token));
	if (!tok_lst)
	{
		perror("malloc");
		return (1);
	}
	tok_lst->next = NULL;
	// while (1)
	// {
	input = "test tout ca";
	// input = readline("Minishell> ");
	// add_history(input);
	printf("Input: %s\n", input);
	tokenize_input(tok_lst, input);
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
	// }
}

// execve("/bin/cat", args, NULL);

// export plusieurs variables d'environnement d'un coup
// pour les binaires 1 string par flag