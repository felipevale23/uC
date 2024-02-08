#!/bin/sh

createDirectory ()
{
  mkdir "$INSTALLER_PATH"
  mkdir "$INSTALLER_PATH/src"
  mkdir "$INSTALLER_PATH/src/lib"
}

cpFiles()
{

  cp -r $(pwd)/scripts/create-project/builder/src/main.c $INSTALLER_PATH/src && echo -e "Main File created!" || echo "\nError 🚨" exit

  cp -r $(pwd)/scripts/create-project/builder/src/lib/config.h $INSTALLER_PATH/src/lib && echo -e "Config File created!" || echo "\nError 🚨" exit

  cp -r $(pwd)/scripts/create-project/builder/src/lib/functions.h $INSTALLER_PATH/src/lib && echo -e "Function File created!" || echo "\nError 🚨" exit

  sleep 0.5

  cp $(pwd)/scripts/create-project/builder/Makefile $INSTALLER_PATH && echo -e "\nMakefile created!" || echo "\nError 🚨" exit

  sleep 0.5

  cp $(pwd)/scripts/create-project/builder/build.sh $INSTALLER_PATH && echo -e "\nFiles created!" || echo "\nError 🚨" exit

}

minimal_install () {
  
  clear

  echo "Enter project name:"

  read name

  echo "Creating Folder...🐢"

  sleep 0.2

  INSTALLER_PATH="/home/$(whoami)/$name"

  echo $INSTALLER_PATH

  mkdir $INSTALLER_PATH

  createDirectory && echo -e "\nFolder created!" || echo "Error 🚨" exit

  echo "Creating base files...🐢"

  sleep 0.2

  # sudo chmod -R 777 $dir && echo "\nGiving read and write permitions. 💂🏿‍♂️" || echo "\nError 🚨\n" exit

  cpFiles

  echo "Done! 🔥"

  sleep 2

  exit

}

install_i2c ()
{
  echo i2c installer script

}

install_i2c_lcd ()
{
 echo i2c_lcd installer script
  
}

install_spi ()
{

 echo spi installer script  

}

install_eusart ()
{
  echo eusart installer script  
}

# Progress bar function
prog() 
{
  local w=80
  local p=$1
  shift

  # Create a string of spaces, then change them to dots
  printf -v dots "%*s" "$((p * w / 100))" ""
  dots=${dots// /.}

  # Print those dots on a fixed-width space plus the percentage
  printf "\r[ Loading | %-*s | %3d %% %s" "$w" "$dots" "$p" "$*"
}

welcome () {
  clear
  echo "----------------------------------------------------------------------------------------"
  echo "                                    Welcome to                                          "  
  echo "                                                                                        "
  echo "         ____   ____            _           _      ____                _                "
  echo "  _   _ / ___| |  _ \ _ __ ___ (_) ___  ___| |_   / ___|_ __ ___  __ _| |_ ___  _ __    "
  echo " | | | | |     | |_) | ¨__/ _ \| |/ _ \/ __| __| | |   | '__/ _ \/ _¨ | __/ _ \| ¨__|   "
  echo " | |_| | |___  |  __/| | | (_) | |  __/ (__| |_  | |___| | |  __/ (_| | || (_) | |      "
  echo "  \__,_|\____| |_|   |_|  \___// |\___|\___|\__|  \____|_|  \___|\____|\__\___/|_|      "
  echo "                             |__/                                                       "
  echo "                        Arch Linux Post Install Setup and Config                        "
  echo "     Microchip PIC Edition                                                                        "
  echo "     Version 0.1  (Release)                                                             "
  echo "     Source Code https://github.com/felipevale23/uC                                     "
  echo "----------------------------------------------------------------------------------------"
  
  echo -e "\n"

  # Test loop (replace this with your actual work)
  for x in {1..100}; do
      prog "$x" "still working..."
      sleep 0.001  # Simulate some work here
  done

  echo -e "\n"
  sleep 1.5
  loadkeys br-abnt2
}

main_menu () { while true
do
  clear
  echo "-------------------------------------"
  echo "        Create uC Project            " 
  echo "-------------------------------------"
  echo ""
  echo "  1) Minimal instalation"
  echo "  2) Install I2C"
  echo "  3) Install I2C_LCD"
  echo "  4) Install SPI"
  echo "  5) Install EUSART"

  echo ""
  echo "  X) Exit"
  echo -e "\n"
  read -p "Enter your choice: " choice1
  case $choice1 in
    1 ) minimal_install ;;
    2 ) install_i2c ;;
    3 ) install_i2c_lcd ;;
    4 ) install_spi ;;
    5 ) install_eusart ;;
    x|X ) exit;;
    * ) invalid ;;
  esac
done
}
#
#

welcome
main_menu
