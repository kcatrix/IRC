/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:37:23 by tnicoue           #+#    #+#             */
/*   Updated: 2023/02/28 17:15:34 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

void free_tab(char **str)
{
	int i = 0;
	
	while(str[i])
	{
		free(str[i]);
	}
	free(str);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;

	i = -1;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
	{	
		a = (char *)malloc(sizeof(*s) * 1);
		if (!a)
			return (NULL);
		a[0] = '\0';
		return (a);
	}
	a = (char *)malloc(sizeof(*s) * (len + 1));
	if (!a)
		return (NULL);
	while (++i < len)
		a[i] = s[i + start];
	a[i] = '\0';
	return (a);
}

static int	compte(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			j++;
		else if (s[i] != c && (i > 0 && s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

static int	futur(const char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	j = compte((char *)s, c);
	a = (char **)malloc(sizeof(char *) * (j + 1));
	if (!a)
		return (0);
	i = 0;
	while (i < j)
	{
		k = 0;
		while (*s != '\0' && *s == c)
			s++;
		k = futur((char *)s, c);
		a[i] = ft_substr(s, 0, k);
		while (*s != '\0' && *s != c)
			s++;
		i++;
	}
	a[i] = NULL;
	return (a);
}
