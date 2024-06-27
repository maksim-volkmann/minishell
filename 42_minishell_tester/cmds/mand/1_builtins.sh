# Test 1
echo cd ~ //1

# Test 2
echo "cd ~"

# Test 3
echo ""$?""

# Test 4
echo $?"42"

# Test 5
echo ''$?''"42"

# Test 6
echo '"$USER"'

# Test 7
echo "'$USER'"

# Test 8
echo ""'$USER'""

# Test 9
echo '"'$USER'"'

# Test 10
echo "''$USER''"

# Test 11
echo "'"'$USER'"'"

# Test 12
echo '"'"$USER"'"'

# Test 13
echo $"HOME"$USER

# Test 14
echo $"HOM"E$USER

# Test 15
echo "exit_code ->$? user ->$USER home -> $HOME"

# Test 16
echo $"HOME"

# Test 17
echo $"42$"

# Test 18
echo """"""""$USER""""""""

# Test 19
echo "$ "

# Test 20
echo hi >./outfiles/outfile01 | echo bye

# Test 21
echo <123 <456 hi | echo 42

# Test 22
echo '$='

# Test 23
echo '$ '

# Test 24
echo "$?"

# Test 25
echo '$?'

# Test 26
echo "'$?'"

# Test 27
echo \$USER

# Test 28
echo \\$USER

# Test 29
echo \\\$USER

# Test 30
echo \\\\$USER

# Test 31
echo \\\\\$USER

# Test 32
echo \\\\\\\\\$USER

# Test 33
echo \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\$USER \$PATH \\$PWD

# Test 34
echo "cat lol.c | cat > lol.c"

# Test 35
echo "cat lol.c '|' cat > lol.c"

# Test 36
echo '$USER' "$USER" "text  ' text"

# Test 37
echo $USER =intergalaktikus miaf*szomez

# Test 38
echo -n"-n" bonjour

# Test 39
echo "'$USER'"

# Test 40
echo " '$USER' "

# Test 41
echo text"$USER"

# Test 42
echo text"'$USER'" ' $USER '

# Test 43
echo "text"   "$USER"    "$USER"

# Test 44
echo '              $USER          '

# Test 45
echo ''''''''''$USER''''''''''

# Test 46
echo """"""""$USER""""""""

# Test 47
echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''

# Test 48
echo "text" "text$USER" ... "$USER"

# Test 49
echo

# Test 50
echo ''

# Test 51
echo ""

# Test 52
echo '' ""

# Test 53
echo echo

# Test 54
echo test1

# Test 55
echo 'test1'

# Test 56
echo "echo hallo"

# Test 57
echo echo"1"

# Test 58
echo "test1 test2"

# Test 59
echo "test1  test2" test3

# Test 60
echo " test1 test2 " 'test3 '

# Test 61
echo test1		test2

# Test 62
echo $USER$TESTNOTFOUND$HOME$

# Test 63
echo $USER$TESTNOTFOUND$HOME$WTF$PWD

# Test 64
echo -n test1

# Test 65
echo -n "test1 test2"

# Test 66
echo -n "test1 test2" test3

# Test 67
echo -n " test1 test2 " 'test3 '

# Test 68
echo -n test1		test2

# Test 69
echo test1 -n

# Test 70
echo "test1 -n"

# Test 71-
echo -n -n test1

# Test 72-
echo -n -n -n -n -n test1

# Test 73
echo -
echo --

# Test 74
echo "  -nn "

# Test 75
echo "-n test1 -n test2"

# Test 76
echo "test1 -n test2"

# Test 77
echo ~42

# Test 78
echo -n -n -nasd

# Test 79
echo -n -n -n-nnnnn

# Test 80
echo -n -nnnnnnn -n -nnn -nnnnn -n-n

# Test 81
echo -n -nnnnnnn -n -nnn -nnnnn -n feel my pain

# Test 82
echo -n -n -n-n

# Test 83
echo "'totally logical'"

# Test 84
echo 'totally logical'

# Test 85
echo ''totally logical''

# Test 86
echo ""'totally logical'""

# Test 87
eCho

# Test 88
eChO

# Test 89
eCHO

# Test 90
ECHO

### CD ###
# Test 91
pwd
cd
pwd

