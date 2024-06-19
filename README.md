# minishell


//TODO: check for 'EOF' and "EOF" and EOF. It saves with quotation marks.
```
bash-3.2$ cat << 'EOF'
> aaa
> "EOF"
> 'EOF'
> EOF
aaa
"EOF"
'EOF'
bash-3.2$
```

To Do:

-History

-Signals

-Heredoc

-Finish lexer and parsing

-Exit codes

-Segfault when setting input without command

-How to organize

## TESTER:
To install the script, copy and run following command:
```bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)"```


## TODO:

1. Need to modify my own env to be able to use in execve.
// TEST: echo -- -n "Hello, world!"
