git clone -b v5.10.x-ti-arm64 https://github.com/beagleboard/BeagleBoard-DeviceTrees/ /home/debian/
make /home/debian/BeagleBoard-DeviceTrees/
sudo make install /home/debian/BeagleBoard-DeviceTrees/
overlay_install=$(grep -c "fdtoverlays /overlays/BONE-UART1.dtbo /overlays/BONE-UART4568.dtbo" /boot/firmware/extlinux/extlinux.conf)
if (($overlay_install==0));
then
	echo "fdtoverlays /overlays/BONE-UART1.dtbo /overlays/BONE-UART4568.dtbo" >> /boot/firmware/extlinux/extlinux.conf
fi
echo $overlay_install
