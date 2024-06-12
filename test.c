#include <stdio.h>
#include <stdlib.h>

int	countbigword(char *s, int i)
{
	i++;
	while ((s[i] != 0) && (s[i] != 34 || s[i] != 39))
		i++;
	return(i);
}

int	countarr(char *s)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != 32)
	{
		count ++;
		while (s[i] != 32)
			i++;
	}
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			i = countbigword(s, i);
			count ++;
		}
		while ((s[i] != 0) && s[i] != 32)
			i++;
		count ++;
	}
	return (count);
}

char **ft_newsplit(char *s)
{
	char	**arr;
	int		i;
	int 	j;
	int		x;

	i = 0;
	arr = NULL;
	x = countarr(s);
	arr = calloc(x + 1, sizeof(char *));
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		j = i;
		while (s[i] != ' ' && s[i] != 0)
			i++;
		if (s[i] == ' ' || s[i] == 0)
		{
			arr[x] = ft_substr(s, j, (i - j) * sizeof(char));
			if (!arr[x])
				return (ft_freearr(arr));
			i++;
			x++;
		}
	}
	return (arr);
}

static char	**toomanylines(char **arr, char *s, char c, size_t word)
{
	size_t	i;
	size_t	j;
	size_t	x;

	x = 0;
	i = 0;
	while (word - 1 > x && s[i] != 0)
	{
		while (s[i] == c)
			i ++;
		j = i;
		while (s[i] != c && s[i] != 0)
			i ++;
		if ((s[i] == c || s[i] == 0) && word - 1 > x)
		{
			arr[x] = ft_substr(s, j, (i - j) * sizeof(char));
			if (!arr[x])
				return (ft_freearr(arr));
			i ++;
			x ++;
		}
	}
	return (arr);
}

int main (int argc, char **argv)
{
	int i = countarr(argv[1]);
	printf("tem %i palavras\n", i);
	return(0);
}