#!/bin/sh
echo ""
echo "Patching Ponyo Workspace..."
echo ""
for p in $(find device/panasonic/ponyo/patches/ -name "*.diff") 
	do 
		echo -n "Apply patch "$(basename $p')
		patch -p1 < $p > /dev/null 2>&1
		echo "" 
	done
echo ""