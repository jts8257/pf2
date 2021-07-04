#include "head.h"

char	*set_padding(size_t zero_flag, size_t size)
//	padding 문자열을 만들 메모리 공간을 확보하고 \
	'0' 플래그 존재 유무와 너비 값에 따라 패딩 문자열을 만든다.
{
	char	*padding;
	
	if (size < 0) {
		padding = ft_strdup("");
		return padding;
	}
	padding = (char *)calloc(sizeof(char),size + 1);
	//	ft_calloc 함수를 통해 size 와 '\0' 문자 1 byte 를 더한 만큼 메모리 공간을 할당.  
	if (zero_flag == 0)
		ft_memset(padding, ' ', size);
	//	'0' 플래그가 존재하지 않았다면 ft_memset 함수를 통해 \
		' ' 문자를 할당된 메모리 공간에 채운다.
	else
		ft_memset(padding, '0', size);
	//	'0' 플래그가 존재한다면 ft_memset 함수를 통해 \
		'0' 문자를 할당된 메모리 공간에 채운다.
	return (padding);
}

char	*set_sorting(size_t mns_flg, char *arg, char *padding)
{
	char	*result;
		//	'-' 플래그가 존재하지 않는다면 ft_strjoin 함수를 통해 \
			 padding 문자열을 기준으로 가변 인자 문자열을 합쳐 우측 정렬을 적용시킨다.
	if (mns_flg == 0)
		result = ft_strjoin(padding, arg);
	else
		result = ft_strjoin(arg, padding);
		//	'-' 플래그가 존재한다면 ft_strjoin 함수를 통해 \
			 가변 인자 문자열을 기준으로 padding 문자열을 합쳐 좌측 정렬을 적용시킨다.
	return (result);
}

char	*applies_to_prec(int prec, char *arg)
{
	char	*padding;

	if (prec > -1 && (size_t)prec > ft_strlen(arg))
	//	'.' 플래그가 존재하고 정밀도의 너비가 가변인자 정수 값의 길이보다 클 경우 정밀도를 적용시킨다.
	{
		padding = set_padding(1, prec - ft_strlen(arg));
		//	첫번째 매개변수 '0' 플래그 값을 1로 넘겨주어 무조건 '0'으로 패딩 처리하도록 set_padding 함수를 호출
		arg = set_sorting(0, arg, padding);
		//	첫번째 매개변수 '-' 플래그 값을 0으로 넘겨주어 무조건 우측 정렬을 기준으로 처리하도록 set_sorting 함수를 호출
	}
	return (arg);
}

char	*applies_to_width(t_opt *opt, char *sign, char *arg)
{
	char	*padding;

	if (opt->width > 0 &&
			(size_t)opt->width > (ft_strlen(sign) + ft_strlen(arg)) &&
			opt->width > opt->prec)
	//	전체 출력 너비값이 arg 길이와 부호 문자 1byte 길이를 더한 값보다 크면서 정밀도 너비보다도 커야한다.
	{
		padding = set_padding(opt->zero,
				opt->width - (ft_strlen(sign) + ft_strlen(arg)));
		//	 전체 출력 너비 값에서 부호 문자와 가변인자 문자열 길이를 합한 값을 뺀 만큼 패딩 문자열을 만든다.
		if (opt->zero == 1)
			padding = ft_strjoin(sign, padding);
		//	'0' 플래그가 존재한다면 부호 문자를 기준으로 패딩 문자열을 합쳐서 부호 문자를 가장 먼저 출력하도록 한다.
		//	|-000015|
		else
			arg = ft_strjoin(sign, arg);
		//	'0' 플래그가 존재하지 않는다면 절댓값 가변 인자 정수 값에 다시 부호를 붙인다.
		//	|    -15|
		arg = set_sorting(opt->minus, arg, padding);
		//	'minus' 플래그에 따른 부호 위치 조정 및 패딩 문자열을 붙이고나서 \
		 '-' 플래그에 따라 좌측 또는 우측 정렬을 적용시킨다.
	}
	else
		arg = ft_strjoin(sign, arg);
	//	if문에서 전체 출력 너비 값 조건에 부합하지 않는다면 \
		단순히 부호와 가변 인자 문자열을 조합한다. 
	return (arg);
}

