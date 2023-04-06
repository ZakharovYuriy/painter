#!/bin/bash

var1=$1
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo "Run with arg ->$var1" 

files=$SCRIPT_DIR/../tests/
program=$SCRIPT_DIR/../bin/html_paint

# Запуск Nginx
service nginx start

if `$program $files$var1`
then
	cp -f ./output.html /usr/share/nginx/html/index.html 
	echo "Programm ended OK"
	
	nginx -s reload
while true
do
# Бесконечный цикл для того, чтобы контейнер не останавливался после выполнения скрипта
echo "Enter 'exit' to exit:"
read input
if [ "$input" = "exit" ]
then
    break
fi
done

else
	echo "Program return -> ERROR" 
fi



