#ifndef EXEC_H
# define EXEC_H

//-lreadline
//-lhistory
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <signal.h>

# define SUCCESS 0
# define ERROR 1
# define BUILTIN_ERR 2

# define STDERR 2

# define CMD_NOT_FOUND 127
# define EXECVE_ERR 126 //commande trouvee mais pas executable

/* #ifndef PATH_MAX */
# define PATH_MAX 4096  // valeur courante sur la plupart des systèmes Linux


typedef struct s_redirect	t_redirect;
typedef struct s_command	t_command;
typedef struct s_sh		    t_sh;
typedef struct s_token		t_token;
typedef struct s_env		t_env;


typedef enum e_token_type
{
	TOKEN_EXIT_STATUS
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_token			*next;
}			t_token;

typedef enum e_redir_type
{
	IN,      // <
	OUT,     // >
	APPEND,  // >>
	HEREDOC  // <<
}			t_redir_type;

typedef struct s_redirect
{
	t_redir_type	type;
	char			*target; // fichier ou delimiteur si heredoc
	int 			fd;      // pour heredoc
	t_redirect		*next;
}			t_redirect;

typedef struct s_command
{
	char		*cmd_name;
	char 		**args;
	//int		arg_count;
	t_redirect	*redirections;
	t_command	*next;
}			t_command;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
	t_env	*prev;
}			t_env;


typedef struct s_sh
{
	char		**env;
	t_env		*envl;
	char		**export; // static? 
	t_command	*cmd_list;
	char		*current_dir;
	int			exit_status;
}			t_sh;

typedef	struct s_exec
{
	int 		**pipes;
	int			nb_pipes;
	pid_t		*pids;
	t_command	*current;
	int			i;
	int			status;
}				t_exec;

/* Expander */
char	*expand_exit_status(t_sh *shell, t_token token);

/* Execution */
int		process_wait_status(int status);
int		execute(t_command *cmd_list, t_sh *shell); //transformer en execute_ast probablement :v
int		execute_command(t_command *cmd, t_sh *shell);
int		execute_pipeline(t_command *cmds, t_sh *shell);
int		execute_binary(t_command *cmd, char **env);

/* Path and environment handling */
char	*get_env_var(char *name, char **env);
int		set_env_var(char *name, char **env, char *path);
char	**get_paths(char **env);
char	*find_cmd_path(char **paths, char *cmd_name);

/* Redirections */
int		redirect_in(int fd, t_redirect *redir);
int		apply_redirections(t_command *cmd);
int		setup_pipes_redirections(int **pipes, int nb_pipes, int i);
int		setup_heredoc(t_redirect *redir); // parsing ou exec?

/* Pipe handling */
void	get_pipe_count(t_command *cmd_list, int *nb_pipes);
void	close_pipes(int **pipes, int nb_pipes);
int		init_pipes(int **pipes, int nb_pipes);
int		**create_pipes(int nb_pipes);

/* Builtin commands */
int		args_count(char **args);
bool	state_changing_builtin(char *cmd_name);
bool	is_builtin(char *cmd_name);
int		execute_builtin(t_command *cmd, t_sh *shell);

/* Builtin implementations */
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_sh *shell);
int		builtin_pwd(t_sh *shell);
int		builtin_export(char **args, t_sh *shell);
int		builtin_unset(char **args, t_sh *shell);
int		builtin_env(t_sh *shell);
int		builtin_exit(char **args, t_sh *shell);

/* Env utils */
t_env	*init_env_list(char **env);
char	*get_envl_var(char *name, t_env *envl);
int		set_envl_var(char *name, t_env **envl, char *value);
/* char	*get_env_var(char *name, char **env);
int		set_env_var(char *name, char **env, char *value); */

/* Utils */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_pathjoin(char const *s1, char const *s2);
//void	error_message(const char *msg);

/* List utils */
t_env	*create_node(char *key, char *value);
t_env	*find_last_node(t_env *head);
t_env	*add_back_node(t_env *new_node, t_env *head);

/* Resources */
void	free_pipes(int **pipes, int i);
void	free_array(char **array, int i);
void	free_envl(t_env **head);
void	cleanup_shell(t_sh *shell);

/* Testing */
void	print_env_list(t_env *envl);

void	init_redir(t_redirect *redir);
void	init_cmd_struct(t_command *cmd, char **av, t_redirect *redir);
void	init_shell_struct(t_sh *shell, char **envp);

#endif