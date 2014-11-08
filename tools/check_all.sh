TERM=zsh
find ../EiTOS -iname "*.cpp" -print | xargs --no-run-if-empty -n 1 $TERM check_file.sh
find ../EiTOS -iname "*.c" -print0 | xargs --no-run-if-empty -n 1 $TERM check_file.sh

find ../EiTOS -iname "*.hpp" -print | xargs --no-run-if-empty -n 1 $TERM check_file.sh
find ../EiTOS -iname "*.h" -print | xargs --no-run-if-empty -n 1 $TERM check_file.sh