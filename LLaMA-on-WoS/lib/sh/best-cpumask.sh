#!/bin/sh

# Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
# Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

usage()
{
    echo "best-cpumask.sh <n-threads>"
    exit
}

nt=$1
[ "$nt" = "" ] && usage

case $(uname -a) in
    Linux*android*aarch64*)
        # Assuming Lanai
        if   [ "$nt" -eq 2 ]; then echo -n '--cpu-mask 0xc0'
        elif [ "$nt" -eq 4 ]; then echo -n '--cpu-mask 0xf0'
        elif [ "$nt" -eq 5 ]; then echo -n '--cpu-mask 0xf8'
        elif [ "$nt" -eq 6 ]; then echo -n '--cpu-mask 0xfc'
        elif [ "$nt" -eq 8 ]; then echo -n '--cpu-mask 0xff'
        fi
        ;;
    MINGW*)
        # Assuming Hamoa
        if   [ "$nt" -eq  2 ]; then echo -n '--cpu-mask 0x110 --cpu-strict'
        elif [ "$nt" -eq  4 ]; then echo -n '--cpu-mask 0xcc0 --cpu-strict'
        elif [ "$nt" -eq  5 ]; then echo -n '--cpu-mask 0x1f0 --cpu-strict'
        elif [ "$nt" -eq  6 ]; then echo -n '--cpu-mask 0x770 --cpu-strict'
        elif [ "$nt" -eq  8 ]; then echo -n '--cpu-mask 0xff0 --cpu-strict'
        elif [ "$nt" -eq 10 ]; then echo -n '--cpu-mask 0xffc --cpu-strict'
        fi
        ;;
    Darwin*arm64*)
	# Assuming M1/M2
	;;
    Linux*x86_64*) 
        ;;
esac
