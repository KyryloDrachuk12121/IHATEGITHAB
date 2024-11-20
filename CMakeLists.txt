cmake_minimum_required(VERSION 3.10)
project(QRCode)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)


find_library(QUIRC_LIB quirc REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(C:\otp\opencv\build)
add_executable(QRCodeWiFiConnector main.cpp)


target_link_libraries(QRCodeWiFiConnector ${OpenCV_LIBS} ${QUIRC_LIB})
