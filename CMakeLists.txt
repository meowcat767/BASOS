cmake_minimum_required(VERSION 3.20)

project(BAS C ASM)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${CMAKE_SOURCE_DIR}/linker.ld")

add_executable(bas
        kernel/kernel.c
        boot/boot.s
)