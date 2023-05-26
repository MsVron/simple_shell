#include "main.h"

ssize_t get_new_len(char *line);
ssize_t handle_semicolon_case(char *line, size_t index, char next);
ssize_t handle_initial_semicolon_case(char *line, size_t index, char next);
int should_insert_space(char previous, char current, char next);
void update_new_len(char *line, ssize_t *new_len);

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
 *handle_semicolon_case - Handles the new length calculation for semicolon cases.
 *@line: The line to check.
 *@index: The current index in the line.
 *@next: The next character.
 *
 *Return: The additional length to add.
 *
 *Description: Handles the new length calculation for cases involving semicolons.
 *             It checks for specific conditions and returns the additional length to add.
 */
ssize_t handle_semicolon_case(char *line, size_t index, char next)
{
	ssize_t additional_len = 0;

	if (next != ' ')
		additional_len++;
	if (line[index - 1] != ' ')
		additional_len++;

	return additional_len + 2;
}

/**
 *handle_initial_semicolon_case - Handles the new length calculation for initial semicolon case.
 *@line: The line to check.
 *@index: The current index in the line.
 *@next: The next character.
 *
 *Return: The additional length to add.
 *
 *Description: Handles the new length calculation for the initial semicolon case.
 *             It checks for specific conditions and returns the additional length to add.
 */
ssize_t handle_initial_semicolon_case(char *line, size_t index, char next)
{
	ssize_t additional_len = 0;

	if (line[index - 1] != ' ')
		additional_len++;
	if (next != ' ' && next != ';')
		additional_len++;

	return additional_len;
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
