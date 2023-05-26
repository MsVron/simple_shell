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
				if (should_insert_space(line[i - 1], current, next))
					new_len += 2;
				else
				{
					if (line[i - 1] != ' ')
						new_len++;
					if (next != ' ')
						new_len++;
				}
			}
			else
				update_new_len(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}

		new_len++;
	}

	return (new_len);
}

/**
 *should_insert_space - Checks whether a space should be inserted between
 *                      characters.
 *@previous: The previous character.
 *@current: The current character.
 *@next: The next character.
 *
 *Return: 1 if a space should be inserted, 0 otherwise.
 *
 *Description: Determines whether a space should be inserted between
 *             characters based on specific conditions. It checks for cases
 *             involving semicolons, double ampersands, and double vertical
 *             bars (logical operators). If the conditions are met, it returns
 *             1 to indicate that a space should be inserted; otherwise, it
 *             returns 0.
 */
int should_insert_space(char previous, char current, char next)
{
	if (current == ';')
	{
		if (next == ';' && previous != ' ' && previous != ';')
			return (1);
		else if (previous == ';' && next != ' ')
			return (1);
		if (previous != ' ')
			return (1);
		if (next != ' ')
			return (1);
	}
	else if (current == '&' && next == '&' && previous != ' ')
		return (1);
	else if (current == '|' && next == '|' && previous != ' ')
		return (1);

	return (0);
}

/**
 *update_new_len - Updates the new length based on specific conditions.
 *@line: The line to check.
 *@new_len: Pointer to the new length.
 *
 *Description: Handles the new length calculation for specific conditions
 *             in the line.
 */
void update_new_len(char *line, ssize_t *new_len)
{
	if (line[0] == ';' && line[1] == ';')
		*
		new_len += 2;
	else if (line[0] == ';' || line[0] == '|' || line[0] == '&')
		*
		new_len += 1;
}
