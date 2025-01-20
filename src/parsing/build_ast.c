/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/20 18:49:07 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void free_ast(t_ast_node *node) 
{
    if (!node)                      
        return ;
    free_ast(node->left);      
    free_ast(node->right);      
    if (node->value)        
        free(node->value);
    free(node);
}

t_ast_node	*create_node(t_node_type type, char *value)
{
    t_ast_node	*node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->value = ft_strdup(value); 
    node->left = NULL;
    node->right = NULL;
    return (node); 
}

t_ast_node	*build_ast(t_token *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;

	current = NULL;
	root = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			t_ast_node	*pipe_node;
			
			pipe_node = create_node(NODE_PIPE, "|");
			

		}
	}
	return (root);
}