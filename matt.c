#include "minishell.h"

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_token_type;

typedef struct s_token	t_token;
typedef struct s_ast	t_ast;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	t_token				*next;
}						t_token;

typedef struct s_ast
{
	t_token_type		type;
	// char				**cmd;
	t_command			*cmd;
	t_ast				*left;
	t_ast				*right;
}						t_ast;

int	tokenize_input(t_token *tok_lst, const char *input)
{
	int	start;
	int	end;
	int	i;
	int	first_word;

	first_word = 1;
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
		tok_lst->value = ft_substr(input, start, end - start);
		if (!tok_lst->value)
			return (1);
		if (input[end] == '|')
		{
			tok_lst->type = PIPE;
			first_word = 1;
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
			if (first_word)
			{
				tok_lst->type = COMMAND;
				first_word = 0;
			}
			else
				tok_lst->type = ARGUMENT;
		}
		tok_lst->next = malloc(sizeof(t_token));
		if (!tok_lst->next)
			return (1);
		i = end;
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		// while (input[end] && input[end] == ' ')
		// 	end++;
		if (input[end] != '\0')
			tok_lst = tok_lst->next;
		start = end + 1;
	}
	tok_lst->next = NULL;
	return (0);
}

void	print_token(t_token *tok_lst)
{
	int	i;

	i = 1;
	while (tok_lst)
	{
		if (tok_lst->value == NULL)
			printf("Token %d type : %d value : NULL\n", i, tok_lst->type);
		else
			printf("Token %d type : %d value : %s\n", i, tok_lst->type,
				tok_lst->value);
		tok_lst = tok_lst->next;
		i++;
	}
}

int	count_cmd_args(t_token *tok_lst)
{
	int	count;

	count = 0;
	while (tok_lst)
	{
		if (tok_lst->type == COMMAND || tok_lst->type == ARGUMENT)
			count++;
		tok_lst = tok_lst->next;
	}
	return (count);
}

int	parse_ast(t_token *tok_lst, t_ast *ast)
{
	int		i;
	t_ast	*new_ast;
	int		arg_count;

	i = 0;
	arg_count = count_cmd_args(tok_lst);
	if (arg_count > 0)
	{
		ast->cmd = malloc(sizeof(t_command));
		if (!ast->cmd)
			return (1);
		ast->cmd = NULL;
	}
	else
		ast->cmd = NULL;
	while (tok_lst)
	{
		if (tok_lst->type == COMMAND)
		{
			ast->cmd->cmd_name = strdup(tok_lst->value);
			if (!ast->cmd->cmd_name)
				return (1);
			ast->type = COMMAND;
			i++;
		}
		else if (tok_lst->type == PIPE)
		{
			if (ast->right == NULL)
			{
				ast->right = malloc(sizeof(t_ast));
				if (!ast->right)
					return (1);
				ast->right->type = PIPE;
				ast->right->cmd = NULL;
				ast->right->left = NULL;
				ast->right->right = NULL;
			}
			else
			{
				new_ast = malloc(sizeof(t_ast));
				if (!new_ast)
					return (1);
				new_ast->type = PIPE;
				new_ast->cmd = NULL;
				new_ast->left = ast->right;
				new_ast->right = NULL;
				ast->right = new_ast;
			}
		}
		else if (tok_lst->type == REDIR_IN || tok_lst->type == REDIR_OUT
			|| tok_lst->type == REDIR_APPEND || tok_lst->type == REDIR_HEREDOC)
		{
			if (ast->right == NULL)
			{
				ast->right = malloc(sizeof(t_ast));
				if (!ast->right)
					return (1);
				ast->right->type = tok_lst->type;
				ast->right->cmd = NULL;
				ast->right->left = NULL;
				ast->right->right = NULL;
			}
			else
			{
				new_ast = malloc(sizeof(t_ast));
				if (!new_ast)
					return (1);
				new_ast->type = tok_lst->type;
				new_ast->cmd = NULL;
				new_ast->left = ast->right;
				new_ast->right = NULL;
				ast->right = new_ast;
			}
		}
		tok_lst = tok_lst->next;
	}
	return (0);
}

void	print_ast(t_ast *ast)
{
	printf("Type: %d\n", ast->type);
	// printf("Type 2: %d\n", ast->right->type);
	if (!ast)
		return ;
	if (ast->type == COMMAND)
	{
		printf("Command/Argument: ");
		while (ast->cmd && ast->cmd[0] && ast->cmd[0][0] == '\0')
			ast->cmd++;
		if (ast->cmd == NULL || ast->cmd->args == NULL)
			printf("No command/argument\n");
		else
		{
			for (int i = 0; ast->cmd[i]; i++)
			{
				printf("%s", ast->cmd[i]);
				if (ast->cmd[i + 1])
					printf(" ");
			}
			printf("\n");
		}
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
	printf("test right\n");
	if (ast->right)
		print_ast(ast->right);
	else
		printf("No right child\n");
}

int	main(int ac, char **av)
{
	const char	*input;
	t_token		*tok_lst;
	t_ast		*ast;

	char *const *args;
	tok_lst = malloc(sizeof(t_token) * 50);
	for (int i = 0; i < 49; i++)
		tok_lst[i].next = &tok_lst[i + 1];
	tok_lst[49].next = NULL;
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
		parse_ast(tok_lst, ast);
		printf("AST:\n");
		print_ast(ast);
	}
}

// execve("/bin/cat", args, NULL);