#include "../headers/main.h"

// typedef enum {INT, FLOAT} TokenTypeNumber;

// void	identifyTokenType(TokenTypeNumber token)
// {
// 	if (token == INT)
// 		printf("Token is an int");

// }


int	main()
{
	char	*input;

	while (1)
	{
		input = readline("Digite algo> ");
		if (input == NULL)
		{
			printf("Saindo do programa.\n");
			break;
		}
		printf("%s\n", process_env_var(input));
		if (*input)
			add_history(input);		
		free(input);
	}
	write_history(".my_history");
	return (0);
}