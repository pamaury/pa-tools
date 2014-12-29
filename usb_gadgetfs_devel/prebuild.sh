#/bin/sh
tag=`echo $kernelver | awk '{ split($0,a,"."); print("v"a[1]"."a[2]); }'`
gadgeturl="https://raw.githubusercontent.com/torvalds/linux/$tag/drivers/usb/gadget"
echo "prebuild"
echo "kver: $kernelver"
echo "gadget url: $gadgeturl"

curl -o dummy_hcd.c "$gadgeturl/dummy_hcd.c"
curl -o inode.c "$gadgeturl/inode.c"
