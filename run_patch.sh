#!/bin/sh
echo ""
echo "Patching Ponyo Workspace..."
echo ""
for p in $(find device/panasonic/ponyo/patches/ -name "*.diff") 
	do 
		echo -n "Apply patch "$(basename $p | awk -F"." '{print $1}')
		patch -p1 < $p > /dev/null 2>&1
		if [ $? == 0 ]; then
			echo "     [DONE]"
		else
			echo "     [FAIL]"
		fi
		echo "" 
	done
echo ""