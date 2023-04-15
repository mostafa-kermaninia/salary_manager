mkdir assets 2> /dev/null
touch soroush.txt
touch myoutput.txt
echo "" > myoutput.txt
echo "" > soroush.txt
g++ -std=c++11 -o mybinary putyourcodehere.cpp 2> /dev/null
((i = 1)) 2> /dev/null
while diff myoutput.txt soroush.txt -Bbq > /dev/null
do
  ((i++)) 2> /dev/null
  ./gen
  ./soroush assets < input.txt > soroush.txt
  ./mybinary assets < input.txt > myoutput.txt
done
code --diff myoutput.txt soroush.txt
