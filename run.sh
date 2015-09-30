#!/bin/bash

OPTIND=1

# Help function
help(){
cat << EOF
Usage: ${0##*/} [-hvdr]  
Launch the Fodus project. Mandatory arg : -d or -r
	-h 	display this help
	-v	verbose mode
	-d	run the debug binary
	-r	run the release binary
EOF
}

echo "######################"
echo -e "# \e[1m\e[34mFodus \e[32mLauncher\e[0m"
echo "######################"
echo -e "# Version 1.2.0"
echo "######################"

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
			echo -e "\e[1m\e[31m! Not yet implemented\e[0m"
			echo "Use -d instead"
			;;
		d)
			echo "Running the debug bin..."
			./bin/Debug/Fodus
			;;
		*)
			echo "No recognized args ; use -d to run debug binary"
			;;
	esac
done





echo -e "=> Exiting"
exit 0

