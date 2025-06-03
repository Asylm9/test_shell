#include "minishell.h"

// Fonction utilitaire pour créer une redirection
t_redirect *create_redirect(t_redir_type type, char *target)
{
    t_redirect *redir = malloc(sizeof(t_redirect));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->target = ft_strdup(target);
    redir->fd = -1;
    redir->next = NULL;
    return (redir);
}

// Fonction utilitaire pour créer une commande
t_command *create_command(char *cmd_name, char **args, t_redirect *redirections)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->cmd_name = ft_strdup(cmd_name);
    cmd->args = args;
    cmd->redirections = redirections;
    cmd->next = NULL;
    return (cmd);
}

// Fonction pour dupliquer un tableau d'arguments
char **dup_args(char **src)
{
    int count = 0;
    int i = 0;
    char **dest;
    
    while (src[count])
        count++;
    
    dest = malloc(sizeof(char *) * (count + 1));
    if (!dest)
        return (NULL);
    
    while (i < count)
    {
        dest[i] = ft_strdup(src[i]);
        i++;
    }
    dest[i] = NULL;
    return (dest);
}

// Fonction pour nettoyer une commande
void free_command(t_command *cmd)
{
    t_redirect *redir;
    t_redirect *next_redir;
    
    if (!cmd)
        return;
    
    free(cmd->cmd_name);
    free_array(cmd->args, -1);
    
    redir = cmd->redirections;
    while (redir)
    {
        next_redir = redir->next;
        free(redir->target);
        free(redir);
        redir = next_redir;
    }
    free(cmd);
}

// Fonction pour nettoyer une liste de commandes
void free_command_list(t_command *cmd_list)
{
    t_command *current;
    t_command *next;
    
    current = cmd_list;
    while (current)
    {
        next = current->next;
        free_command(current);
        current = next;
    }
}

// Test 1: Commande simple
void test_simple_command(t_sh *shell)
{
    printf("\n=== TEST 1: Commande simple (ls -l) ===\n");
    
    char *args1[] = {"ls", "-l", NULL};
    char **args_copy = dup_args(args1);
    t_command *cmd = create_command("ls", args_copy, NULL);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d\n", status);
    
    free_command_list(cmd);
}

// Test 2: Pipeline simple
void test_pipeline(t_sh *shell)
{
    printf("\n=== TEST 2: Pipeline (ls -l | head -5) ===\n");
    
    // Première commande: ls -l
    char *args1[] = {"ls", "-l", NULL};
    char **args1_copy = dup_args(args1);
    t_command *cmd1 = create_command("ls", args1_copy, NULL);
    
    // Deuxième commande: head -5
    char *args2[] = {"head", "-5", NULL};
    char **args2_copy = dup_args(args2);
    t_command *cmd2 = create_command("head", args2_copy, NULL);
    
    // Liaison des commandes
    cmd1->next = cmd2;
    
    int status = execute(cmd1, shell);
    printf("Status de retour: %d\n", status);
    
    free_command_list(cmd1);
}

