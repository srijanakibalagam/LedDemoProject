#!/bin/bash

echo "Building project via Conan..."
conan create . swf/latest -pr=swf_ubuntu18_x64_gcc7

echo "'Installing' latest version via Conan..."
cd build
conan install demo-led-status-indication/1.0.0@swf/latest -pr=swf_ubuntu18_x64_gcc7
cd ..