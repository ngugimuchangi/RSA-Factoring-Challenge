#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * str_to_llu - converts string to number
 * @str_num: number to convert
 * @len: string length
 *
 * Description: converts a string number
 * greater than long long to unsigned
 * long long
 *
 * Return: unsigned long long
 */

unsigned long long int str_to_llu(char *str_num, size_t len)
{
	unsigned long long num = 0, p_value = 1, digit, i;
	char str_digit[2];

	str_digit[1] = '\0';
	for (i = 0; i < len - 1; i++)
		p_value *= 10;
	for (i = 0; i < len; i++)
	{
		str_digit[0] = str_num[i];
		digit = atoi(str_digit);
		num = num + (digit * p_value);
		p_value /= 10;
	}
	return (num);
}

/**
 * factors - factorizes number
 * @str_num: number to factorize
 *
 * Description: factorizes a number to
 * the product of two smaller numbers
 *
 * Return: nothing
 */
void factors(char *str_num)
{
	unsigned long long int div, factor, num, len;
	char *str_copy;

	len = strlen(str_num) - 1;
	if (len < 18)
		num = atoll(str_num);
	else
		num = str_to_llu(str_num, len);

	for (div = 2; div <= num; div++)
		if (num % div == 0)
		{
			factor = num / div;
			break;
		}
	printf("%llu=%llu*%llu\n", num, factor, num / factor);
}

/**
 * main - Entry point
 * @ac: argument count
 * @av: arguments
 *
 * Return: always 0
 */
int main(int ac, char **av)
{
	FILE *file;
	ssize_t _read;
	size_t n = 0;
	char *buff = NULL;

	if (ac != 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(av[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: File not found\n");
		exit(EXIT_FAILURE);
	}
	_read = getline(&buff, &n, file);
	while (_read != -1)
	{
		factors(buff);
		_read = getline(&buff, &n, file);
	}
	free(buff);
	fclose(file);
	return (0);
}
