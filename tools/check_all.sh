find ../EiTOS -iname "*.cpp" -exec bash check_file.sh $1 {} \;
find ../EiTOS -iname "*.c" -exec bash check_file.sh $1 {} \;

find ../EiTOS -iname "*.hpp" -exec bash check_file.sh $1 {} \;
find ../EiTOS -iname "*.h" -exec bash check_file.sh $1 {} \;