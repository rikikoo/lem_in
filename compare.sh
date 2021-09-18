#!/usr/bin/env bash

declare -i i=0
declare -i f1res=0
declare -i f10res=0
declare -i f1000res=0
declare -i bigres=0
declare -i superres=0
declare -i actual=0
declare -i expected=0

while [ $i -lt 5 ]
do
	printf "\033[0;33m********** ITERATION $i **********\033[0m"

	echo ""
	echo "generating maps..."
	./generator --flow-one > f1
	./generator --flow-ten > f10
	./generator --flow-thousand > f1000
	./generator --big > big
	./generator --big-superposition > bigSuper
	echo ""

	echo "--flow-one";
	./lem-in < f1 > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

    actual=$(grep ^L out | wc -l)
    expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((f1res = f1res + actual - expected))
	
    echo ""

	echo "--flow-ten"
	./lem-in < f10 > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

    actual=$(grep ^L out | wc -l)
    expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((f10res = f10res + actual - expected))
	
    echo ""

	echo "--flow-thousand"
	./lem-in < f1000 > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

    actual=$(grep ^L out | wc -l)
    expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((f1000res = f1000res + actual - expected))
	
    echo ""

	echo "--big"
	./lem-in < big > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

    actual=$(grep ^L out | wc -l)
    expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((bigres=bigres + actual - expected))
	
    echo ""

	echo "--big-superposition"
	./lem-in < bigSuper > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

    actual=$(grep ^L out | wc -l)
    expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((superres = superres + actual - expected))
    
    echo ""

    ((i++))
done

((result = f1res / i))
printf "\033[0;33mAverage flow-one difference: $result\033[0m\n"
((result = f10res / i))
printf "\033[0;33mAverage flow-ten difference: $result\033[0m\n"
((result = f1000res / i))
printf "\033[0;33mAverage flow-thousand difference: $result\033[0m\n"
((result = bigres / i))
printf "\033[0;33mAverage big difference: $result\033[0m\n"
((result = superres / i))
printf "\033[0;33mAverage superposition difference: $result\033[0m\n"
