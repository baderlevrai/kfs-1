#include "kernel.h"
#include <stdarg.h>

void  print_char(char c, size_t *len)
{
  (*len)++;
  terminal_wchar(c);
}

void print_str(char *str, size_t *len)
{
  *len = *len + strlen(str);
  terminal_wstr(str);
}

void print_nb(int nb, size_t *len)
{
	char	temp;

	if (nb < 0)
	{
		terminal_wchar('-');
    (*len)++;
		if (nb == -2147483648)
    {
      terminal_wstr("214748364");
      *len = *len + 9;
			nb = -8;
		}
		nb = nb * -1;
	}
	if (nb > 9)
	{
		print_nb((nb - (nb % 10)) / 10, len);
		nb = (nb % 10);
	}
  terminal_wchar(48 + nb);
  (*len)++;
}

uint8_t  handle_format(char c, size_t *len, va_list args)
{
  size_t old_len = *len;

  if (c == 'c')
    print_char(va_arg(args, int), len);
  if (c == 's')
    print_str(va_arg(args, char *), len);
  if (c == 'd' || c == 'i')
    print_nb(va_arg(args, int), len);
  if (old_len == *len)
    return (0);
  return (1);
}

int printk(const char *format, ...)
{
  size_t  index = 0;
  size_t  len = 0;
  va_list args;

  va_start(args, format);
  if (!format)
    return (-1);
  while (format[index])
  {
    if (format[index] != '%')
    {
      terminal_wchar(format[index]);
      len++;
    }
    else
    {
      index++;
      if (!handle_format(*(format + index), &len, args))
        return (-1);
    }
    index++;
  }
  va_end(args);
  return (len);
}
