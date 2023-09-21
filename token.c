#include "main.h"

/**
 * **_strtok - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_strtok2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtok2(char *str, char d)
{
	int numwords = 0;
    char **s = NULL;
    int len =_strlen(str);
	int word_count = 0;
    int word_start = 0;
    int i = 0;
    int j = 0;
	
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (; i <= len; i++)
    {
        if (str[i] != d && (i == 0 || str[i - 1] == d))
        {
            word_start = i;
        }
        else if ((str[i] == d || str[i] == '\0') && i > 0 && str[i - 1] != d)
        {
            int word_length = i - word_start;
            s[word_count] = malloc((word_length + 1) * sizeof(char));
            if (!s[word_count])
            {
                for (; j < word_count; j++)
                    free(s[j]);
                free(s);
                return NULL;
            }

            _strncpy(s[word_count], &str[word_start], word_length);
            s[word_count][word_length] = '\0';
            word_count++;
        }
    }
	s[numwords] = NULL;
    return (s);
}
