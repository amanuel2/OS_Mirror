#PLEASE COMMENT BETWEEN START AND END BY ADDING # 
#IF YOU HAVE VIRTUAL BOX INSTALLED
##START
sudo pacman -S install dkms
wget -q http://download.virtualbox.org/virtualbox/debian/oracle_vbox.asc -O- | sudo apt-key add -
sudo sh -c 'echo "deb http://download.virtualbox.org/virtualbox/debian trusty contrib" >> /etc/apt/sources.list.d/virtualbox.list '
sudo pacman -Sy 
sudo pacman -S install virtualbox
##END


sudo pacman -S install xorriso 
sudo pacman -S install grub-pc-bin
sudo pacman -S install g++ binutils libc6-dev-i386
sudo pacman -S install  grub xorriso qemu
