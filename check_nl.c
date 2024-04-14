int check_nl(char *str)
{
	while(*str)
	{
		if (*str = '\n')
			return (1);
		str++;
	}
	return (0);
}

