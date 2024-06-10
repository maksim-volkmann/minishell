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


