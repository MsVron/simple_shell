#include <stdio.h>
#include "main.h"

/**
 *main - Entry point of the program
 *
 *Return: Always 0 (Success)
 */
int main(void)
{
	quote();
	return (0);
}

/**
 *quote - Prints an iconic girl programmer quote
 */
void quote(void)
{
	printf("I'm not a great programmer; I'm just a good programmer");
	printg(" with great habits. - Ada Lovelace\n");
}
