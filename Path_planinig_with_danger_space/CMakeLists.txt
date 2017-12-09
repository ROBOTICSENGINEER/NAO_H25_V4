cmake_minimum_required(VERSION 2.8)
project(danger)

find_package(qibuild)

qi_create_bin(danger "main.cpp")
qi_use_lib(danger ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)


