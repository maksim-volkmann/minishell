# **************************************************************************** #
#                                    REDIRS                                    #
# **************************************************************************** #

#1
grep hi <./test_files/infile
#2
grep hi "<infile" <         ./test_files/infile
#3
grep hi <./test_files/infile_big <./test_files/infile
#4
cat <"./test_files/file name with spaces"
#5
cat <./test_files/infile_big ./test_files/infile
#6
cat <"1""2""3""4""5"
#7
cat <"./test_files/infile"
#8
echo <"./test_files/infile_big" | cat <"./test_files/infile"
#9
echo <"./test_files/infile_big" | cat "./test_files/infile"
#10
echo hi | cat <"./test_files/infile"
#11
echo hi | cat "./test_files/infile"
#12
cat <"./test_files/infile" | echo hi
#13
cat <"./test_files/infile" | grep hello
#14
cat <"./test_files/infile_big" | echo hi
#15
cat <missing
#16
cat <missing | cat
#17
cat <missing | echo oi
#18
cat <missing | cat <"./test_files/infile"
#19
echo <123 <456 hi | echo 42
#20
ls >./outfiles/outfile01
#21
ls >         ./outfiles/outfile01
#22
ls >./outfiles/outfile01 >./outfiles/outfile02
#23
ls >./outfiles/outfile01 >./test_files/invalid_permission
#24
ls >"./outfiles/outfile with spaces"
#25
ls >"./outfiles/outfile""1""2""3""4""5"
#26
ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
#27
ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
#28
cat <"./test_files/infile" >"./outfiles/outfile01"
#29
echo hi >./outfiles/outfile01 | echo bye
#30
echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
#31
echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
#32
echo hi >./test_files/invalid_permission | echo bye
#33
echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
#34
cat <"./test_files/infile" >./test_files/invalid_permission
#35
cat >./test_files/invalid_permission <"./test_files/infile"
#36
cat <missing >./outfiles/outfile01
#37
cat >./outfiles/outfile01 <missing
#38
cat <missing >./test_files/invalid_permission
#39
cat >./test_files/invalid_permission <missing
#40
cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
#41
ls >>./outfiles/outfile01
#42
ls >>      ./outfiles/outfile01
#43
ls >>./outfiles/outfile01 >./outfiles/outfile01
#44
ls >./outfiles/outfile01 >>./outfiles/outfile01
#45
ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
#46
ls >>./outfiles/outfile01 >>./outfiles/outfile02
#47
ls >>./test_files/invalid_permission
#48
ls >>./test_files/invalid_permission >>./outfiles/outfile01
#49
ls >>./outfiles/outfile01 >>./test_files/invalid_permission
#50
ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
#51
ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
#52
ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
#53
echo hi >>./outfiles/outfile01 | echo bye
#54
echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
#55
echo hi >>./test_files/invalid_permission | echo bye
#56
echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
#57
cat <minishell.h>./outfiles/outfile
#58
cat <minishell.h|ls

### SIMPLE ###
/bin/echo 42 > tmp_redir_out 42
cat tmp_redir_out
rm tmp_redir_out

/bin/echo "cat this text\n" > tmp_redir_out
cat <tmp_redir_out
rm tmp_redir_out

cat | cat | ls

cat < /dev/null

/bin/echo 42 > /dev/null

/bin/echo 42 >> /dev/null

### OVERWRITE ###
/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

/bin/echo 42 > tmp_redir_out > tmp_redir_out1 > tmp_redir_out2 > tmp_redir_out3
/bin/echo 0
cat tmp_redir_out
/bin/echo 1
cat tmp_redir_out1
/bin/echo 2
cat tmp_redir_out2
/bin/echo 3
cat tmp_redir_out3
rm tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3

/bin/echo 42 > /dev/null > tmp_redir_out
/bin/echo 2 >> /dev/null >> tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

### PERMISSION DENIED ###
touch tmp_redir_out_file1
chmod -r tmp_redir_out_file1
/bin/echo 1 > tmp_redir_out tmp_redir_out_file1

/bin/grep 1 < inputfile

/bin/grep 1 < NO_SUCH_FILE

/bin/grep 1 < inputfile < inputfile

/bin/grep 1 < NO_SUCH_FILE < inputfile

rm -f tmp_std_outfile

rm -f tmp_std_outfile

rm -f tmp_std_outfile

/bin/echo 1 >/dev/null | /usr/bin/grep 1

/bin/echo 1 >/dev/null | /bin/echo 2

/bin/echo >/dev/null 1 | /usr/bin/grep 1

/bin/echo >/dev/null 1 | /bin/echo 2

### HERE_DOC ###
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

<<lim cat
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF

cat << hello
$USER
$NOVAR
$HOME
hello

cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << "lim"
$USER
$NOVAR
$HOME
lim

cat << 'lim'
$USER
$NOVAR
$HOME
lim

> out
/bin/rm -f out

< out
/bin/rm -f out

>> out
/bin/rm -f out
