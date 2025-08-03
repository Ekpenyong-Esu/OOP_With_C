#!/bin/bash

# Build and Test Script for AND Pattern Project

echo "=== Building AND Pattern Project ==="

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build the project
echo "Building..."
make -j4

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    
    # Run the comprehensive demo if it exists
    if [ -f "./examples/comprehensive_demo" ]; then
        echo ""
        echo "=== Running Comprehensive Demo ==="
        ./examples/comprehensive_demo
    else
        echo "⚠️  Demo executable not found. Check build output."
    fi
else
    echo "❌ Build failed!"
    exit 1
fi

echo ""
echo "=== Build Complete ==="
echo "Executables are in the build directory:"
echo "- examples/comprehensive_demo"
