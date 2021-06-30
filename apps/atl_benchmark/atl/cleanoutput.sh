#
sed 's/\\n/\'$'\n''/g' $1 > out1.txt
sed 's/"//g' out1.txt > out2.txt
sed 's/@/"/g' out2.txt > out3.txt
sed 's/~/\\n/g' out3.txt > out4.txt
vim -c "normal gg=G" -c "%s/COQ.*//g" -c "%s/\\$//g" -c wq out4.txt
sed '/./,$!d' out4.txt > tmp
mv tmp out5.txt
csplit --quiet --elide-empty-files --suffix-format='%d.out' out5.txt '/!!!/' '{*}'

out_to_c() {
	sed -i '1d' $1

	NAME=$(head -n 1 $1)

	tail -n +2 $1 > $NAME

	vim -c "normal gg=G" -c wq $NAME

	rm $1
}

for f in *.out; do out_to_c $f; done
