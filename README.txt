To handle:

´ ´ 		-> Single quotes.
" " 		-> Double quotes.
< > << >> 	-> Redirections. Already done in pipex, just implement it again for minishell
| 			-> Pipes. Handled in pipex already
$? 			-> exit status code
$name		-> environment variables
Ctrl-C-D-\	-> should behave like in bash

Builtins:

echo (-n)
cd (relative or absolute path)
pwd
export
unset
env
exit

receiving data in this format:
r
Linked list containing every word and its type:

< Makefile cat | wc -l > outfile

i would receive:
< 			Redirection
Makefile 	Word
cat 		Word
| 			Pipe
wc 			Word
-l 			Word
> 			Redirection
outfile 	Word
