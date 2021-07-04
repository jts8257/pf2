#ifndef HEAD_H
 #define HEAD_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>


typedef struct	s_opt
    {
        size_t		minus;  // 0
        size_t		zero;   // 0
        int			width;  // 0
        int			prec;   // -1 ('.' 플래그만 존재하고 너비에 대한 값이 존재하지 않을 수 있는 경우를 대비하여 초기값을 -1로 설정)
        char		type;   // 0 ('\0')
    }			t_opt;

int	ft_printf(const char *str, ...);
int	data_type(va_list ap, t_opt *opt);
size_t	char_format(int ch, t_opt *opt);
size_t	str_format(char *str, t_opt *opt);
size_t			int_format(int n, t_opt *opt);
size_t			pointer_format(long long n, t_opt *opt);
size_t			uint_format(unsigned int n, t_opt *opt);

int		in_format(char c);
char	*set_padding(size_t zr_flg, size_t size);
char	*set_sorting(size_t mns_flg, char *arg, char *padding);
char	*applies_to_prec(int prec, char *arg);
char	*applies_to_width(t_opt *opt, char *sign, char *arg);
size_t			uint_format(unsigned int n, t_opt *opt);
size_t			pointer_format(long long n, t_opt *opt);
int		ft_dupl_check(char *str, int length);
t_opt *init_opt();

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
char		*ft_itoa(int n);
char	*ft_strdup(const char *s1);
size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);

char			*ft_tobase_n(long long n, char *base);


#endif








