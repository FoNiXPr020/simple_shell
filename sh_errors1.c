#include "shell.h"

/**
 * _convert_to_integer - Convert a string to an integer.
 * @s: The string to be converted
 * Return: 0 if no numbers are present in the string,
 * the converted number otherwise,
 *         -1 on error
 */
int _convert_to_integer(char *s)
{
	int i = 0;
	unsigned long int iResult = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			iResult *= 10;
			iResult += (s[i] - '0');
			if (iResult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (iResult);
}

/**
 * display_error - Display an error message.
 * @info: The parameter & return info struct
 * @estr: String containing the specified error type
 * Return: 0 if no numbers are present in
 * the string, the converted number otherwise,
 *         -1 on error
 */
void display_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_decimal - Print a decimal (integer) number (base 10).
 * @input: The input number
 * @fd: The file descriptor to write to
 * Return: Number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, iCount = 0;
	unsigned int _abs_, iCurrent;

	if (fd == STDERR_FILENO)
		__putchar = _eput_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		iCount++;
	}
	else
		_abs_ = input;
	iCurrent = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + iCurrent / i);
			iCount++;
		}
		iCurrent %= i;
	}
	__putchar('0' + iCurrent);
	iCount++;

	return (iCount);
}

/**
 * number_conversion - Convert a number to a string representation.
 * @num: The number to convert
 * @base: The base of the conversion
 * @flags: Argument flags
 * Return: A string representation of the number
 */
char *number_conversion(long int num, int base, int flags)
{
	static char *iArray;
	static char iBuff[50];
	char iSign = 0;
	char *iPtr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		iSign = '-';

	}
	iArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	iPtr = &iBuff[49];
	*iPtr = '\0';

	do	{
		*--iPtr = iArray[n % base];
		n /= base;
	} while (n != 0);

	if (iSign)
		*--iPtr = iSign;
	return (iPtr);
}

/**
 * eliminate_comments - Replace the first instance of '#' with '\0' in string.
 * @buf: Address of the string to modify
 * Return: Always returns 0
 */
void eliminate_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

