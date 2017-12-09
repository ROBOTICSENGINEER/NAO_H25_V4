cmake_minimum_required(VERSION 2.8)
project(mdf)

find_package(qibuild)

qi_create_bin(mdf "main.cpp")
qi_use_lib(mdf ALCOMMON ALVISION OPENCV2_CORE OPENCV2_HIGHGUI)


