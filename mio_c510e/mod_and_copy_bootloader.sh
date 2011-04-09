#!/bin/bash
./create_binfs bootloader/bootloader.bin bin/binfs_hdr.bin bin/mod_WINCEIMG.BIN
./create_cks bin/mod_WINCEIMG.BIN bin/mod_WINCEIMG.CKS
cp bin/mod_WINCEIMG.BIN $1/winceimg.bin
cp bin/mod_WINCEIMG.CKS $1/winceimg.cks
