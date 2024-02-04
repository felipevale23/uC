#!/bin/sh

# Set the version of XC8 you want to install
XC8_VERSION="v2.46"

# Define the download URL for the XC8 installer
XC8_URL="https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v2.46-full-install-linux-x64-installer.run"

# Follow the installer prompts to complete the installation
# You may need to provide your password during the installation process

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

download_xc8 () {
    echo -e "\n"
    echo -e "Download the XC8 installer from: \n"
    echo "$XC8_URL"
    echo -e "\n"
    prog "$x" "working..."
    echo -e "\n"
    # Download the XC8 installer using curl
    curl -o xc8-"$XC8_VERSION"-linux-installer.run "$XC8_URL"

    
}

make_executable () {
    echo -e "\n"
    echo Making the installer file executable
    echo -e "\n"
    prog "$x" "working..."
    # Make the installer file executable
    chmod +x xc8-"$XC8_VERSION"-linux-installer.run

    sleep 0.02

}

run_installer () {
    echo -e "\n"
    echo Runing the installer, root privileges required
    echo -e "\n"
    prog "$x" "working..."
    # Run the installer with root privileges
    sudo ./xc8-"$XC8_VERSION"-linux-installer.run

    sleep 0.02

}

make_symbolic () {
    echo -e "\n"
    echo Making a simbolic link to xc8 binary, root access needed.
    echo -e "\n"
    prog "$x" "working..."
    sudo ln -sf /opt/microchip/xc8/"$XC8_VERSION"/bin/xc8 /bin/xc8
    sleep 0.02
}

remove_installer () {
    echo -e "\n"
    echo Removing installer..
    echo -e "\n"
    prog "$x" "working..."

    # Run the installer with root privileges
    sudo rm -rf ./xc8-"$XC8_VERSION"-linux-installer.run
    sleep 0.02
}

exit_cmd () {
    echo -e "\n"
    echo Instaltion completed..
    echo -e "\n"
    prog "$x" "Finished"

    sleep 1
    exit
}

install_xc8 () {
    # Test loop (replace this with your actual work)
    for x in {1..100}; do
        clear
        
        echo -e "\n"
        echo "-------------------------------------"
        echo "       xc8 Compiler Installer       " 
        echo "-------------------------------------"

        case "$x" in
            "1" ) download_xc8 ;;
            "20" ) make_executable  ;;
            "30" ) run_installer  ;;
            "40" ) make_symbolic ;;
            "50" ) remove_installer ;;
            "100" ) exit_cmd ;;
        esac
        
        echo -e "\n"
        echo Fnishing
        echo -e "\n"
        
        prog "$x" "working..."
        sleep 0.02
        
        echo -e "\n"
    done

    remove_installer
}

uninstall_xc8 (){

    echo -e "\n"
    echo Runing the installer, root privileges required

    # Run the installer with root privileges
    sudo /opt/microchip/xc8/"$XC8_VERSION"/bin/Uninstall-xc8-v2.46

    sleep 0.5

}

main_menu () { while true
do
  clear
  echo "-------------------------------------"
  echo "       xc8 Compiler Installer       " 
  echo "-------------------------------------"
  echo ""
  echo "  1) install"
  echo "  2) uninstall"

  echo ""
  echo "  X) Exit"
  echo -e "\n"
  read -p "Enter your choice: " choice1
  case $choice1 in
    1 ) install_xc8 ;;
    2 ) uninstall_xc8 ;;

    x|X ) exit;;
    * ) invalid ;;
  esac
done
}
#
#

main_menu
