cd /home/debian/
git clone -b v5.10.x-ti-arm64 https://github.com/beagleboard/BeagleBoard-DeviceTrees/
cd home/debian/BeagleBoard-DeviceTrees/
make
sudo make install
echo "fdtoverlays/overlays/BONE-UART1.dtbo" >> /boot/firmware/extlinux/extlinux.conf
tree /dev/bone 
