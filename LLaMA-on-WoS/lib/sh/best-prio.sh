#!/bin/sh

# Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
# Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

usage()
{
    echo "best-prio.sh"
    exit
}

case $(uname -a) in
    Linux*android*aarch64*)
        # Assuming Lanai
        echo -n '--prio 0'
        ;;
    MINGW*)
	# Assuming Hamoa
        echo -n '--prio 2'
        ;;
    Darwin*arm64*)
	# Assuming M1/M2
        /bin/echo -n '--prio 3'
	;;
    Linux*x86_64*)
        ;;
esac
