cmake_minimum_required(VERSION 2.8)
project(walk)

find_package(qibuild)


qi_create_bin(walk "main.cpp")
qi_use_lib(walk ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)