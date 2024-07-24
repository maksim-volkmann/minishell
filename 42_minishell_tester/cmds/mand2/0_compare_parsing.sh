





# **************************************************************************** #
#                                COMPARE PARSING                               #
# **************************************************************************** #

### comparing your input parsing to bash ###
# 1. Echo the exit code of the last command with double quotes around it
/bin/echo ""$?""

# 2. Echo the exit code of the command "42" (interpreted as a string)
/bin/echo $?"42"

# 3. Echo the literal characters "$?" surrounded by single quotes and followed by "42"
/bin/echo ''$?''"42"

# 4. Echo the value of the environment variable $USER surrounded by double quotes
/bin/echo '"$USER"'

# 5. Echo the value of the environment variable $USER surrounded by single quotes
/bin/echo "'$USER'"

# 6. Echo the literal characters "$USER" surrounded by double quotes
/bin/echo ""'$USER'""

# 7. Echo the value of the environment variable $USER surrounded by single and double quotes
/bin/echo '"'$USER'"'

# 8. Echo the literal characters "''$USER''"
/bin/echo "''$USER''"

# 9. Echo the value of the environment variable $USER surrounded by nested single quotes and double quotes
/bin/echo "'"'$USER'"'"

# 10. Echo the value of the environment variable $USER surrounded by triple single quotes
/bin/echo '"'"$USER"'"'

# 11. Echo the value of the environment variable $HOME followed immediately by the value of $USER (without space)
/bin/echo $"HOME"$USER

# 12. Echo the literal characters "HOM" followed by the value of the environment variable $USER
/bin/echo $"HOM"E$USER

# 13. Echo a concatenated string with variables $?, $USER, and $HOME
/bin/echo "exit_code ->$? user ->$USER home -> $HOME"

# 14. Echo the value of the environment variable $HOME (interpreted as a string)
/bin/echo $"HOME"

# 15. Echo the literal characters "42$"
/bin/echo $"42$"

# 16. Echo the literal characters "$ "
/bin/echo "$ "

# 17. Echo the literal string "hi" to a file "./outfiles/outfile01" and then echo "bye"
/bin/echo hi >./outfiles/outfile01 | /bin/echo bye

# 18. Echo the literal strings "<123 <456 hi" and then echo "42"
/bin/echo <123 <456 hi | /bin/echo 42

# 19. Echo the literal characters "$="
/bin/echo '$='

# 20. Echo the literal characters "$ "
/bin/echo '$ '

# 21. Echo the exit code of the last command
/bin/echo "$?"

# 22. Echo the literal characters "$?"
/bin/echo '$?'

# 23. Echo the literal characters "'$?'"
/bin/echo "'$?'"

# 24. Echo the literal characters "$USER"
/bin/echo \$USER

# 25. Echo the literal characters "\$USER"
/bin/echo \\$USER

# 26. Echo the literal characters "\\$USER"
/bin/echo \\\$USER

# 27. Echo the literal characters "\\\\$USER"
/bin/echo \\\\$USER

# 28. Echo the literal characters "\\\\\$USER"
/bin/echo \\\\\\$USER

# 29. Echo the literal characters "\\\\\\\\$USER"
/bin/echo \\\\\\\\$USER

# 30. Echo the literal characters "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER", $PATH, and \$PWD
/bin/echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

# 31. Echo the literal string "cat lol.c | cat > lol.c"
/bin/echo "cat lol.c | cat > lol.c"

# 32. Echo the literal string "cat lol.c '|' cat > lol.c"
/bin/echo "cat lol.c '|' cat > lol.c"

# 33. Echo the literal characters '$USER', the value of $USER, and the literal string "text  ' text"
/bin/echo '$USER' "$USER" "text  ' text"

# 34. Echo the value of $USER followed by the literal characters "=intergalaktikus miaf*szomez"
/bin/echo $USER =intergalaktikus miaf*szomez

# 35. Echo the literal string "-n" followed by "bonjour"
/bin/echo -n"-n" bonjour

# 36. Echo the literal characters "'$USER'"
/bin/echo "'$USER'"

# 37. Echo the literal characters " '$USER' "
/bin/echo " '$USER' "

# 38. Echo the literal characters "text" followed by the value of $USER
/bin/echo text"$USER"

# 39. Echo the literal characters "text", the value of $USER surrounded by single quotes, and the literal string " $USER "
/bin/echo text"'$USER'" ' $USER '

# 40. Echo the literal characters "text", the value of $USER twice
/bin/echo "text"   "$USER"    "$USER"

# 41. Echo the literal characters "              $USER          "
/bin/echo '              $USER          '

# 42. Echo the literal characters "''''''''''$USER''''''''''"
/bin/echo ''''''''''$USER''''''''''

