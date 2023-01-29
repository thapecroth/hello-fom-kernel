
if [ "$#" -ne 2 ]; then
   echo "Usage: ./run-vm.sh <image file> <ssh port number>"
fi

IMG_FILE=$1;
PORT=$2;

qemu-system-x86_64 -nographic -smp 4 -m 4G -serial mon:stdio -hda $IMG_FILE -device e1000,netdev=net0 -netdev user,id=net0,hostfwd=tcp::$PORT-:22;
practice.sh
Displaying practice.sh
