# ----------------------------------------------------------------------------
# Imports
# ----------------------------------------------------------------------------

import os
import sys
import re

# ----------------------------------------------------------------------------
# C/C++ Defines
# ----------------------------------------------------------------------------

cppBaseDefines = {
    "_CRT_SECURE_NO_WARNINGS" : "1",
}

cppDebugDefines = {
    "DEBUG" : "1",
}

cppNoDebugDefines = {
}


# ----------------------------------------------------------------------------
# C/C++ Compiler Options
# ----------------------------------------------------------------------------

# Documentation on Visual C++ Compiler Options can be found here:
# http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vccore/html/_core_compiler_reference.asp

ccBaseFlags = [
    "/EHsc",    # Synchronous exception handling, assume extern C functions
                # never throw exceptions.
    "/W4",      # Treat all warnings as errors
    "/nologo",  # Suppress display of sign-on banner
    "/analyze"
    ]

ccDebugFlags = [
    "/MT",      # Use dynamically-linked msvcrt for C runtime
    "/Zi",      # Produce a program database (PDB) that contains type
    "/Od",      # Disable optimization
    ]

ccNoDebugFlags = [
    "/O2",      # Enable optimizations
    "/MT",      # Use dynamically-linked msvcrt for C runtime
    "/Ob1",     # Inline expansion only for functions marked as inline
    "/GF",      # Pool strings as read-only
    "/Gy",      # Enable function-level linking
]


# ----------------------------------------------------------------------------
# C/C++ Linker Options
# ----------------------------------------------------------------------------

linkBaseFlags = [
    "/nologo",
]

linkDebugFlags = [
    "/DEBUG",   # Create .pdb file containing debugging information
]

linkNoDebugFlags = [
]


# ----------------------------------------------------------------------------
# Base Environment Definition
# ----------------------------------------------------------------------------

baseEnv = Environment(
    # Standard environment variables used by SCons.
    CPPDEFINES = cppBaseDefines,
    CCFLAGS = ccBaseFlags,
    LINKFLAGS = linkBaseFlags,
    TARGET_ARCH = "x86",
    DEBUG = 0
)


# ----------------------------------------------------------------------------
# Debug/Non-Debug Environments
# ----------------------------------------------------------------------------

# Take the base environment and create specialized debug and non-debug
# environments out of them.

debugEnv = baseEnv.Clone()
noDebugEnv = baseEnv.Clone()

debugEnv.Append(
    CPPDEFINES = cppDebugDefines,
    CCFLAGS = ccDebugFlags,
    LINKFLAGS = linkDebugFlags
)

noDebugEnv.Append(
    CPPDEFINES = cppNoDebugDefines,
    CCFLAGS = ccNoDebugFlags,
    LINKFLAGS = linkNoDebugFlags
)

# Depending on whether we're building for debugging or release, set
# the active environment to the debug or non-debug environment.

if baseEnv["DEBUG"] == 1:
    env = debugEnv
else:
    env = noDebugEnv


# ----------------------------------------------------------------------------
# Build Actions
# ----------------------------------------------------------------------------

target = env.Program(
    target = "AudioSwitch", 
    source = ["AudioSwitch.cpp", "AudioPlaybackControl.cpp", env.RES('AudioSwitch.rc')], 
    LIBS = ["gdi32.lib", "user32.lib", "ole32.lib"]
)

env.Default(target)
