cmake_minimum_required(VERSION 3.20)
project(NiiroOS C ASM)

set(CMAKE_C_STANDARD 11)
enable_language(ASM)


set(CMAKE_C_FLAGS "-m32 -ffreestanding -O0 -g -Wall -Wextra -fno-pie")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -nostdlib -T ${CMAKE_SOURCE_DIR}/linker.ld -no-pie")
set(CMAKE_ASM_FLAGS "-m32 -g")


add_executable(kernel.elf
        kernel/kernel.c
        boot/boot.s
        kernel/memory.c
        kernel/memory.h
        kernel/shell.c
        kernel/shell.h
        kernel/gdt.c
        kernel/gdt.h
        kernel/keyboard.c
        kernel/keyboard.h
        kernel/vga.h
        kernel/vga.c
        kernel/string.c
        kernel/string.h
)


add_custom_command(
        TARGET kernel.elf POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:kernel.elf>
        ${CMAKE_SOURCE_DIR}/iso/boot/kernel.elf
        COMMENT "Copying kernel.elf into ISO folder"
)


add_custom_target(iso
        COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/bas.iso ${CMAKE_SOURCE_DIR}/iso
        DEPENDS kernel.elf
        COMMENT "Building bas.iso"
)

add_custom_target(run
        COMMAND qemu-system-x86_64 -cdrom ${CMAKE_BINARY_DIR}/bas.iso
        DEPENDS iso
        COMMENT "Launching QEMU"
)

add_custom_target(debug
        COMMAND qemu-system-x86_64
        -cdrom ${CMAKE_BINARY_DIR}/bas.iso
        -S -s
        DEPENDS iso
        COMMENT "Launching QEMU in GDB mode (-S -s)"
)