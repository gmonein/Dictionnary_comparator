#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int		get_fd_size(int fd)
{
	off_t	first_pos;
	int		size;

	first_pos = lseek(fd, (size_t)0, SEEK_CUR);
	size = lseek(fd, (size_t)0, SEEK_END);
	lseek(fd, first_pos, SEEK_SET);
	return (size);
}

char	*ft_read(char *file_path)
{
	int		fd;
	char	*res;
	int		size;

	if ((fd = open(file_path, O_RDONLY)) == -1)
		return (NULL);
	if ((size = get_fd_size(fd)) < 1)
	{
		close(fd);
		return (NULL);
	}
	if(!(res = (char *)malloc(size + 1)))
	{
		close(fd);
		return (NULL);
	}
	read(fd, res, size);
	res[size] = '\0';
	close(fd);
	return (res);
}

char	**ft_split(char *str, char s)
{
	char		**res;
	size_t		i;
	size_t		line = 1;

	for (i = 0; str[i]; i++)
		if (str[i] != s && (i == 0 || str[i - 1] == s)) line++;
	res = (char **)malloc(sizeof(char *) * (line + 1));
	size_t		j = 0;
	for (i = 0; str[i]; i++)
		if (str[i] != s && (i == 0 || str[i - 1] == s)){
			res[j] = &str[i]; j++;}
	for (i = 0; str[i]; i++)
		if (str[i] == s) str[i] = '\0';
	res[j] = NULL;
	printf("splitted in %lu\n", j);
	return (res);
}

int		strcmp_swap(char *s1, char *s2, int error)
{
	size_t		i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			error--;
		if (error == -1)
			return (-1);
	}
	if (s1[i] != s2[i])
		error--;
	return (error == -1 ? 1 : 0);
}

int		strcmp_more(char *s1, char *s2, unsigned char mode, int error)
{
	size_t		i = 0;
	size_t		j = 0;

	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[i])
		{
			if (mode & 0b1)
				i++;
			if (mode & 0b01)
				j++;
			error--;
		}
		if (error == -1)
			return (-1);
	}
	return (s1[i] != s2[j] ? 1 : 0);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	char		*names_line = ft_read(argv[1]);
	char		*dico_line = ft_read(argv[2]);
	if (!names_line || !dico_line)
		return (1);
	char		**names = ft_split(names_line, '\n');
	char		**dico = ft_split(dico_line, '\n');
	if (!names || !dico)
		return (1);
	printf("Perfect name\n");
	for (int i = 0; names[i]; i++)
		for (int j = 0; dico[j]; j++)
			if (!strcmp(names[i], dico[j]))
				printf("%s\n", names[i]);
	/*
	printf("1 error permit\n");
	for (int i = 0; names[i]; i++)
	{
		for (int j = 0; dico[j]; j++)
		{
			if (!strcmp_swap(names[i], dico[j], 1))
				printf("%s -> %s\n", names[i], dico[j]);
		}
	}
	printf("1 more letter permit\n");
	for (int i = 0; names[i]; i++)
	{
		for (int j = 0; dico[j]; j++)
		{
			if (!strcmp_more(names[i], dico[j], 0b1, 1))
				printf("%s -> %s\n", names[i], dico[j]);
		}
	}*/ //CA NE MARCHE PAS LOL
}
