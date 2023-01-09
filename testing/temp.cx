


t_token	*insert_node(t_token *current, t_token *next)
{
	if (next->desc == 1)
	{
		current->a = next;
		return (next);
	}
	// else if (next->desc == 2)
	// {
	// 	next->a = current;
	// 	return (next);
	// }
	else
	{
		free(next);
		return (current);
	}
}

void	parse_input(char *input)
{
	char	*seps = " \t\n\r";
	t_token	*head;
	t_token	*current;
	t_token	*next;

	head = malloc(sizeof(t_token));
	current = head;
	while (input)
	{
		next = create_token();
		next->word = ft_strsep(&input, seps);
		next->desc = desc_word(next->word);
		current = insert_node(current, next);
	}
	print_ast(head);
}
