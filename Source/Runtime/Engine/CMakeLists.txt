# Add executable
add_executable(VulkanBoids)

# Sources
file(GLOB SOURCES_PRIVATE "${SOURCE_RUNTIME_DIRECTORY}/Engine/Private/*.cpp")
file(GLOB HEADERS_PUBLIC "${SOURCE_RUNTIME_DIRECTORY}/Engine/Public/*.h")

# Add sources to target
target_sources(VulkanBoids PRIVATE ${SOURCES_PRIVATE})
target_sources(VulkanBoids PUBLIC ${HEADERS_PUBLIC})

# Create the project filters
GROUPSOURCES(${SOURCE_RUNTIME_DIRECTORY}/Engine/Public Public)
GROUPSOURCES(${SOURCE_RUNTIME_DIRECTORY}/Engine/Private Private)

# Private includes
target_include_directories(VulkanBoids PUBLIC ${SOURCE_RUNTIME_DIRECTORY}/Graphics)

# Link libraries
target_link_libraries(VulkanBoids PUBLIC Graphics)

# Include self
target_include_directories(VulkanBoids PUBLIC ${SOURCE_RUNTIME_DIRECTORY}/Engine/Public)
target_include_directories(VulkanBoids PRIVATE ${SOURCE_RUNTIME_DIRECTORY}/Engine/Private)

# Compile definitions
target_compile_definitions(VulkanBoids PUBLIC -DRTS_VULKAN)

if(${CMAKE_HOST_WIN32})
    target_compile_definitions(VulkanBoids PUBLIC -DPPP_WINDOWS)
endif()

# Target properties
set_target_properties(VulkanBoids PROPERTIES
                      FOLDER "Engine")
