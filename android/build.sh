#!/bin/bash

mkdir -p build
javac -source 1.6 -target 1.6 -bootclasspath /usr/lib/jvm/java-6-oracle/jre/lib/rt.jar -d ./build java/com/sagargv/kage/GameWrapper.java

NDK_PROJECT_PATH=. ndk-build NDK_APPLICATION_MK=./Application.mk

mv libs lib
jar cf kage.jar lib -C build .
mv lib libs
rm -rf build