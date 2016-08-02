#PLEASE COMMENT BETWEEN START AND END BY ADDING # 
#IF YOU HAVE VIRTUAL BOX INSTALLED
##START
sudo apt-get install dkms
wget -q http://download.virtualbox.org/virtualbox/debian/oracle_vbox.asc -O- | sudo apt-key add -
sudo sh -c 'echo "deb http://download.virtualbox.org/virtualbox/debian trusty contrib" >> /etc/apt/sources.list.d/virtualbox.list '
sudo apt-get update
sudo apt-get install virtualbox
##END


sudo apt-get install xorriso 
sudo apt-get install grub-pc-bin
sudo apt-get install g++ binutils libc6-dev-i386
sudo apt-get install  grub xorriso qemu