# 43. Echo the literal characters '""""""""$USER""""""""'
/bin/echo '""""""""$USER""""""""'

# 44. Echo the literal characters ""'""""""$USER""""""'""
/bin/echo ""'""""""$USER""""""'""

# 45. Echo the literal characters """"""""'$USER'""""""""
/bin/echo """"""""'$USER'""""""""

# 46. Echo the literal characters """""""'"$USER"'"""""""
/bin/echo """""""'"$USER"'"""""""

# 47. Echo the literal characters """"""'""$USER""'""""""
/bin/echo """"""'""$USER""'""""""

# 48. Echo the literal characters ""'""'""""$USER""""'""'""
/bin/echo ""'""'""""$USER""""'""'""

# 49. Echo the literal characters '""'""'""""$USER""""'""'""'
/bin/echo '""'""'""""$USER""""'""'""'

# 50. Echo the values of $USER followed by '$USER', and additional literal characters
/bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''

# 51. Echo the literal characters "text", "text" followed by the value of $USER, and literal characters
/bin/echo "text" "text$USER" ... "$USER"

# 52. Echo an empty line
/bin/echo

# 53. Echo an empty string
/bin/echo ''

# 54. Echo an empty string
/bin/echo ""

# 55. Echo an empty single-quoted string followed by an empty double-quoted string
/bin/echo '' ""

# 56. Echo the literal string "/bin/echo"
/bin/echo /bin/echo

# 57. Echo the literal string "test1"
/bin/echo test1

# 58. Echo the literal string "test1" surrounded by single quotes
/bin/echo 'test1'

# 59. Echo the literal string "/bin/echo hallo"
/bin/echo "/bin/echo hallo"

# 60. Echo the literal string "/bin/echo1"
/bin/echo /bin/echo"1"

# 61. Echo the literal strings "test1 test2"
/bin/echo "test1 test2"

# 62. Echo the literal strings "test1  test2" and "test3"
/bin/echo "test1  test2" test3

# 63. Echo the literal string " test1 test2 " and the literal string "test3 "
/bin/echo " test1 test2 " 'test3 '

# 64. Echo the literal string "test1" followed by a tab character and "test2"
/bin/echo test1		test2

# 65. Echo the values of $USER, $TESTNOTFOUND, $HOME, and an empty variable $ (interpreted as strings)
/bin/echo $USER$TESTNOTFOUND$HOME$

# 66. Echo the values of $USER, $TESTNOTFOUND, $HOME, $WTF, and $PWD (interpreted as strings)
/bin/echo $USER$TESTNOTFOUND$HOME$WTF$PWD

# 67. Echo the literal string "test1" without a newline character
/bin/echo -n test1

# 68. Echo the literal strings "test1 test2" without a newline character
/bin/echo -n "test1 test2"

# 69. Echo the literal strings "test1 test2" without a newline character followed by "test3"
/bin/echo -n "test1 test2" test3

# 70. Echo the literal string " test1 test2 " without a newline character and "test3 " with a space
/bin/echo -n " test1 test2 " 'test3 '

# 71. Echo the literal string "test1" followed by a tab character and "test2" without a newline character
/bin/echo -n test1		test2

# 72. Echo the literal string "test1" followed by the literal characters "-n"
/bin/echo test1 -n

# 73. Echo the literal string "test1 -n"
/bin/echo "test1 -n"

# 74. Echo the literal string "-n" without a newline character followed by "test1"
/bin/echo -n -n test1

# 75. Echo the literal string "-n" without a newline character repeated five times followed by "test1"
/bin/echo -n -n -n -n -n test1

# 76. Echo the literal string "  -nn "
/bin/echo "  -nn "

# 77. Echo the literal string "-n test1 -n test2"
/bin/echo "-n test1 -n test2"

# 78. Echo the literal strings "test1 -n test2"
/bin/echo "test1 -n test2"

# 79. Echo the literal string "~42"
/bin/echo ~42

# 80. Echo the literal string "-n -nasd"
/bin/echo -n -n -nasd

# 81. Echo the literal string "-n -n-nnnnn"
/bin/echo -n -n -n-nnnnn

# 82. Echo the literal strings "-nnnnnnn -n -nnn -nnnnn -n-n"
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n-n

# 83. Echo the literal strings "-nnnnnnn -n -nnn -nnnnn -n feel my pain"
/bin/echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain

# 84. Echo the literal string "-n -n-n"
/bin/echo -n -n -n-n

# 85. Echo the literal characters "'totally logical'"
/bin/echo "'totally logical'"

# 86. Echo the literal characters "totally logical" surrounded by single quotes
/bin/echo 'totally logical'

# 87. Echo the literal characters "totally logical"
/bin/echo ''totally logical''

# 88. Echo the literal characters "totally logical"
/bin/echo ""'totally logical'""
