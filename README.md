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
// TEST: echo -- -n "Hello, world!"

[A-Z][a-z][_]

bash-3.2$ /bin/echo "$123123"
23123

----------------------

mvolkman$USERtext oui oui oui oui mvolkman oui mvolkman
mvolkman$USERtext oui oui oui oui mvolkman oui mvolkman [SPACE HERE]

there should a space at the end.

minishell> echo '' ""

minishell>
bash-3.2$ echo '' ""
[SPACE HERE]
bash-3.2$
bash-3.2$ /bin/echo $USER$TESTNOTFOUND$HOME$
adrherna/Users/adrherna$

This should not be interpreted as redirection:
minishell> ">>" asd          <- this is done



this segfault happens when redirecting with no existing command.
also like this:
minishell> >> efe

------


 ctrl + \ . - interrupting running processes


#REDIRECTIONS seg faults
24


echo
Echo
ECho
ECHo
ECHO
eCHO
ecHO
echO
EchO
eCHo

pwd
PWD
Pwd
PWd
pWD

env
ENV
Env
ENv
eVN


-----


ALL ERROR CODES.
FORBIDDEN FUNCTIONS.
NORMINETTE
EXPLANATIONS.
REFACTORING.
