# A simple script for compiling and running the c file as input
name="${1%.c}" # strips the .c so I can tab the name :)
gcc -g -fsanitize=address,undefined -Wall -Wextra -o "$name" "$name".c && ./"$name"
