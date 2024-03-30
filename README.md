# Repository: Base-Projects

  Small, base projects, which were used as implementations for larger projects in the future. 
  > I don not share code from larger applications *** 

## Content

  - [Introduction](#Introduction)
  - [Projects](#ESP32asPLC)
  - [License](#License)



## Introduction

  Projects included in the repository: 
  - [ESP32asPLC](#ESP32asPLC)
  - [NeuralNetwork](#NeuralNetwork)
  - [OpenGlParser](#OpenGlParser)
  - [SmartHome_Editor](#SmartHome_Editor)
  - [CrowdSimulation](#CrowdSimulation)

## ESP32asPLC

  PLC Unit Emulator.

  ![cpu](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/29d2be9c-ed0d-4af7-b071-97ec6cbef093)

```
.
│
├── src/
│   ├── main.c
│   ├── MCU.c
│   └── MCU/
│         └── Instructions.c
│
└── include/
      │
      ├── MCU/
      │     ├── Instructions.h
      │     └── Instructions
      │            └── Opcode.h
      │
      └── GLOBAL/ <------------------------------------------------ Configuration point
            ├── Types.h
            └── Project.h

.
│
└── UnitTest/
      ├── src/
      │     ├── UnitTest.cpp
      │     └── pch.cpp (Microsoft::VisualStudio::CppUnitTestFramework)
      │
      └── include/
            ├── MCU.h
            ├── Opcode.h
            └── pch.h
```

Simplified Unit Test:

```
unsigned char _romProgram[] =
{
    SET, 3,
    ST, 0,
    ADD, 0,
    ST, 1
};

// Define the RAM data
unsigned char _ramData[256] = { 0 };

// Create MCU simulation:
MCU_t* _mcuSimulation = new MCU_t(); // Dynamically allocate memory for MCU_t object

// Initialize ROM and RAM data - Conversion from:
/*
    MCU_t* _mcuSimulation = MCU
    (
        &(MEM_t) { (unsigned char*)_romProgram, sizeof(_romProgram) },
        & (MEM_t) { _ramData, sizeof(_ramData) }
    );
*/

_mcuSimulation->rom.data = new unsigned char[sizeof(_romProgram)];
memcpy(_mcuSimulation->rom.data, _romProgram, sizeof(_romProgram));
_mcuSimulation->rom.size = sizeof(_romProgram);

_mcuSimulation->ram.data = new unsigned char[sizeof(_ramData)];
memcpy(_mcuSimulation->ram.data, _ramData, sizeof(_ramData));
_mcuSimulation->ram.size = sizeof(_ramData);

// Run the simulation
_mcuSimulation->Run();

// Verify the result
Logger::WriteMessage("RAM map:\n");
for (int i = 0; i < sizeof(_ramData); i++) 
{
    Logger::WriteMessage(std::to_string(_ramData[i]).c_str());
    Logger::WriteMessage(" ");
}

Assert::AreEqual(static_cast<unsigned char>(6), _ramData[1], L"Value at RAM ADDR = 1 should be 6");

// Free memory
delete[] _mcuSimulation->rom.data;
delete[] _mcuSimulation->ram.data;
delete _mcuSimulation;

```

## NeuralNetwork

Simplified Unit Test:

```

```

## OpenGlParser

Simplified Unit Test:

```

```

## SmartHome_Editor

Simplified Unit Test:

```

```

## CrowdSimulation

  Crowd Simulating Project. Mainly designed for optimization. The main premise in developing this project is for the object not to plan steps ahead.
       
  ![photo_2024-03-30_09-07-22](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/fd831e81-a8ef-4188-b121-8958c368b772)

```
.
├── src/
│   └── main.cpp
│         ├── Scene2D.cpp
│         └── Scene2D
│               ├── Drawing2D.cpp
│               └── DynamicObject2D
│                      ├── DynamicObject2D_Fast.h
│                      └── Base
│                            ├── DynamicObject2D.cpp
│                            └── Random.h
│
└── include/
    │
    ├── main
    │   ├── Scene2D.h
    │   └── Scene2D
    │        ├── Drawing2D.h
    │        └── DynamicObject2D
    │              ├── DynamicObject2D_Fast.h
    │              └── Base
    │                    ├── DynamicObject2D.cpp
    │                    └── Random.h
    │
    └── GLOBAL/ <------------------------------------------------ Configuration point
          │
          ├── Define_Colors.h
          ├── Struct.h
          ├── Config.h
          ├── Project.h
          └── Debug.h


```

Simplified Unit Test:

```
---
```

## License

-
