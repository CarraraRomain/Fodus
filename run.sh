#!/bin/bash

OPTIND=1

# Help function
help(){
cat << EOF
Usage: ${0##*/} [-hvdr]  
Launch the Fodus project. Will try to launch the release binary first, then the debug.
	-h 	display this help
	-v	verbose mode
	-d	force to run the debug binary
	-r	force to run the release binary
EOF
}


# Get launch args
while getopts "hrdvf:" option; do
	case "$option" in
		h)
			help
			exit 0
			;;
		v)
			echo "Verbose mode"
			;;
		r)
			echo "Running the release bin..."
			;;
		d)
			echo "Running the debug bin..."
			;;

	esac
done

echo "######################"
echo -e "# \e[1m\e[34mFodus \e[32mLauncher\e[0m"
echo "######################"
echo -e "# Version 1.2.0"
echo "######################"
echo -e "\e[1m\e[31m! Not yet implemented\e[0m"
echo -e "=> Exiting"
exit 0