//	ft_tobase_n.c	(La Piscine 과정에서 작업한 ft_putnbr_base.c 파일을 일부 수정하여 만듦)
int		ft_dupl_check(char *str, int length)
//	진수 표현 문자들중 중복된 문자들의 유무를 체크해주는 함수
{
	int i;
	int j;

	i = 0;
	j = i + 1;	// 없어도 될 것 같다.
	/* 첫 번째 인덱스 문자를 기준으로 나머지 문자들과의 중복 체크를 하고
		기준이 되는 인덱스를 1씩 증가시키며 반복 비교 	*/
	while (i < length - 1)
	{
		j = i + 1;
		while (j < length)
		{
			if (str[i] == str[j])
				return (1);
			//	만약 중복되는 문자들이 존재한다면 1을 리턴하여 함수 종료
			j++;
		}
		i++;
	}
	return (0);
}

static	char	*ft_putnbr(long long nbr, char *base,
		int base_count, char *result)
//	nbr : 변환될 대상 값
//	base : 진수 표현 문자열
//	base_count : 진수 표현 문자 수
//	result : 최종 변환된 결과를 문자열로 저장할 변수
{
	char	*hex;

	if (nbr >= 0)	// ft_printf 에서는 절댓값만을 nbr로 넘겨주기 때문에 없어도 되는 문장
	//	음수에 대한 처리는 구현하지 않음
	{
		if (nbr / base_count < base_count)
		//	나눈 값이 base_count 보다 작으면 바로 진법 표현이 가능하다.
		{
			if (nbr / base_count != 0)
			//	nbr이 base_count 보다 작은 값일 경우 \
				여기서 문자 추출 및 병합 과정을 수행하지 않고 \
				밑에 if, else 문 다음 과정으로 넘긴다.
			{
				hex = ft_substr(base, nbr / base_count, 1);
				//	ft_substr 함수를 통해 base 문자열에서 \
					나눈 값의 인덱스 문자를 추출하여 hex에 저장
				result = ft_strjoin(result, hex);
				//	추출한 문자를 result 와 병합
			}
		}
		else
			result = ft_putnbr(nbr / base_count, base, base_count, result);
		// 나눈 값이 base_count보다 크거나 같다면 \
			 나눈 값을 다시 변환 대상 값으로 재귀 함수 호출

		hex = ft_substr(base, nbr % base_count, 1);
		// base 문자열에서 나머지 값의 인덱스 문자를 추출하여 hex에 저장
		result = ft_strjoin(result, hex);
		// 나눈 값의 인덱스 문자와 나머지 값의 인덱스 문자를 병합
	}
	return (result);
}

char			*ft_tobase_n(long long n, char *base)
{
	char	*result;
	int		base_count;

	base_count = 0;
	while (base[base_count] != '\0')
	{
		if (base[base_count] == '-' || base[base_count] == '+')
		{
			ft_putchar_fd('\0', 1);
			return (NULL);
		}
		base_count++;
		//	진수 표현 문자들 중 '-', '+' 문자들이 포함되어있다면 NULL 리턴 함수 종료
	}
	if (base_count < 2)	// 이진법보다 진수 표현 수가 작으면 NULL 리턴 함수 종료
		return (NULL);
	else if (ft_dupl_check(base, base_count))	// 진수 표현 문자 중복 체크
		return (NULL);
	else
	{
		result = ft_calloc(sizeof(char), 1); 
		// result 1byte 만큼 메모리 공간 할당 및 '\0'(ft_bzero) 초기화
		result = ft_putnbr(n, base, base_count, result);
		// 진수 변환 시작
	}
	return (result);
}

t_opt			*init_opt() {
	t_opt *opt = malloc(sizeof(t_opt));
	if (!opt)
	return 0;
	opt->minus = 0;
	opt->zero = 0;
	opt->width = 0;
	opt->prec = -1;
	opt->type = 0;
	return opt;
}

int		in_format(char c) 
{
	char	*types;
	int		i;
	
	i = 0;
	types = ft_strdup("csidpuxX%");
	while (types[i])
	{
		if (types[i] == c)
		{
			free(types);
			return (1);
		}
		i++;
	}
	free(types);
	return (0);
}