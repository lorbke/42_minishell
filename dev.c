#include <stdio.h>
#include <dirent.h>
#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == 0 || haystack == needle)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] != 0 && i < len)
	{
		j = 0;
		while (haystack[i + j] != 0 && needle[j] != 0
			&& haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == 0)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	// DIR *dir;
	// struct dirent *entry;

	// if (argc != 2) {
	// 	fprintf(stderr, "Usage: %s path\n", argv[0]);
	// 	return 1;
	// }
	// dir = opendir(argv[1]);
	// if (dir == NULL) {
	// 	perror("opendir");
	// 	return 1;
	// }
	// while ((entry = readdir(dir)) != NULL) {
	// 	if (ft_strnstr(entry->d_name, ".c", strlen(entry->d_name)))
	// 		printf("%s ", entry->d_name);
	// }
	// printf("\n");
	// closedir(dir);
	printf("%d\n", strcmp("Makefile", "dev"));
	return(0);
}
