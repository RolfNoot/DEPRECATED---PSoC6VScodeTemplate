# PSoC6 Dual Core Project for VS Code

1. Prerequisites
    - VS Code
    - ModusToolbox 1.1 (for PDL, Device Configurator, CyMCUElfTool and OpenOCD)
    - GNU Arm Embedded Toolchain
    - CMake

1. VS Code Extensions
    - ARM Support For Visual Studio Code (dan-c-underwood)
    - C/C++ IntelliSense, debugging (microsoft)
    - CMake language support (twxs)
    - CMake Tools (vector-of-bool)
    - Cortex-Debug GDB support (marus25)
    - LinkerScript support for GNU (Zixuan Wang)
    - Open in Application (Fabio Spampinato)
    - Output Colorizer (IBM)
    
1. Check
    - if make is installed by typing 'make -v' into the terminal window of VS Code
        (make needs to be added to the system's path variable)
        
        
1. Remind
    - after changing the device configuration to use
        - Clean Reconfigure
        - Clean Rebuild
      in order to build the image properly.
