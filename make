#!/usr/bin/env bash
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
# Build bonefish
pushd build/
pushd ../lib/bonefish/build
make -j4
popd
make -j4
cd ../bin/Debug/
if [ ! -f router ]
then
    echo "Creating router symlink..."
    ln -s ../../lib/bonefish/build/daemon/bonefish router
else
    echo "Router symlink already exists"
fi
