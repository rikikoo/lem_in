#!/usr/bin/env bash

i=0
declare -i res=0

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

	echo ""

	echo "--flow-ten"
	./lem-in < f10 > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

	echo ""

	echo "--flow-thousand"
	./lem-in < f1000 > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

	echo ""

	echo "--big"
	./lem-in < big > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

	echo ""

	echo "--big-superposition"
	./lem-in < bigSuper > out
	echo "$(grep -m 1 "#Here" out | awk '{ print $8 }') $(grep ^L out | wc -l)"

	declare -i actual=$(grep ^L out | wc -l)
	declare -i expected=$(grep -m 1 "#Here" out | awk '{ print $8 }')
	((res = res + actual - expected))
	echo ""

	((i++))
done

((result = res / i))
echo "Average superposition difference: $result"
