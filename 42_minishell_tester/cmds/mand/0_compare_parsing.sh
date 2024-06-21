# **************************************************************************** #
#                                COMPARE PARSING                               #
# **************************************************************************** #

### comparing your input parsing to bash ###
# Test 1
/bin/echo ""$?""

# Test 2
/bin/echo $?"42"

# Test 3
/bin/echo ''$?''"42"

# Test 4
/bin/echo '"$USER"'

# Test 5
/bin/echo "'$USER'"

# Test 6
/bin/echo ""'$USER'""

# Test 7
/bin/echo '"'$USER'"'

# Test 8
/bin/echo "''$USER''"

# Test 9
/bin/echo "'"'$USER'"'"

# Test 10
/bin/echo '"'"$USER"'"'

# Test 11
/bin/echo $"HOME"$USER

# Test 12
/bin/echo $"HOM"E$USER

# Test 13
/bin/echo "exit_code ->$? user ->$USER home -> $HOME"

# Test 14
/bin/echo $"HOME"

# Test 15
/bin/echo $"42$"

# Test 16
/bin/echo "$ "

# Test 17
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye

# Test 18
/bin/echo <123 <456 hi | /bin/echo 42

# Test 19
/bin/echo '$='

# Test 20
/bin/echo '$ '

# Test 21
/bin/echo "$?"

# Test 22
/bin/echo '$?'

# Test 23
/bin/echo "'$?'"

# Test 24
/bin/echo \$USER

# Test 25
/bin/echo \\$USER

# Test 26
/bin/echo \\\$USER

# Test 27
/bin/echo \\\\$USER

# Test 28
/bin/echo \\\\\$USER

# Test 29
/bin/echo \\\\\\\\\$USER

# Test 30
/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

# Test 31
/bin/echo "cat lol.c | cat > lol.c"

# Test 32
/bin/echo "cat lol.c '|' cat > lol.c"

# Test 33
/bin/echo '$USER' "$USER" "text  ' text"

# Test 34
/bin/echo $USER =intergalaktikus miaf*szomez

# Test 35
/bin/echo -n"-n" bonjour

# Test 36
/bin/echo "'$USER'"

# Test 37
/bin/echo " '$USER' "

# Test 38
/bin/echo text"$USER"

# Test 39
/bin/echo text"'$USER'" ' $USER '

# Test 40
/bin/echo "text"   "$USER"    "$USER"

# Test 41
/bin/echo '              $USER          '

# Test 42
/bin/echo ''''''''''$USER''''''''''

# Test 43
/bin/echo """"""""$USER""""""""

# Test 44
/bin/echo '""""""""$USER""""""""'

# Test 45
/bin/echo ""'""""""$USER""""""'""

# Test 46
/bin/echo """"""""'$USER'""""""""

# Test 47
/bin/echo """""""'"$USER"'"""""""

# Test 48
/bin/echo """"""'""$USER""'""""""

# Test 49
/bin/echo ""'""'""""$USER""""'""'""

# Test 50
/bin/echo '""'""'""""$USER""""'""'""'

# Test 51
/bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''

# Test 52
/bin/echo "text" "text$USER" ... "$USER"

# Test 53
/bin/echo

# Test 54
/bin/echo ''

# Test 55
/bin/echo ""

# Test 56
/bin/echo '' ""

/bin/echo /bin/echo

# Test 57
/bin/echo test1

# Test 58
/bin/echo 'test1'

# Test 59
/bin/echo "/bin/echo hallo"

# Test 60
/bin/echo /bin/echo"1"

# Test 61
/bin/echo "test1 test2"

# Test 62
/bin/echo "test1  test2" test3

# Test 63
/bin/echo " test1 test2 " 'test3 '

# Test 64
/bin/echo test1		test2

# Test 65
/bin/echo $USER$TESTNOTFOUND$HOME$

# Test 66
/bin/echo $USER$TESTNOTFOUND$HOME$WTF$PWD

# Test 67
/bin/echo -n test1

# Test 68
/bin/echo -n "test1 test2"

# Test 69
/bin/echo -n "test1 test2" test3

# Test 70
/bin/echo -n " test1 test2 " 'test3 '

# Test 71
/bin/echo -n test1		test2

# Test 72
/bin/echo test1 -n

# Test 73
/bin/echo "test1 -n"

# Test 74
/bin/echo -n -n test1

# Test 75
/bin/echo -n -n -n -n -n test1

# Test 76
/bin/echo "  -nn "

# Test 77
/bin/echo "-n test1 -n test2"

# Test 78
/bin/echo "test1 -n test2"

# Test 79
/bin/echo ~42

# Test 80
/bin/echo -n -n -nasd

# Test 81
/bin/echo -n -n -n-nnnnn

# Test 82
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n-n

# Test 83
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain

# Test 84
/bin/echo -n -n -n-n

# Test 85
/bin/echo "'totally logical'"

# Test 86
/bin/echo 'totally logical'

# Test 87
/bin/echo ''totally logical''

# Test 88
/bin/echo ""'totally logical'""
