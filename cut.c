char *cut(char *str)
{
	int i;
	int j;
	char *right_str;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	right_str = (char *)malloc(sizeof(char) * (i + 1));
	while (str[j])
	{
		right_str[j] = str[j];
		if (str[j] == '\n')
		{
			j++;
			break;
		}
		j++;
	}
	right_str[j] = '\0';
	return (right_str);
}
