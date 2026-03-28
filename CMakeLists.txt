cmake_minimum_required(VERSION 3.20)

project(BAS C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_ASM_FLAGS "-m32")

# Compiler and linker flags
set(CMAKE_C_FLAGS "-m32 -ffreestanding -O2 -Wall -Wextra -fno-pie")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -nostdlib -T ${CMAKE_SOURCE_DIR}/linker.ld -no-pie")

# Kernel executable
add_executable(kernel.elf
        kernel/kernel.c
        boot/boot.s
)

# Copy kernel into ISO folder after build
add_custom_command(
        TARGET kernel.elf POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:kernel.elf>
        ${CMAKE_SOURCE_DIR}/iso/boot/kernel.elf
)

# Build ISO (bas.iso)
add_custom_target(iso
        COMMAND grub-mkrescue -o ${CMAKE_BINARY_DIR}/bas.iso ${CMAKE_SOURCE_DIR}/iso
        DEPENDS kernel.elf
        COMMENT "Building bas.iso"
)

# Run QEMU with the ISO
add_custom_target(run
        COMMAND qemu-system-x86_64 -cdrom ${CMAKE_BINARY_DIR}/bas.iso
        DEPENDS iso
        COMMENT "Launching QEMU"
)