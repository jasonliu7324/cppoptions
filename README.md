# Options Library
Home to private access of Options Library + Any math backengine for Options

## Local setup (create .vscode/settings.json — not tracked in git)

**Windows:**
{
    "cmake.configureSettings": {
        "CMAKE_TOOLCHAIN_FILE": "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
}

**Mac:**
{
    "cmake.configureSettings": {
        "CMAKE_PREFIX_PATH": "/opt/homebrew"
    },
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools"
}