cmake_minimum_required(VERSION 2.8)
project(mamdany)

find_package(qibuild)

qi_create_bin(mamdany "main.cpp")
qi_use_lib(mamdany ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)

