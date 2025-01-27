/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:35:00 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/27 20:11:37 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	open_stdout(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_token_append(char *file)
{
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_stdin(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}
// #include <stdio.h>

// int main() {
//     int fd;

//     // Testar open_stdout
//     fd = open_stdout("saida.txt");
//     if (fd != -1) {
//         write(fd, "Escrevendo no arquivo de saída\n", 31);
//         close(fd);
//     }

//     // Testar open_token_append
//     fd = open_token_append("saida_append.txt");
//     if (fd != -1) {
//         write(fd, "Adicionando ao arquivo (append)\n", 32);
//         close(fd);
//     }

//     // Testar open_stdin
//     fd = open_stdin("open_file.c");
//     if (fd != -1) {
//         char buffer[128];
//         int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
//         if (bytesRead > 0) {
//             buffer[bytesRead] = '\0';
//             printf("Conteúdo do arquivo: %s\n", buffer);
//         }
//         close(fd);
//     }

//     return 0;
// }
