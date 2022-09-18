#!/bin/zsh

echo "         ____   ____            _           _      ____                _             "
echo "  _   _ / ___| |  _ \ _ __ ___ (_) ___  ___| |_   / ___|_ __ ___  __ _| |_ ___  _ __ "
echo " | | | | |     | |_) | ¨__/ _ \| |/ _ \/ __| __| | |   | '__/ _ \/ _¨ | __/ _ \| ¨__|"
echo " | |_| | |___  |  __/| | | (_) | |  __/ (__| |_  | |___| | |  __/ (_| | || (_) | |   "
echo "  \__,_|\____| |_|   |_|  \___// |\___|\___|\__|  \____|_|  \___|\__,_|\__\___/|_|   "
echo "                             |__/                                                    "

echo "Enter project name:"

read name

echo "\n"
echo "Enter project folder:"

read dir

echo "\n"
echo "Creating Folder...🐢"

dir=~/DEV/C/uC/$dir/$name

sudo mkdir $dir && echo "\nFolder created!" || echo "\nError 🚨" exit

echo "\n"
echo "Creating base files...🐢"

sudo chmod -R 777 $dir && echo "\nGiving read and write permitions. 💂🏿‍♂️" || echo "\nError 🚨\n" exit
sudo cp -r /home/felipevale/DEV/C/uC/scripts/create-project/builder/src $dir && echo "\nSource Files created!" || echo "\nError 🚨" exit
sudo cp /home/felipevale/DEV/C/uC/scripts/create-project/builder/Makefile $dir && echo "\nMakefile created!" || echo "\nError 🚨" exit
sudo cp /home/felipevale/DEV/C/uC/scripts/create-project/builder/build.sh $dir && echo "\nFiles created!" || echo "\nError 🚨" exit

echo "Done! 🔥 \n"