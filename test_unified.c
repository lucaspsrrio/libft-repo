/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unified.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lupalhan <lupalhan@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:13:06 by lupalhan          #+#    #+#             */
/*   Updated: 2025/11/30 21:14:24 by lupalhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <type.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include "libft.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define RESET "\033[0m"

int g_tests_passed = 0;
int g_tests_total = 0;

void check(int condition, const char *test_name)
{
	g_tests_total++;
	if (condition)
	{
		printf("%s[OK] %s%s\n", GREEN, test_name, RESET);
		g_tests_passed++;
	}
	else
		printf("%s[KO] %s%s\n", RED, test_name, RESET);
}

void test_char_funcs()
{
	printf("\n=== CHAR FUNCTIONS ===\n");
	check(ft_isalpha('a') && !ft_isalpha('1'), "ft_isalpha");
	check(ft_isdigit('1') && !ft_isdigit('a'), "ft_isdigit");
	check(ft_isalnum('a') && ft_isalnum('1') && !ft_isalnum('!'), "ft_isalnum");
	check(ft_isascii(127) && !ft_isascii(128), "ft_isascii");
	check(ft_isprint(32) && ft_isprint(126) && !ft_isprint(31), "ft_isprint");
	check(ft_toupper('a') == 'A' && ft_toupper('1') == '1', "ft_toupper");
	check(ft_tolower('A') == 'a' && ft_tolower('1') == '1', "ft_tolower");
}

void test_str_mem()
{
	printf("\n=== STRING & MEMORY ===\n");
	
	/* Strlen */
	check(ft_strlen("123") == 3, "ft_strlen");

	/* Memset & Bzero */
	char buff[10];
	ft_bzero(buff, 10);
	check(buff[0] == 0 && buff[9] == 0, "ft_bzero");
	ft_memset(buff, 'A', 5);
	check(buff[0] == 'A' && buff[4] == 'A' && buff[5] == 0, "ft_memset");

	/* Memcpy & Memmove */
	char src[] = "hello";
	char dst[10];
	ft_memcpy(dst, src, 6);
	check(strcmp(dst, "hello") == 0, "ft_memcpy");
	
	char move_buff[] = "0123456789";
	ft_memmove(move_buff + 4, move_buff + 3, 3); // Move '345' to index 4
	check(strcmp(move_buff, "0123345789") == 0, "ft_memmove overlap");

	/* Strlcpy & Strlcat */
	char lcpy_dst[10];
	size_t ret = ft_strlcpy(lcpy_dst, "hello", 3); // Copies "he" + null
	check(strcmp(lcpy_dst, "he") == 0 && ret == 5, "ft_strlcpy");
	
	char lcat_dst[20] = "Hello";
	ret = ft_strlcat(lcat_dst, " World", 20);
	check(strcmp(lcat_dst, "Hello World") == 0 && ret == 11, "ft_strlcat normal");
	
	/* Strchr & Strrchr */
	check(ft_strchr("abc", 'b') != NULL, "ft_strchr found");
	check(ft_strchr("abc", 'z') == NULL, "ft_strchr not found");
	check(ft_strchr("abc", 0) != NULL, "ft_strchr null term");
	check(ft_strrchr("abbc", 'b') != NULL, "ft_strrchr");

	/* Strncmp & Memcmp */
	check(ft_strncmp("abc", "abd", 2) == 0, "ft_strncmp equal n");
	check(ft_strncmp("abc", "abd", 3) != 0, "ft_strncmp diff");
	check(ft_memcmp("abc", "abd", 3) != 0, "ft_memcmp");

	/* Strnstr */
	check(ft_strnstr("lorem ipsum", "ipsum", 15) != NULL, "ft_strnstr found");
	check(ft_strnstr("lorem ipsum", "ipsum", 5) == NULL, "ft_strnstr limit");

	/* Atoi */
	check(ft_atoi("  -42") == -42, "ft_atoi whitespace/sign");
	check(ft_atoi("0") == 0, "ft_atoi zero");
	check(ft_atoi("2147483647") == 2147483647, "ft_atoi int_max");

	/* Calloc & Strdup */
	int *p = ft_calloc(5, sizeof(int));
	check(p[0] == 0 && p[4] == 0, "ft_calloc");
	free(p);
	char *d = ft_strdup("dup");
	check(strcmp(d, "dup") == 0, "ft_strdup");
	free(d);
}

char map_func(unsigned int i, char c) { (void)i; return c + 1; }
void iter_func(unsigned int i, char *c) { (void)i; *c = *c + 1; }

void test_additional()
{
	printf("\n=== ADDITIONAL FUNCTIONS ===\n");
	
	/* Substr */
	char *sub = ft_substr("hello world", 6, 5);
	check(strcmp(sub, "world") == 0, "ft_substr");
	free(sub);

	/* Strjoin */
	char *join = ft_strjoin("40", "2");
	check(strcmp(join, "402") == 0, "ft_strjoin");
	free(join);

	/* Strtrim */
	char *trim = ft_strtrim("  xxhelloxx  ", " x");
	check(strcmp(trim, "hello") == 0, "ft_strtrim");
	free(trim);

	/* Split */
	char **split = ft_split("hello!world!", '!');
	check(strcmp(split[0], "hello") == 0, "ft_split 1");
	check(strcmp(split[1], "world") == 0, "ft_split 2");
	check(split[2] == NULL, "ft_split null");
	free(split[0]); free(split[1]); free(split);

	/* Itoa */
	char *n = ft_itoa(-123);
	check(strcmp(n, "-123") == 0, "ft_itoa negative");
	free(n);

	/* Strmapi & Striteri */
	char *mapi = ft_strmapi("abc", map_func);
	check(strcmp(mapi, "bcd") == 0, "ft_strmapi");
	free(mapi);

	char iter_str[] = "abc";
	ft_striteri(iter_str, iter_func);
	check(strcmp(iter_str, "bcd") == 0, "ft_striteri");
}

void test_fd()
{
	printf("\n=== FD FUNCTIONS (Visual Check Required) ===\n");
	printf("Printing 'X' to stdout... ");
	ft_putchar_fd('X', 1);
	printf("\nPrinting 'Test' to stdout... ");
	ft_putstr_fd("Test", 1);
	printf("\nPrinting 'Line' with newline... ");
	ft_putendl_fd("Line", 1);
	printf("Printing number -42... ");
	ft_putnbr_fd(-42, 1);
	printf("\n[OK] FD Functions executed (check output above)\n");
}

int main(void)
{
	printf("==================================\n");
	printf("      LIBFT AUTOMATED TESTER      \n");
	printf("==================================\n");

	test_char_funcs();
	test_str_mem();
	test_additional();
	test_fd();

	printf("\n==================================\n");
	printf("RESULT: %d/%d tests passed.\n", g_tests_passed, g_tests_total);
	if (g_tests_passed == g_tests_total)
		printf("%sALL TESTS PASSED PERFECTLY!%s\n", GREEN, RESET);
	else
		printf("%sSOME TESTS FAILED!%s\n", RED, RESET);
	
	return (0);
}
