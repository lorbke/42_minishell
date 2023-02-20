#!bin/bash

BLUE='\033[0;34m'

# path to test script
test_script="shinimell.py"

echo -e "${BLUE}Running 'make re'..."
cd ..
# just comment the next line if you don't want to run make re every time
make re > /dev/null || exit 1
cd test/src > /dev/null
python3 $test_script
