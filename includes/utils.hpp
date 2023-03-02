#include <vector>
#pragma once

void    print_error (std::string error_message);
bool    CheckUserExists (std::vector<User> users, int fd);
void    removeInvisibleChars(char* str);
int     removeStringVector(std::vector<std::string>& myVector, const char* target);



void	free_tab(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
