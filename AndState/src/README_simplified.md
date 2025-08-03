# Light AND Pattern - Simple Learning Project

This project demonstrates the **AND Pattern** (also called Orthogonal or Concurrent States) using a simple Light example. It's designed to be the easiest way to understand this important design pattern.

## 🎯 What is the AND Pattern?

The AND pattern allows an object to have **multiple independent aspects** that operate simultaneously. Instead of being in just one state, the object can be in multiple states at the same time.

## 💡 Light Example

Our Light demonstrates the AND pattern with **two independent aspects**:

1. **Color**: RED, YELLOW, or GREEN
2. **Flash Mode**: STEADY, SLOWLY, or QUICKLY

### Key Insight: Independence

These aspects are **orthogonal** (independent):

- You can change color without affecting flash mode
- You can change flash mode without affecting color
- Both work together when the light is on

## 📁 Simplified Project Structure

```text
src/
├── LightPkg/           # 📋 Basic types (ColorType, FlashType)
└── Light/              # 💡 Simple Light with AND pattern
```

That's it! No complex hierarchies, no threading, no advanced features. Just the core AND pattern.

## 🚀 Quick Start

1. **Understand the Types** (`LightPkg/`)
   - `ColorType`: RED, YELLOW, GREEN
   - `FlashType`: STEADY, SLOWLY, QUICKLY

2. **See the AND Pattern** (`Light/`)
   - Light has BOTH color AND mode
   - Change them independently
   - They work together

3. **Run the Example**

   ```bash
   cd examples
   ./light_demo
   ```

## 💭 Learning Questions

After studying the code, ask yourself:

1. How does the Light store two independent aspects?
2. What happens when you change just the color?
3. What happens when you change just the mode?
4. How do both aspects work together?

## 🎓 Real-world Examples

The AND pattern is everywhere:

- **Car**: Speed AND Direction AND Gear
- **Phone**: Battery Level AND Signal Strength AND Bluetooth Status
- **Computer**: CPU Usage AND Memory Usage AND Network Activity

## ✨ Next Steps

Once you understand this simple version:

1. Try adding a third aspect (like brightness)
2. Study more complex state machines
3. Learn about state hierarchies

Remember: Complex systems are built from simple, well-understood parts!
