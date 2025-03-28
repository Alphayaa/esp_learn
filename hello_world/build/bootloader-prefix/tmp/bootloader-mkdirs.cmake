# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP_IDF/Espressif/frameworks/esp-idf-v5.2.2/components/bootloader/subproject"
  "F:/Learn/esp/hello_world/build/bootloader"
  "F:/Learn/esp/hello_world/build/bootloader-prefix"
  "F:/Learn/esp/hello_world/build/bootloader-prefix/tmp"
  "F:/Learn/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp"
  "F:/Learn/esp/hello_world/build/bootloader-prefix/src"
  "F:/Learn/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "F:/Learn/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "F:/Learn/esp/hello_world/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
