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

![neural](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/0f2c472c-2453-43ae-8f2b-82e51f188e38)

Simplified Unit Test:

```
void Test_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, std::vector<std::vector<double>>* testingInputs)
{
    for (size_t i = 0; i < (*testingInputs).size(); ++i)
    {
        std::vector<double> _input = (*testingInputs)[i];
        std::vector<double> _output = (*neuralNetwork).FeedForward(_input);

        Logger::WriteMessage("Input: [");
        for (size_t j = 0; j < _input.size(); ++j)
        {
            Logger::WriteMessage(std::to_string(_input[j]).c_str());
            if (j < _input.size() - 1)
                Logger::WriteMessage(", ");
        }
        Logger::WriteMessage("], Output: ");
        Logger::WriteMessage(std::to_string(_output[0]).c_str());
        Logger::WriteMessage(_output[0] >= 0.5 ? " (Sine Wave)\n" : " (Not Sine Wave)\n");
    }
}

void Train_NeuralNetwork(NeuralNetwork_FeedForward* neuralNetwork, TrainingData_t* trainingData, int iterationsCnt)
{
    for (int epoch = 0; epoch < iterationsCnt; ++epoch)
    {
        for (size_t i = 0; i < (*trainingData).inputs.size(); ++i)
        {
            std::vector<double> input = (*trainingData).inputs[i];
            std::vector<double> target = (*trainingData).results[i];

            (*neuralNetwork).Train(input, target);
        }
    }
}


NeuralNetwork_Builder* _neuralNetwork_Builder = new NeuralNetwork_Builder();
NeuralNetwork_FeedForward* _neuralNetwork = _neuralNetwork_Builder
    ->Set_Size_InputNodes(10)
    ->Set_Size_HiddenNodes(10)
    ->Set_Size_OutputNodes(1)
    ->Set_LearningRate(0.1)
    ->Build();

// Step 1: Create training data
TrainingData_t _trainingData
{
    {
        {0.0, 0.25, 0.5, 0.75, 1.0, 0.75, 0.5, 0.25, 0.0, -0.25},   // 1 - Sine
        {0.1, 0.35, 0.6, 0.85, 1.1, 0.85, 0.6, 0.35, 0.1, -0.15},   // 1 - Shifted Sine Wave
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},         // 0
        {0.2, 0.4, 0.6, 0.8, 1.0, 0.8, 0.6, 0.4, 0.2, 0.0},         // 1 - Sine
        {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3}          // 0
    },
    {
        {1},
        {1},
        {0},
        {1},
        {0}
    }
};

// Step 2: Train Neural Network
Train_NeuralNetwork(_neuralNetwork, &_trainingData, 10000);

// Step 3: Create test data
std::vector<std::vector<double>> _testingInputs =
{
    {0.05, 0.3, 0.55, 0.8, 1.05, 0.8, 0.55, 0.3, 0.05, -0.2},       // Different Sine Wave pattern
    {0.15, 0.35, 0.55, 0.75, 0.95, 0.75, 0.55, 0.35, 0.15, -0.05},  // Another Different Sine Wave pattern
    {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}              // Non-Sine Wave pattern
};

// Step 4: Test the Neural Network with different input vectors
Test_NeuralNetwork(_neuralNetwork, &_testingInputs);

delete _neuralNetwork_Builder;
delete _neuralNetwork;

```

## OpenGlParser

Simplified Unit Test:

```
---
```

## SmartHome_Editor

Simplified Unit Test:

```
---
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
