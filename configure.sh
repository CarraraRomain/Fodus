#!/bin/bash
sfml_path=""
OPTIND=1

# Help func
help(){
cat << EOF
Usage: ${0##*/} [-hv] [-s SFML_ROOT_PATH]  
CMake and Make the project Fodus.
	-s SFML_ROOT_PATH	if SFML is installed in a not standard path and/or not recognized
	-h 			display this help
	-v			verbose mode
EOF
}

while getopts "hs:vf:" option; do
	case "$option" in
		h)
			help
			exit 0
			;;
		s)
			sfml_path=$OPTARG
			echo "SFML Path : $sfml_path"
			;;	
	esac
done


mkdir build
cd build
if ["$sfml_path" == ""]; then
	echo "Trying default SMFL autodetect"
	cmake ..
else
	echo "Using custom SFML location"
	cmake .. -DSFML_ROOT=$sfml_path
fi

make
