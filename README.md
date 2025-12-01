# Libft

Implementação da biblioteca padrão C.

## 1. Compilar

Gera o arquivo `libft.a`:

make

## 2. Rodar Teste

1. Salve o arquivo `test_unified.c` na raiz.
2. Execute:

make re
gcc -Wall -Wextra -Werror test_unified.c -L. -lft -o tester
./tester
