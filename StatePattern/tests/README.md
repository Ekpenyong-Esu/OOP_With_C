# Tests Directory

This directory contains clean, focused tests for the simplified State Pattern implementation.

## Test Files

### `test_simple_state_pattern.c`

- **Purpose**: Unit tests for the State Pattern implementation
- **Tests**:
  - Basic functionality (digit parsing, context operations)
  - Simple integer parsing
  - Simple decimal parsing  
  - State transitions
  - Edge cases (empty input, invalid input)

### `test_integration.c`

- **Purpose**: Integration tests for the complete workflow
- **Tests**:
  - End-to-end number parsing sequences
  - Multiple number parsing
  - Mixed integer and decimal parsing
  - Manual state transition verification
  - Edge case handling

### `test_mutex.c`

- **Purpose**: Unit tests for thread safety
- **Tests**:
  - Mutex initialization and destruction
  - Lock and unlock operations
  - Error handling
  - Thread safety verification

## Running Tests

```bash
# Build all tests
cmake --build build

# Run all tests
cd build && ctest

# Run individual test
./build/tests/SimpleStatePatternTests
./build/tests/IntegrationTests  
./build/tests/MutexTests
```

## Test Coverage

The tests provide comprehensive coverage of:

- ✅ Core State Pattern functionality
- ✅ All state transitions
- ✅ Number parsing accuracy
- ✅ Thread safety with mutexes
- ✅ Error handling and edge cases
- ✅ Integration between all components

## Why These Tests?

1. **Simple & Clear**: Easy to understand and maintain
2. **Focused**: Each test has a single responsibility
3. **Comprehensive**: Covers all major functionality
4. **Fast**: Quick execution for development feedback
5. **Reliable**: Deterministic results every time
