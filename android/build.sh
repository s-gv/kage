#!/bin/bash

mkdir -p build
javac -source 1.6 -target 1.6 \
    -bootclasspath /usr/lib/jvm/java-6-oracle/jre/lib/rt.jar \
    -classpath /home/sagar/Android/Sdk/platforms/android-25/android.jar \
    -d ./build \
    java/com/sagargv/kagegame/GameWrapper.java \
    java/com/sagargv/kagegame/Al.java

NDK_PROJECT_PATH=. ndk-build NDK_APPLICATION_MK=./Application.mk

mv libs lib
jar cf kage.jar lib -C build .
mv kage.jar app/Kage/app/libs/

mv lib libs
rm -rf build
