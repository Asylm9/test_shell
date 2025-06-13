
typedef enum e_token_type
{
	CMD,
	PIPE,
}							t_token_type;

typedef struct s_ast
{
	t_token_type			type;
	t_command				*cmd;
	t_ast					*left;
	t_ast					*right;
}							t_ast;

typedef struct s_redirect
{
	t_redir_type			type;
	char *target; // fichier ou delimiteur si heredoc
	int fd;       // pour heredoc
	t_redirect				*next;
}							t_redirect;

typedef struct s_command
{
	char					*cmd_name;
	char					**args;
	int						argc;
	t_redirect				*redirections;
	t_command				*next;
}							t_command;