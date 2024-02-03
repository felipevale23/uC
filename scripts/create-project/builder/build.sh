#!/bin/sh

echo "\n"
echo "Building...🏗"
echo "\n"

make all && echo "Compiled!" || echo "\n ERROR. Check the code above for details 😭" exit

echo "\n"
echo "Cleaning.. 🧹"
echo "\n"

make clean && echo "\nAll clean! 🔥" || echo "\n Error. Check the code above for details 😭" exit
sleep 1

echo "\n"
echo "Copying to Working Area... 🐢"
echo "\n"

sudo cp main.hex /mnt/c/Users/felip/Desktop && echo "Copied to > /mnt/c/Users/felip/Desktop"|| echo "\n I couldnt copy the file 😭" exit

echo "\n"
echo "Done! 😘"