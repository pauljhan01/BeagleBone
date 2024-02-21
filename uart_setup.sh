git clone -b v5.10.x-ti-arm64 https://github.com/beagleboard/BeagleBoard-DeviceTrees/ /home/debian/
make /home/debian/BeagleBoard-DeviceTrees/
sudo make install /home/debian/BeagleBoard-DeviceTrees/
echo "fdtoverlays/overlays/BONE-UART1.dtbo" >> /boot/firmware/extlinux/extlinux.conf
tree /dev/bone 
