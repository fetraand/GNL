/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fetraand <fetraand@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 00:00:00 by fetraand          #+#    #+#             */
/*   Updated: 2026/03/18 12:12:42 by fetraand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

/* -------------------------------------------------------------------------
** TEST 1 — Read all lines from a file
** ------------------------------------------------------------------------- */
static void	test_file(const char *filename)
{
	int		fd;
	char	*line;
	int		i;

	printf("\n=== TEST: Reading file '%s' ===\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("Line %d: [%s]\n", i++, line);
		free(line);
	}
	printf("--- EOF reached (%d line(s) read) ---\n", i - 1);
	close(fd);
}

/* -------------------------------------------------------------------------
** TEST 2 — Invalid file descriptor
** ------------------------------------------------------------------------- */
static void	test_invalid_fd(void)
{
	char	*line;

	printf("\n=== TEST: Invalid fd (-1) ===\n");
	line = get_next_line(-1);
	if (!line)
		printf("PASS — returned NULL for fd = -1\n");
	else
	{
		printf("FAIL — expected NULL, got: [%s]\n", line);
		free(line);
	}
}

/* -------------------------------------------------------------------------
** TEST 3 — Read from stdin (interactive, ends on empty line)
** ------------------------------------------------------------------------- */
static void	test_stdin(void)
{
	char	*line;

	printf("\n=== TEST: Reading from stdin (type lines, empty line to quit) ===\n");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || line[0] == '\n')
		{
			free(line);
			break ;
		}
		printf("Got: [%s]\n", line);
		free(line);
	}
	printf("--- stdin test done ---\n");
}

/* -------------------------------------------------------------------------
** TEST 4 — Empty file
** ------------------------------------------------------------------------- */
static void	test_empty_file(const char *filename)
{
	int		fd;
	char	*line;

	printf("\n=== TEST: Empty file '%s' ===\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("(skipped — file not found)\n");
		return ;
	}
	line = get_next_line(fd);
	if (!line)
		printf("PASS — returned NULL for empty file\n");
	else
	{
		printf("FAIL — expected NULL, got: [%s]\n", line);
		free(line);
	}
	close(fd);
}

/* -------------------------------------------------------------------------
** MAIN
** ------------------------------------------------------------------------- */
int	main(void)
{
	printf("==============================\n");
	printf("   get_next_line — Test Suite  \n");
	printf("==============================\n");

	/* --- File tests --- */
	test_file("filename");

	/* --- Invalid fd --- */
	test_invalid_fd();

	/* --- Empty file (create an empty file manually to use this test) --- */
	test_empty_file("empty.txt");

	/* --- Stdin test (optional — uncomment to use interactively) --- */
	/* test_stdin(); */

	printf("\n=== All tests done ===\n");
	return (0);
}