/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:10:00 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/11 19:27:55 by matthieu         ###   ########.fr       */
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
	while (tok_lst->next)
	{
		if (tok_lst->value != NULL)
			printf("Token %d type : %d value : %s\n", i, tok_lst->type,
				tok_lst->value);
		if (tok_lst->expand == EXPAND && tok_lst->value != NULL)
			printf("Token %d expand : EXPAND\n", i);
		else if (tok_lst->value != NULL)
			printf("Token %d expand : NO_EXPAND\n", i);
		tok_lst = tok_lst->next;
		i++;
	}
}

void	free_tok_lst(t_token *list)
{
    t_token	*temp;

    while (list)
    {
        temp = list;
        list = list->next;
        if (temp->value)
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

	tok_lst = NULL;
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
		printf("Creating new token node.\n");
		if (create_token_node(&tok_lst))
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
		printf("Expanding token list.\n");
		temp = expand_list(tok_lst, envp);
		printf("Expansion successful.\n");
		print_token(temp);
		printf("Creating AST.\n");
		ast = malloc(sizeof(t_ast));
		if (!ast)
		{
			perror("malloc");
			free(tok_lst);
			return (1);
		}
		printf("AST created successfully.\n");
		printf("Freeing token list.\n");
		free_tok_lst(tok_lst);
		printf("Token list freed successfully.\n");
		printf("Freeing expanded token list.\n");
		free_tok_lst(temp);
		printf("Expanded token list freed successfully.\n");
		// free(input);
		// parse_ast(tok_lst, ast);
		// printf("AST:\n");
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