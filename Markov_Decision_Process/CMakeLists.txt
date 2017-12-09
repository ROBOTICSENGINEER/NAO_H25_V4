cmake_minimum_required(VERSION 2.8)
project(md1)

find_package(qibuild)

qi_create_bin(md1 "main.cpp")
qi_use_lib(md1 ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)


