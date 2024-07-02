# minishell

//TODO: check for 'EOF' and "EOF" and EOF. It saves with quotation marks.

To Do:

-Signals

-Heredoc

-Finish lexer and parsing

-Exit codes

-How to organize Makefile

export and env is different
export starts at: declare -x
if you "unset PATH" you should not access the "env", because env is part of "PATH" in real bash.

## TESTER:
To install the script, copy and run following command:
```bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)"```



## TODO:

1. Need to modify my own env to be able to use in execve.

 ctrl + \ . - interrupting running processes


#REDIRECTIONS

---------->this runs only the second command:
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye

----------> this doesnt run at all:
ls >./outfiles/outfile01
