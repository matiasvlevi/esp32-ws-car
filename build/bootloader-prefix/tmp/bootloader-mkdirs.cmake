# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/vlev/esp/esp-idf/components/bootloader/subproject"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/tmp"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/src/bootloader-stamp"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/src"
  "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/vlev/Documents/Github/esp32-mbot/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
