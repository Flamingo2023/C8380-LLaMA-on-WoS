#!/bin/sh

# Copyright 2023 Qualcomm Technologies, Inc. All rights reserved.
# Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")

basedir=$(dirname $0)
basedir=$(realpath $basedir/..)

export ADSP_LIBRARY_PATH=$basedir/lib
export LD_LIBRARY_PATH=$basedir/lib

set -x

$basedir/bin/qualla-embedd "$@"
