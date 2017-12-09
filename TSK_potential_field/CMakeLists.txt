cmake_minimum_required(VERSION 2.8)
project(square2)

find_package(qibuild)


qi_create_bin(square2 "main.cpp")
qi_use_lib(square2 ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)
