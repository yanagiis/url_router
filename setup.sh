#!/usr/bin/env bash

if [[ ! -d ./3rdparty/Unity ]]; then
    git clone https://github.com/ThrowTheSwitch/Unity.git 3rdparty/Unity
else
    echo "Unity is already in 3rdparty"
fi
