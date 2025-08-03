# AND Pattern Components - Learning Journey

This project demonstrates the **AND Pattern** (Orthogonal/Concurrent States) through multiple components that show different aspects and complexity levels.

## 🎯 What is the AND Pattern?

The AND pattern allows an object to have **multiple independent aspects** that operate simultaneously. Instead of being in just one state, the object can be in multiple states at the same time.

## � Component Structure

```text
src/
├── LightPkg/           # 📋 Basic types (ColorType, FlashType)
├── Light/              # 💡 Simple Light with 2 AND aspects
├── Timer/              # ⏱️  Timer with 3 AND aspects  
├── Sensor/             # 📊 Sensor with 4 AND aspects
└── SmartLight/         # 🤖 Complex system combining all patterns
```

## 🚀 Learning Path

### 1. **Start Simple**: Light Component

**Two independent aspects**: Color AND Flash Mode

- **Color**: RED, YELLOW, GREEN
- **Flash Mode**: STEADY, SLOWLY, QUICKLY

**Key Learning**: Change one without affecting the other!

### 2. **Add Time**: Timer Component  

**Three independent aspects**: State AND Mode AND Duration

- **State**: STOPPED, RUNNING, PAUSED, EXPIRED
- **Mode**: ONESHOT, REPEATING, COUNTDOWN  
- **Duration**: Any time value

**Key Learning**: Time can be an orthogonal aspect too!

### 3. **Add Complexity**: Sensor Component

**Four independent aspects**: State AND Quality AND Power AND Type

- **State**: OFF, INITIALIZING, CALIBRATING, READY, ACTIVE, ERROR
- **Quality**: INVALID, POOR, GOOD, EXCELLENT
- **Power Mode**: SLEEP, LOW, NORMAL, HIGH
- **Type**: TEMPERATURE, HUMIDITY, PRESSURE, LIGHT

**Key Learning**: Multiple aspects can all work independently!

### 4. **Combine Everything**: SmartLight Component

**ALL aspects working together**:

- Light aspects (Color AND Mode)
- Timer aspects (Multiple timers with different behaviors)
- Sensor aspects (Motion AND Ambient light)
- Smart aspects (Mode AND Brightness AND Features)

**Key Learning**: Complex behavior emerges from simple, independent parts!

## 💭 Learning Questions

As you study each component, ask yourself:

1. **Independence**: Can I change one aspect without affecting others?
2. **Concurrency**: Do multiple aspects work simultaneously?
3. **Orthogonality**: Are the aspects truly independent?
4. **Composition**: How do simple aspects create complex behavior?

## 🎓 Real-world Examples

The AND pattern is everywhere:

- **Car**: Speed AND Direction AND Gear AND Headlights AND Radio
- **Phone**: Network State AND Battery Level AND Screen Brightness AND App Status
- **Game Character**: Health AND Position AND Animation State AND Inventory
- **Smart Home**: Temperature AND Lighting AND Security AND Entertainment

## ✨ Next Steps

1. **Build and Run**: `cd examples && ./comprehensive_demo`
2. **Experiment**: Modify the components to add new aspects
3. **Create**: Build your own AND pattern components
4. **Advance**: Study hierarchical state machines

Remember: Start simple, understand thoroughly, then build complexity!
