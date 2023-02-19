#include <stdio.h>

int	is_special_char(char *str)
{
	if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '<')
		return (1);
	else if (*str == '>')
		return (1);
	else if (*str == '|' && *(str + 1) == '|')
		return (2);
	else if (*str == '|')
		return (1);
	else if (*str == '&' && *(str + 1) == '&')
		return (2);
	return (0);
}

int	get_word_len(char *word)
{
	int	len;
	int	special;

	len = 0;
	while (word[len])
	{
		special = is_special_char(word + len);
		if (special)
		{
			if (!len)
				return (special);
			else
				return (len);
		}
		len++;
	}
	return (len);
}

static char	*get_next_word(char **str, char *seps, char *esc)
{
	static char	*word = NULL;

	if (word && *word)
		word += get_word_len(word);
	else
		word = *str;
	return (word);
}

int	main(void)
{
	char	*str = "ls|cat";

	printf("%d\n", get_word_len(get_next_word(&str, NULL, NULL)));
	printf("%d\n", get_word_len(get_next_word(&str, NULL, NULL)));
	printf("%d\n", get_word_len(get_next_word(&str, NULL, NULL)));
	printf("%s\n", get_next_word(&str, NULL, NULL));
	printf("%d\n", get_word_len(get_next_word(&str, NULL, NULL)));
	return (0);
}