# Test 92
pwd
cd ..
pwd

# Test 93
cd ..
cd $OLDPWD

# Test 94
pwd
cd .
pwd

# Test 95
pwd
cd "."
pwd

# Test 96
pwd
cd /Users
pwd

# Test 97
pwd
cd //////
pwd

# Test 98
pwd
cd ./././
pwd

# Test 99
pwd
cd /
pwd

# Test 100
pwd
cd '/////'
pwd

# Test 101
pwd
cd "$PWD/file_tests"
pwd

# Test 102
cd '/////' 2>/dev/null

# Test 103
cd '/etc'

# Test 104
cd '/var'

# Test 105
cd "doesntexist" 2>/dev/null

# Test 106
cd ../../..

# Test 107
cd "wtf" 2>/dev/null

# Test 108
cd ?

# Test 109
cd +

# Test 110
cd _

# Test 111
cd woof

# Test 112
cd bark bark

# Test 113
cd '/'

# Test 114
pwd
cd "doesntexist"
pwd

# Test 115
pwd
cd "doesntexist"
pwd

# Test 116
pwd
cd ../../..
pwd

# Test 117
pwd
cd "wtf"
pwd

# Test 118
pwd
cd ..
cd ..
pwd

# Test 119
pwd
cd ?
pwd

# Test 120
pwd
cd +
pwd

# Test 121
pwd
cd _
pwd

# Test 122
cd ../../
cd -
cd -

# Test 123
pwd
cd echo
pwd

# Test 124
pwd
cd echo echo
pwd

# Test 125
pwd
cd '/'
pwd

# Test 126
pwd
cd $PWD/file_tests
pwd

# Test 127
pwd
cd $OLDPWD/something
pwd

# Test 128
pwd
cd ~
cd - ananas dot jpeg
pwd

# Test 129
pwd
cd includes/ djhwbdhwbd wgdyuhgw jdwjdh wuiydjwh
pwd

# Test 130
pwd
cd ~ asd w dd q asd
pwd

# Test 131
pwd
cd ~
cd -
pwd

# Test 132
pwd
cd -
pwd

# Test 133
pwd
cd ~
pwd

# Test 134
pwd
cd ../libft
pwd

# Test 135
pwd
cd ../libft ojid iowjiojwoid joijd owjoid jwojd
pwd

### ENV ###
# Test 136
env | grep DOESNT_EXIST

# Test 137
env | grep HOME

# Test 138
env | grep USER

# Test 139
env | wc -l

# Test 140
env what

### PWD ###
# Test 141
pwd

# Test 142
"pwd"

# Test 143
pwd test42

# Test 144
pwd 42 42 42

# Test 145
pwd pwd

# Test 146
pwd pwd pwd

### EXPORT ###
# Test 147
/bin/echo $HALLO42
env | grep HALLO42
export HALLO42=42
/bin/echo $HALLO42
env | grep HALLO42

# Test 148
/bin/echo $HOME
env | grep HOME
export HOME=42
/bin/echo $HOME
env | grep HOME

# Test 149
export =============123

# Test 150
export

# Test 151
export =

# Test 152
export =42

# Test 153
export ''=''

# Test 154
export ""=""

# Test 155
export export

# Test 156
export echo

# Test 157
export cd

# Test 158
export test

# Test 159
export TEST

# Test 160
export $?

# Test 161
export TEST

# Test 162
export TEST=

# Test 163
export TEST=123

# Test 164
export ___TEST=123

# Test 165
export --TEST=123

# Test 166
export ''=''

# Test 167
export "="="="

# Test 168
export '='='='

# Test 169
export TE-ST=100

# Test 170
export -TEST=100

# Test 171
export TEST-=100

# Test 172
export _TEST=100

# Test 173
export ==========

# Test 174
export 1TEST=

# Test 175
export ""=""

# Test 176
export TES=T=""

# Test 177
export TE+S=T=""

# Test 178
export TES.T=123

# Test 179
export TES.T=123

# Test 180
export TES+T=123

# Test 181
export TES=T=123

# Test 182
export TES}T=123

