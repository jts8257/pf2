#include "head.h"

size_t	char_format(int ch, t_opt *opt)	// 데이터 타입이 'c' || '%' 일 경우 처리하는 함수
{
	size_t	print_len;
    char	*padding;

	if (opt->width > 0)
		padding = set_padding(opt->zero, (size_t)opt->width - sizeof(char));
	else
		padding = ft_strdup("");
	//	전체 출력 너비가 0 보다 작거나 같다면 빈 문자열('\0')을 padding 에 저장

    /*	'-' 플래그가 존재하지 않는다면 우측 정렬*/
	if (opt->minus == 0)
	{
		print_len = ft_putstr_fd(padding, 1);
		print_len += ft_putchar_fd((char)ch, 1);
	}
	else
	{
		print_len = ft_putchar_fd((char)ch, 1);
		print_len += ft_putstr_fd(padding, 1);
	}
	free(padding);
	return (print_len);
}

size_t	str_format(char *str, t_opt *opt)//	s 데이터 타입일 경우 처리하는 함수
{
	size_t	print_len;
	char	*arg;
	char	*padding;
	
	if (str == NULL)
		str = "(null)";
	//	만약 가변인자 문자열이 NULL 일 경우 가변인자 문자열을 "(null)"로 대체
	if (opt->prec > -1){
		arg = ft_substr(str, 0, opt->prec);
	}
	// 만약 '.' 플래그가 존재한다면 정밀도 너비만큼 가변인자 문자열을 잘라내어 메모리에 저장. 
	// 모든 서식문자에서 ‘-0.*’ 플래그와 최소 필드 너비의 조합을 어떤 조합도 처리할 것이기 때문이다.
	else
		arg = ft_strdup(str);
	//	'.' 플래그가 존재하지 않는다면 가변인자 문자열을 그대로 복제하여 메모리에 저장
    /* 패딩을 고려한 출력및 길이 설정 */
	if (opt->width > 0 && (size_t)opt->width > ft_strlen(arg))
	{
		padding = set_padding(opt->zero, opt->width - ft_strlen(arg));
		arg = set_sorting(opt->minus, arg, padding);
	}
	print_len = ft_putstr_fd(arg, 1);
	free(arg);
	return (print_len);
}

size_t			int_format(int n, t_opt *opt)
//	정수형 데이터 타입 'i', 'd'에 대한 출력 처리를 하는 함수
{
	size_t	print_len;
	char	*sign;		// 가변인자 정수가 음수일 때 부호를 저장할 변수
	char	*arg;		// 가변인자 정수의 절댓값을 저장할 변수

printf("n : %d", n);
    if (n < 0)
        sign = ft_strdup("-");
    else 
        sign = ft_strdup("");
	if (opt->prec == 0 && n == 0)
		arg = ft_strdup("");
		//	'.' 플래그가 존재하면서 정밀도 너비가 0, 가변인자 정수값이 0일 경우 arg를 빈 문자열로 저장한다.
	else if (n < 0)
    arg = ft_itoa((long long)n * -1);
		//	음수인 가변인자 정수 값의 절댓값을 문자열로 변환하여 arg에 저장한다.
	else
		arg = ft_itoa(n);
		//	가변인자 정수 값이 양수일 경우 문자열로만 변환하여 arg에 저장한다.
	arg = applies_to_prec(opt->prec, arg);
	//	정밀도 너비에 따라 가변인자 정수값이 저장되어있는 arg에 정밀도를 적용시킨다.
	arg = applies_to_width(opt, sign, arg);
	//	전체 출력 너비에 따라 패딩 처리 및 부호 위치 조정하는 과정을 수행한다.
	print_len = ft_putstr_fd(arg, 1);
	free(arg);
	return (print_len);
}

size_t			pointer_format(long long n, t_opt *opt)
//	포인터 주소 데이터 타입 'p'를 출력 처리하기 위한 함수. \
	포인터 주소를 long long 형으로 받아오게 된다.
{
	size_t	print_len;
	char	*addr;

	if (n == 0 && opt->prec == 0)
		addr = ft_strdup("");
	// 정밀도 너비가 0이고 가변인자 값이 0일 경우 addr에 빈 문자열을 저장
	else if (n == 0 && opt->prec == -1)
		addr = ft_strdup("0");
	//	'.' 플래그가 존재하지 않고 가변인자 값이 0일 경우 addr에 "0"을 저장
	else
		addr = ft_tobase_n(n, "0123456789abcdef");
	//	포인터 주소 출력에 대한 예외 조건에 부합하지 않는다면 long long 형 가변인자 값을 \
		16진수로 변환하여 addr에 저장한다. 
	addr = applies_to_prec(opt->prec, addr);
	//	정밀도 너비에 따라 가변인자 정수값이 저장되어있는 arg에 정밀도를 적용시킨다.
	addr = ft_strjoin(ft_strdup("0x"), addr);
	//	포인터 주소를 출력할 때 해당 주소는 16진수로 이루어져있다는 것을 나타내기 위해	\
		"0x"를 16진수로 변환된 문자열 addr 앞에 붙여준다.
	addr = applies_to_width(opt, ft_strdup(""), addr);
	//	전체 출력 너비에 따라 패딩 처리하는 과정을 수행한다. \
		포인터 주소도 마찬가지로 부호 문자를 처리할 필요가 없어 부호 문자열 대신 빈 문자열을 넘겨주었다.
	print_len = ft_putstr_fd(addr, 1);
	free(addr);
	return (print_len);
}

size_t			uint_format(unsigned int n, t_opt *opt)
//	부호 없는 정수형 타입을 가변인자로 받는 'u', 'x', 'X' 에 대한 출력 처리를 하는 함수
{
	size_t	print_len;
	char	*arg;

	if (opt->prec == 0 && n == 0)
		arg = ft_strdup("");
	// 정밀도 너비가 0으로 설정되어있고 가변 인자 정수 값이 0일 경우 arg를 빈 문자열로 저장하여 출력한다.
	else if (opt->type == 'u')
		arg = ft_itoa(n);
	// 데이터 타입이 'u'일 경우 단순히 문자열로 변환하여 arg에 저장;
	else if (opt->type == 'x')
		arg = ft_tobase_n(n, "0123456789abcdef");
	else if (opt->type == 'X')
		arg = ft_tobase_n(n, "0123456789ABCDEF");
	// 데이터 타입이 'x' 또는 'X'일 경우 포인터 주소를 부호 없는 정수형으로 가변인자 값을 받아오기 때문에 \
		부호 없는 정수형 가변인자 값을 16진주로 변환하는 ft_tobase_n 함수를 호출한다.
	else
		return (0);
	// 'X'일 경우의 else if문을 else로 설계하여도 되지만 \
		본인은 명시적이고 가독성이 좋은 코드를 선호하기 때문에 번거롭고 코드가 길어지는 것을 감수하고도 \
		5개의 if 문을 만들었다.
	arg = applies_to_prec(opt->prec, arg);
	//	정밀도 너비에 따라 가변인자 정수값이 저장되어있는 arg에 정밀도를 적용시킨다.
	arg = applies_to_width(opt, ft_strdup(""), arg);
	//	전체 출력 너비에 따라 패딩 처리하는 과정을 수행한다. \
		부호 없는 정수형을 출력하기 때문에 부호 문자를 처리할 필요가 없어 부호 문자열 대신 빈 문자열을 넘겨주었다.
	print_len = ft_putstr_fd(arg, 1);
	free(arg);
	return (print_len);
}
