1) rpi-config
	- disable console on serial port

2) Edit /boot/config.txt

dtoverlay=pi3-disable-bt

3) Edit /boot/cmdline.txt

remove the word phase "console=serial0,115200" or "console=ttyAMA0,115200"