# Test 183
export TES{T=123

# Test 184
export TES-T=123

# Test 185
export -TEST=123

# Test 186
export _TEST=123

# Test 187
export TES_T=123

# Test 188
export TEST_=123

# Test 189
export TE*ST=123

# Test 190
export TES#T=123

# Test 191
export TES@T=123

# Test 192
export TES!T=123

# Test 193
export TES$?T=123

# Test 194
export =============123

# Test 195
export +++++++=123

# Test 196
export ________=123

# Test 197
export TES^T=123

# Test 198
export TES!T=123

# Test 199
export TES\~T=123

# Test 200
export TEST+=100

# Test 201
export TES_T=123
/bin/echo $TES_T
env | grep TES_T

# Test 202
export HELLO42=T=""
/bin/echo $HELLO42
env | grep HELLO42
env | grep HELLO42=T=

# Test 203
echo $?
export ?=hallo
echo $?

# Test 204
/bin/echo $test
export test=42 | echo 99
/bin/echo $test

# Test 205
/bin/echo $mini_test
env | grep mini_test
export mini_test=
/bin/echo $mini_test
env | grep mini_test

### UNSET ###
# Test 206
unset

# Test 207
unset ""

# Test 208
unset =

# Test 209
unset "="

# Test 210
unset ""=

# Test 211
unset =""

# Test 212
unset ==

# Test 213
unset ?

# Test 214
unset "?"

# Test 215
unset $

# Test 216
unset "$"

# Test 217
unset $""

# Test 218
export TEST=100

# Test 219
unset doesntexist

# Test 220
unset OLDPWD

# Test 221
unset PATH

# Test 222
unset PATH

# Test 223
unset PATH

# Test 224
unset TES;T

# Test 225
unset TES.T

# Test 226
unset TES+T

# Test 227
unset TES=T

# Test 228
unset TES}T

# Test 229
unset TES{T

# Test 230
unset TES-T

# Test 231
unset -TEST

# Test 232
unset _TEST

# Test 233
unset TES_T

# Test 234
unset TEST_

# Test 235
unset TE*ST

# Test 236
unset TES#T

# Test 237
unset TES@T

# Test 238
unset TES!T

# Test 239
unset TES$?T

# Test 240
unset ============

# Test 241
unset +++++++

# Test 242
unset ________

# Test 243
unset export

# Test 244
unset echo

# Test 245
unset pwd

# Test 246
unset cd

# Test 247
unset unset

# Test 248
unset sudo

# Test 249
unset TES^T

# Test 250
unset TES!T

# Test 251
unset TES\~T

# Test 252
/bin/echo $HOME
unset $HOME
/bin/echo $HOME

# Test 253
/bin/echo $HOME
unset HOME
/bin/echo $HOME

# Test 254
/bin/echo $HOME
unset HOME
unset HOME
unset HOME
/bin/echo $HOME

# Test 255
/bin/echo $HOME
unset HOME
unset HOME
unset HOME
unset HOME
/bin/echo $HOME

###  EXIT ###
# Test 256
exit 9223372036854775807

# Test 257
exit something somethingv2

# Test 258
exit 0 0

# Test 259
exit

# Test 260
exit ""

# Test 261
exit "+100"

# Test 262
exit "-100"

# Test 263
exit -9223372036854775805

# Test 264
exit 0

# Test 265
exit 10

# Test 266
exit 42

# Test 267
exit 1

# Test 268
exit +++++

# Test 269
exit ++++++

# Test 270
exit +1

# Test 271
exit ++1

# Test 272
exit ++12560

# Test 273
exit -----

# Test 274
exit ------

# Test 275
exit -1

# Test 276
exit --1

# Test 277
exit -12560

# Test 278
exit --12560

# Test 279
exit 255

# Test 280
exit 1 2

# Test 281
exit 1 2 3

# Test 282
exit A

# Test 283
exit A 2 3

# Test 284
exit "A"

# Test 285
exit "+++"

# Test 286
exit ++++3193912939

# Test 287
exit 01

# Test 288
exit 001

# Test 289
exit 0001

# Test 290
exit +++000

# Test 291
exit ++++000

# Test 292
exit ---000

# Test 293
exit ----000

# Test 294
exit "something"

# Test 295
exit x

# Test 296
exit echo

# Test 297
exit cd ..

# Test 298
exit exit

# Test 299
exit 42 42 42 42 42
