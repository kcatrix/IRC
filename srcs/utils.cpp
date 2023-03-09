
#include "../includes/irc.hpp"

void    print_message (int sd, std::string message) {
    write (sd, message.c_str (), message.length ());
}

void    print_error (std::string error_message) {
    std::cout << error_message << std::endl;
    exit (EXIT_FAILURE);
}

bool    CheckUserExists (std::vector<User> users, int fd) {
    for (std::vector<User>::iterator it = users.begin (); it != users.end (); it++) {
        if ((*it).sd == fd)
            return 1;
    }
    return 0;
}

void    removeInvisibleChars(char* str)
{
    int i = 0;
    while (str[i])
        i++;
    i--;
    str[i] = '\0';
}

int     removeStringVector(std::vector<std::string>& myVector, const char* target)
{
    int length = myVector.size();
    for (int i = 0; i < length; ++i) 
    {
        if (myVector[i] == target) 
        {
            myVector.erase(myVector.begin() + i);
            return (0);
            break;
        }
    }
    std::cout << "not find \n"; 
    return(1);
}

void free_tab(char **str)
{
	int i = 0;
	
	while(str[i])
	{
		free(str[i]);
		i++;

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



static int	strl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	size_t	lena;
	size_t	lenb;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	lena = strl(s1);
	lenb = strl(s2);
	c = (char *)malloc(sizeof(char) * (lena + (lenb + 1)));
	if (!c)
		return (NULL);
	i = 0;
	j = 0 - lena;
	while (i < lena + (lenb + 1))
	{
		c[i] = s1[i];
		if (i >= lena)
			c[i] = s2[j];
		j++;
		i++;
	}
	c[i] = '\0';
	return (c);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		i;
	int		j;

	j = 0;
	while (s1[j])
		j++;
	dest = (char *)malloc(sizeof(*dest) * (j + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (i < j)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

std::vector<std::string> splitString(const std::string& str) {
    std::vector<std::string> result;

    std::string::size_type start = 0;
    std::string::size_type end = str.find(" ");

    while (end != std::string::npos) {
        if (end > start) {
            result.push_back(str.substr(start, end - start));
        }
        start = end + 1;
        end = str.find(" ", start);
    }

    if (start < str.size()) {
        result.push_back(str.substr(start));
    }

    result.push_back ("");
    return result;
}
