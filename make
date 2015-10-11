OPTIND=1

# Help func
help(){
cat << EOF
Usage: ${0##*/} [-h]
Make the project Fodus.
	-h 			display this help
EOF
}

while getopts "h" option; do
	case "$option" in
		h)
			help
			exit 0
			;;
	esac
done

cd build/
make