// Test 3: Redirection de sortie
void test_output_redirect(t_sh *shell)
{
    printf("\n=== TEST 3: Redirection de sortie (echo hello > output.txt) ===\n");
    
    // Créer la redirection
    t_redirect *redir = create_redirect(OUT, "output.txt");
    
    // Créer la commande
    char *args[] = {"echo", "hello world", NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("echo", args_copy, redir);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d\n", status);
    printf("Vérifiez le contenu du fichier output.txt\n");
    
    free_command_list(cmd);
}

// Test 4: Redirection d'entrée
void test_input_redirect(t_sh *shell)
{
    printf("\n=== TEST 4: Redirection d'entrée (cat < output.txt) ===\n");
    
    // Créer la redirection (utilise le fichier créé dans le test précédent)
    t_redirect *redir = create_redirect(IN, "output.txt");
    
    // Créer la commande
    char *args[] = {"cat", NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("cat", args_copy, redir);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d\n", status);
    
    free_command_list(cmd);
}

// Test 5: Pipeline avec redirection
void test_pipeline_with_redirect(t_sh *shell)
{
    printf("\n=== TEST 5: Pipeline avec redirection (ls -l | grep .c > c_files.txt) ===\n");
    
    // Première commande: ls -l
    char *args1[] = {"ls", "-l", NULL};
    char **args1_copy = dup_args(args1);
    t_command *cmd1 = create_command("ls", args1_copy, NULL);
    
    // Deuxième commande: grep .c avec redirection
    t_redirect *redir = create_redirect(OUT, "c_files.txt");
    char *args2[] = {"grep", ".c", NULL};
    char **args2_copy = dup_args(args2);
    t_command *cmd2 = create_command("grep", args2_copy, redir);
    
    // Liaison des commandes
    cmd1->next = cmd2;
    
    int status = execute(cmd1, shell);
    printf("Status de retour: %d\n", status);
    printf("Vérifiez le contenu du fichier c_files.txt\n");
    
    free_command_list(cmd1);
}

// Test 6: Pipeline long
void test_long_pipeline(t_sh *shell)
{
    printf("\n=== TEST 6: Pipeline long (ls -l | grep .c | wc -l) ===\n");
    
    // Première commande: ls -l
    char *args1[] = {"ls", "-l", NULL};
    char **args1_copy = dup_args(args1);
    t_command *cmd1 = create_command("ls", args1_copy, NULL);
    
    // Deuxième commande: grep .c
    char *args2[] = {"grep", ".c", NULL};
    char **args2_copy = dup_args(args2);
    t_command *cmd2 = create_command("grep", args2_copy, NULL);
    
    // Troisième commande: wc -l
    char *args3[] = {"wc", "-l", NULL};
    char **args3_copy = dup_args(args3);
    t_command *cmd3 = create_command("wc", args3_copy, NULL);
    
    // Liaison des commandes
    cmd1->next = cmd2;
    cmd2->next = cmd3;
    
    int status = execute(cmd1, shell);
    printf("Status de retour: %d\n", status);
    
    free_command_list(cmd1);
}

// Test 7: Commande avec append
void test_append_redirect(t_sh *shell)
{
    printf("\n=== TEST 7: Redirection append (echo \"nouvelle ligne\" >> output.txt) ===\n");
    
    // Créer la redirection append
    t_redirect *redir = create_redirect(APPEND, "output.txt");
    
    // Créer la commande
    char *args[] = {"echo", "nouvelle ligne", NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("echo", args_copy, redir);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d\n", status);
    printf("Vérifiez le contenu du fichier output.txt (doit contenir les deux lignes)\n");
    
    free_command_list(cmd);
}

// Test 8: Commande inexistante
void test_command_not_found(t_sh *shell)
{
    printf("\n=== TEST 8: Commande inexistante (commande_inexistante) ===\n");
    
    char *args[] = {"commande_inexistante", NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("commande_inexistante", args_copy, NULL);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d (devrait être 127)\n", status);
    
    free_command_list(cmd);
}

// Test 9: exit
void test_exit_simple(t_sh *shell)
{
    printf("\n=== TEST 9: exit 2 ===\n");
    
    char *args[] = {"abc", NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("exit", args_copy, NULL);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d (2)\n", status);
    
    free_command_list(cmd);
}

// Test 10: pwd
void test_pwd(t_sh *shell)
{
    printf("\n=== TEST 10: pwd ===\n");
    
    char *args[] = {NULL};
    char **args_copy = dup_args(args);
    t_command *cmd = create_command("pwd", args_copy, NULL);
    
    int status = execute(cmd, shell);
    printf("Status de retour: %d (0)\n", status);
    
    free_command_list(cmd);
}

int main(int argc, char **argv, char **envp)
{
    t_sh shell;
	(void)argc;
	(void)argv;
    

    printf("=== DÉBUT DES TESTS D'EXÉCUTION ===\n");
    
    init_shell_struct(&shell, envp);
    init_env_list(shell.env);

    // Exécution des tests

    //test_simple_command(&shell);
    //test_pipeline(&shell);
    //test_output_redirect(&shell);
    //test_input_redirect(&shell);
    //test_pipeline_with_redirect(&shell);
    //test_long_pipeline(&shell);
    //test_append_redirect(&shell);
    //test_command_not_found(&shell);
    //test_exit_simple(&shell);
    //test_pwd(&shell);
    
/*     printf("\n=== FIN DES TESTS ===\n");
    printf("Status final du shell: %d\n", shell.exit_status); */
    
    cleanup_shell(&shell);
    
    return (0);
}