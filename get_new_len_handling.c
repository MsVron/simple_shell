#include "main.h"

ssize_t get_new_len(char *line);
ssize_t handle_semicolon_case(char *line, size_t index, char next);
ssize_t handle_initial_semicolon_case(char *line, size_t index, char next);
ssize_t update_new_len(char *line);

/**
 *get_new_len - Gets the new length of a line partitioned
 *              by ";", "||", "&&&", or "#".
 *@line: The line to check.
 *
 *Return: The new length of the line.
 *
 *Description: Cuts short lines containing '#' comments with '\0'.
 */
ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];

		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				new_len += handle_semicolon_case(line, i, next);
			}
			else
			{
				new_len += update_new_len(&line[i]);
			}
		}
		else if (current == ';')
		{
			new_len += handle_initial_semicolon_case(line, i, next);
		}

		new_len++;
	}

	return (new_len);
}

/**
 *handle_semicolon_case - Handles the semicolon case.
 *@line: The line to check.
 *@index: The index of the current character.
 *@next: The next character.
 *
 *Return: The count to add to new_len.
 *
 *Description: Handles the new length calculation when the current character
 *             is a semicolon.
 */
ssize_t handle_semicolon_case(char *line, size_t index, char next)
{
	ssize_t count = 1;

	if (next == ';' && line[index - 1] != ' ' && line[index - 1] != ';')
		count++;
	else if (line[index - 1] == ';' && next != ' ')
		count++;

	if (line[index - 1] != ' ')
		count++;
	if (next != ' ')
		count++;

	return (count);
}

/**
 *handle_initial_semicolon_case - Handles the initial semicolon case.
 *@line: The line to check.
 *@index: The index of the current character.
 *@next: The next character.
 *
 *Return: The count to add to new_len.
 *
 *Description: Handles the new length calculation when the current character
 *             is an initial semicolon.
 */
ssize_t handle_initial_semicolon_case(char *line, size_t index, char next)
{
	ssize_t count = 0;

	if (index != 0 && line[index - 1] != ' ')
		count++;
	if (next != ' ' && next != ';')
		count++;

	return (count);
}

/**
 *update_new_len - Updates the new length based on specific conditions.
 *@line: The line to check.
 *
 *Return: The count to add to new_len.
 *
 *Description: Handles the new length calculation for specific conditions
 *             in the line.
 */
ssize_t update_new_len(char *line)
{
	if (line[0] == ';' && line[1] == ';')
		return (2);
	else if (line[0] == ';' || line[0] == '|' || line[0] == '&')
		return (1);
	else
		return (0);
}
