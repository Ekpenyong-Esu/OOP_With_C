# AND Pattern Learning Project

This project demonstrates the **AND Pattern** (Orthogonal/Concurrent States) through multiple components that progress from simple to complex examples.

## 🎯 What You'll Learn

- What the AND pattern is and why it's fundamental
- How to implement independent, concurrent aspects in C
- Progressive complexity from simple to advanced patterns
- Real-world applications and design principles
- Clean C programming patterns for state management

## 🏗️ Component Overview

### 1. **Light** - Basic AND Pattern (2 aspects)
- **Color**: RED, YELLOW, GREEN
- **Flash Mode**: STEADY, SLOWLY, QUICKLY

### 2. **Timer** - Time-based AND Pattern (3 aspects)  
- **State**: STOPPED, RUNNING, PAUSED, EXPIRED
- **Mode**: ONESHOT, REPEATING, COUNTDOWN
- **Duration**: Configurable timing

### 3. **Sensor** - Multi-aspect AND Pattern (4 aspects)
- **Operational State**: OFF, READY, ACTIVE, ERROR
- **Data Quality**: INVALID, POOR, GOOD, EXCELLENT  
- **Power Mode**: SLEEP, LOW, NORMAL, HIGH
- **Sensor Type**: TEMPERATURE, HUMIDITY, PRESSURE, LIGHT

### 4. **SmartLight** - Complex AND Pattern (All aspects combined)
- All Light aspects
- Multiple Timer behaviors
- Sensor inputs and responses
- Smart modes and features
- Adaptive learning

## 🚀 Quick Start

```bash
# Easy build and run
./build_and_run.sh

# Or manual build
mkdir build && cd build
cmake ..
make

# Run comprehensive demo
./examples/comprehensive_demo
```
```

## 📁 Project Structure

```text
AndState/
├── src/
│   ├── LightPkg/       # 📋 Basic types (ColorType, FlashType)
│   ├── Light/          # 💡 Simple 2-aspect AND pattern
│   ├── Timer/          # ⏱️  Time-based 3-aspect AND pattern
│   ├── Sensor/         # 📊 Multi-aspect 4-aspect AND pattern
│   └── SmartLight/     # 🤖 Complex combined AND patterns
├── examples/           # 🚀 Comprehensive demonstrations
├── build_and_run.sh    # 🔨 Easy build script
└── README.md          # 📖 This guide
```

**Progressive Learning**: Start with Light, then Timer, then Sensor, finally SmartLight!
└── README.md          # This file
```

Clean, simple, focused on learning!

## 🎓 Why This Matters

The AND pattern is fundamental to:

- **State Machines**: Multiple concurrent states
- **Real-time Systems**: Independent subsystems
- **Game Development**: Character states (health AND movement AND animation)
- **UI Programming**: Multiple widget states
- **Embedded Systems**: Device aspects operating simultaneously

## ✨ Learning Path

1. **Start here**: Understand the simple Light example
2. **Experiment**: Add new aspects (brightness, blink rate, etc.)
3. **Advance**: Study hierarchical state machines
4. **Apply**: Use in your own projects

Perfect for students, professionals learning C, or anyone wanting to understand this essential pattern!

## 📝 Key Takeaways

- **AND Pattern**: Multiple independent aspects operating simultaneously
- **Orthogonal States**: Changing one doesn't affect others
- **Clean C**: Proper struct design and function organization
- **Real-world Applicable**: Pattern used everywhere in software

Start simple, understand thoroughly, then build complexity!
