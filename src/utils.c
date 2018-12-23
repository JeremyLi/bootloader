#include "stdint.h"

typedef __builtin_va_list VA_LIST;


#define VA_START(Marker, Parameter)  __builtin_va_start (Marker, Parameter)

#define VA_ARG(Marker, TYPE)         ((sizeof (TYPE) < sizeof (uint32_t)) ? (TYPE)(__builtin_va_arg (Marker, uint32_t)) : (TYPE)(__builtin_va_arg (Marker, TYPE)))

#define VA_END(Marker)               __builtin_va_end (Marker)

typedef int (*fputc_func_t)(int);
extern int uart_put_char(int ch);
//fputc_func_t putchar = uart_put_char;
#define putchar uart_put_char

/*
 * puts : ��ʾ�ַ���
 *  - char *str : �ַ���
 * return : void
 */
int puts( char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        putchar(*str++);
        count++;
    }
    return count;
}

/*
 * number_to_str : ������תΪ�ַ���
 *  - char *buff : ���ݵ�ַ
 *  - int number : ����
 *  - int hex : 10���ƻ�16����
 * return : void
 */
void number_to_str(char *buff, int64_t number, int hex)
{
    char temp[64];
    char num[16] = "0123456789ABCDEF";
    int i = 0;
    // int length = 0;
    int32_t rem;
    char sign = '+';

    temp[i++] = '\0';
    if (number < 0)
    {
        sign = '-';
        number = 0 - number;
    }
    else if (number == 0)
	{
        temp[i++] = '0';
    }
    //������תΪ�ַ���
    while (number > 0)
    {
	rem = number % hex;
	temp[i++] = num[rem];
	number = number / hex;
    }
    //�������
    if (sign == '-')
    {
        *buff++ = '-';
    }
    // length = i;
    //���򿽱���buff������
    i--;
    for (; i >= 0; i--)
    {
       *buff++ = temp[i];
    }
    // *buff = '\0';
}

int __kprintf(const char *fmt, ...)
{
	char ch= ' ';
	VA_LIST args;
	VA_START(args, fmt);
	char buff[256];
	uint64_t count = 0;
	char* str = 0;
	int i = 0;
	for (i=0; i<sizeof(buff); i++) {
		buff[i] = 0;
	}
	//����\0Ϊ����
	while (*fmt != '\0')
	{
        //��ʽ�����%
        if (*fmt == '%')
        {
			//��ʾһ���ַ�
			if ('c' == *(fmt + 1))
			{
				ch = VA_ARG(args, char);
				putchar(ch);
				count++;
				fmt += 2;
			}
			//��ʾ�ַ���
			else if ('s' == *(fmt + 1))
			{
				str = VA_ARG(args, char*);
				count += puts(str);
				fmt += 2;
			}
			//��ʾ����
			else if ('d' == *(fmt + 1))
			{
				number_to_str(buff, VA_ARG(args, int64_t), 10);
				count += puts(buff);
				fmt += 2;
			}
			//��ʾ�޷���16��������
			else if ('x' == *(fmt + 1))
			{
				number_to_str(buff, VA_ARG(args, uint64_t), 16);
				count += puts(buff);
				fmt += 2;
			}
        }
        //��ʾ��ͨ�ַ�
        else
        {
			putchar(*fmt++);
			count++;
        }
	}

	VA_END(args);
	return count;
}



