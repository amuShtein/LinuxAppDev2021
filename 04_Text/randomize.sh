#!/bin/bash
TIME="0"
echo "arg is = [$1]"
if [ "$1" != "" ]
then
	echo "set default time $1"
	TIME=$1
fi
echo "TIME IS $TIME"


lines=()
lens=()
line=""
while IFS="" read -r line; do
	echo "line = $line"
    lines+=( "$line" )
    lens+=( "${#line}" )
done

len=${#lines[*]}
echo "lines = $len"

indexes=""
for ((i=0; i<len; i++)); do
	echo "[$i] '${lines[$i]}' len = ${lens[$i]}"

	indexes="$indexes"
done

indexes=""
NL=$'\n'
for ((i=0; i<len; i++)); do
	for((j=0; j<lens[i] - 1; j++)) do
		indexes="$indexes$i $j$NL"
	done

	if [ $i -lt $((len - 1)) ]
	then
		indexes="$indexes$i $((lens[i] - 1))$NL"
	else
		indexes="$indexes$i $((lens[i] - 1))"
	fi
done

# indexes=`echo  "$indexes" | shuf`

# echo  "$indexes"


pair=()
echo "" > debug
tput clear
while read -r line
do
    echo "$line" >> debug
    pair=( $line )
    i=${pair[0]}
    j=${pair[1]}
    line=${lines[$i]}
    char=${line:$j:1}
    echo "line[$i] = $line" >> debug
    echo "char[$j] = $char" >> debug
    if [ "$char" != " " ]
    then
    	tput cup $i $j; sleep $TIME; echo "$char"
    fi
done < <(echo  "$indexes" | shuf)
tput cup $len 0