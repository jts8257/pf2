#include "head.h"

static	void	set_width_or_prec(va_list ap, t_opt *opt, char ch)
{
	if (ft_isdigit(ch)) // 너비 값이 고정 인자 문자열에 명시적으로 존재할 경우
	{
		if (opt->prec == -1)    // '.' 플래그가 발견되지 않은 상태일 경우
			opt->width = opt->width * 10 + ch - '0';
            //  고정 인자 문자열은 문자로 이루어져 있기 때문에
            //  ASCII 코드를 활용하여 문자를 정수형으로 변환하기 위한 과정
		else    // '.' 플래그 이후에 너비 값이 존재할 경우
			opt->prec = opt->prec * 10 + ch - '0';
	}
	else if (ch == '*') // 숫자 와일드카드, 가변 인자로 값이 들어올 경우
	{
		if (opt->prec == -1)
		{
			if ((opt->width = va_arg(ap, int)) < 0)
			{
				opt->minus = 1;
                /* 만약 너비에 대한 가변 인자 값이 음수일 경우
                    '-' 부호를 플래그로 인식하도록
                    minus 변수를 1로 설정       */
				opt->width *= -1;   //  너비는 양수로 변경
				opt->zero = 0;  //  zero 변수는 0으로 설정하여 무시 ('%' 타입 대비)
			}
		}
		else
		{
			if ((opt->prec = va_arg(ap, int)) < 0)
				opt->prec = -1;
            //   가변 인자로 받아온 정밀도 너비가 음수일 경우 prec 변수를 -1로 설정하여 정밀도에 대한 처리를 무시
		}
	}
}

int			type_matcging(va_list ap, t_opt *opt)
{
	/* 여기까지는 가변인자가 제대로 들어옴
	printf("==type_matcging==\nstr : %s\n", va_arg(ap, char *));
	printf("int : %d\n", va_arg(ap, int));
	*/
	if (opt->type == 'c')
		return (char_format(va_arg(ap, int), opt));
	else if (opt->type == 's')
		return (str_format(va_arg(ap, char*), opt));
	else if (opt->type == 'i' || opt->type == 'd')
		return (int_format(va_arg(ap, int), opt));
	else if (opt->type == 'p')
		return (pointer_format(va_arg(ap, long long), opt));
	else if (opt->type == 'u' || opt->type == 'x' || opt->type == 'X')
		return (uint_format(va_arg(ap, unsigned long long), opt));
	else if (opt->type == '%')
		return (char_format(opt->type, opt));
	else
		return (-1);
}

char		*next_addr(char *str) 
{
	while (*str) 
	{
		if (in_format(*str))
		{
			return ++str;
		}
		str++;
	}
	return 0;
}

int			find_format(char *fmt, va_list ap)
{
	int		print_len;
	t_opt	*opt;
	char	*types;

	types = ft_strdup("csidpuxX%");
	opt = init_opt();
	if (!types || !opt) 
	return (-1);
	while (!ft_strchr(types, *fmt) && *fmt != '\0')
	{
		if (*fmt == '-')
			opt->minus = 1;
		else if (*fmt == '0' && opt->width == 0 &&
				opt->prec == -1 && opt->minus == 0)
			opt->zero = 1;
		else if (*fmt == '.')
			opt->prec = 0;
		else if (ft_isdigit(*fmt) || *fmt == '*')
			set_width_or_prec(ap, opt, *fmt);
		fmt++;
	}
	opt->type = *fmt;
    if ((opt->prec >= 0 || opt->minus > 0) && opt->type != '%')
		opt->zero = 0;
	print_len = type_matcging(ap, opt);
	free(types);
	free(opt);
	return (print_len);
}

int	ft_printf(const char *str, ...)
{
	int			print_len;
	int			rtn; 
	va_list		ap;

	rtn = 0;
	va_start(ap, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			print_len = find_format((char *)++str, ap);
			if (print_len >= 0)
			{
				rtn += print_len;
				str = next_addr((char *)str);
			}
		}
		else
		{
			rtn += ft_putchar_fd(*str, 1);
			str++;
		}
	}
	va_end(ap);
	return (rtn);
}