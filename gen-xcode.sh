#!/bin/bash

cd build-xcode
cmake .. -GXcode
open staticshock.xcodeproj
