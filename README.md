# Repository: Base-Projects

  Small, base projects, which were used as implementations for larger projects in the future. 

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



## NeuralNetwork

![neural](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/0f2c472c-2453-43ae-8f2b-82e51f188e38)

```
.
│
├── include/
|      |
│      └── main-NeuralNetwork/
|            |
│            ├── NeuralNetwork_Builder.h
│            └── NeuralNetwork_Builder/
|                  |
│                  ├── NeuralNetwork_FeedForward.h
│                  └── NeuralNetwork_FeedForward/
|                        |
│                        ├── NeuralNetwork/
│                        ├── NeuralNetwork_ActivationFunction.h
│                        ├── NeuralNetwork_FeedForwardCalculator.h
│                        ├── NeuralNetwork_LayerErrors.h
│                        └── NeuralNetwork_WeightInitializer.h
│            
├── scr/
|      |
│      └── main-NeuralNetwork/
|            |
│            ├── NeuralNetwork_Builder.cpp
│            └── NeuralNetwork_Builder/
│                    |
│                    ├── NeuralNetwork_FeedForward.cpp
│                    └── NeuralNetwork_FeedForward/
│                            |
│                            └── NeuralNetwork/
│                                    |
│                                    ├── NeuralNetwork_FeedForwardCalculator.cpp
│                                    ├── NeuralNetwork_LayerErrors.cpp
│                                    └── NeuralNetwork_WeightInitializer.cpp
│
└── GLOBAL/  <------------------------------------------------ Configuration
      |
      ├── Define.h
      ├── Project.h
      └── Struct.h


.
│
└── UnitTest/
      |
      ├── src/
      │     |
      │     ├── UnitTest.cpp
      │     └── pch.cpp (Microsoft::VisualStudio::CppUnitTestFramework)
      │
      └── include
            |
            ├── NeuralNetwork_Builder.h
            ├── Opcode.h
            └── Struct.h
```

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

![work37_h](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/aa6373b9-2d88-4eaa-9f70-a69d22be5ef6)

```
.
├── src/
|       |
│       ├── main.cpp
│       └── main/
|               |
│               ├── glWindow/
│               │      │   
│               │      ├── glCamera.cpp
│               │      └── glInput.cpp
│               │
│               ├── glWindow_Scenes/
│               │      │ 
│               │      ├── base/
│               │      │     └── glDraw.cpp
│               │      │     
│               │      ├── glScene_Dynamic/
│               │      │     └── glScene_Dynamic_Driver.cpp
│               │      │     
│               │      └── glScene_Dynamic.cpp
│               │
│               ├── parser/
│               │      │ 
│               │      ├── base/
│               │      │     │
│               │      │     ├── StringMathParser/
│               │      │     │       └── StringMathTokenizer.cpp
│               │      │     │
│               │      │     ├── StringCommandParser.cpp
│               │      │     └── StringMathParser.cpp
│               │      │
│               │      ├── parser_Command/
│               │      │     │
│               │      │     ├── command_Line.cpp
│               │      │     ├── command_Load.cpp
│               │      │     ├── command_Point.cpp
│               │      │     ├── command_Remove.cpp
│               │      │     ├── command_Square.cpp
│               │      │     ├── command_Switch_Math.cpp
│               │      │     ├── command_Text.cpp
│               │      │     └── command_Texture.cpp
│               │      │     
│               │      ├── parser_Common/
│               │      │     │
│               │      │     ├── command_Exit.cpp
│               │      │     └── command_Help.cpp
│               │      │
│               │      ├── parser_Math/
│               │      │     │
│               │      │     ├── parser_Clear.cpp
│               │      │     ├── parser_Graph.cpp
│               │      │     └── parser_Switch_Command.cpp
│               │      │
│               │      ├── parser_Command.cpp
│               │      └── parser_Math.cpp
│               │
│               ├── glWindow.cpp
│               └── parser.cpp
│
└── include/
│         └── main/
|               |
│               ├── glWindow/
│               │      │  
│               │      ├── glCamera.h
│               │      └── glInput.h
│               │
│               ├── glWindow_Scenes/
│               │      │   
│               │      ├── base/
│               │      │     │
│               │      │     ├── glDraw/
│               │      │     │      └── stb_image.h
│               │      │     │
│               │      │     ├── glDraw.h
│               │      │     └── glDraw_Base.h
│               │      │  
│               │      ├── glScene_Dynamic/
│               │      │     └── glScene_Dynamic_Driver.h
│               │      │   
│               │      └── glScene_Dynamic.h
│               │
│               ├── parser/
│               │      │ 
│               │      ├── base/
│               │      │     ├── StringMathParser/
│               │      │     │       └── StringMathTokenizer.h
│               │      │     │
│               │      │     ├── Parser_Base.h
│               │      │     ├── StringCommandParser.h
│               │      │     └── StringMathParser.h
│               │      │
│               │      ├── parser_Command/
│               │      │     │
│               │      │     ├── command_Line.h
│               │      │     ├── command_Load.h
│               │      │     ├── command_Point.h
│               │      │     ├── command_Remove.h
│               │      │     ├── command_Square.h
│               │      │     ├── command_Switch_Math.h
│               │      │     ├── command_Text.h
│               │      │     └── command_Texture.h
│               │      │     
│               │      ├── parser_Common/
│               │      │     │
│               │      │     ├── command_Exit.h
│               │      │     └── command_Help.h
│               │      │
│               │      ├── parser_Math/
│               │      │     │
│               │      │     ├── parser_Clear.h
│               │      │     ├── parser_Graph.h
│               │      │     └── parser_Switch_Command.h
│               │      │
│               │      ├── parser_Command.h
│               │      └── parser_Math.h
│               │
│               ├── glWindow.h
│               └── parser.h
│
└── GLOBAL/ <------------------------------------------------ Configuration
    │
    ├── CMD.h
    ├── Project.h
    └── Struct.h

```

Simplified Unit Test:

```
---
```

## SmartHome_Editor

![work36_h](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/482cbb79-5323-4718-a33f-a163a2408a16) 

![318230525-482cbb79-5323-4718-a33f-a163a2408a16](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/8c3f3f66-43ad-4870-aff0-27815420a26c) ![dada](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/f654f493-34bf-43a8-9b7a-90110b2c1cc9)

```
DSharp_Interop/
    │
    ├── DSharp_Interop.cs
    └── DSharp_InteropLibrary/
                │ 
                ├── DSharp_Camera.cs
                ├── DSharp_Size.cs
                └── IDxWindow.cs

SmartHome_Editor/
    │ 
    ├── dependencies/
    │        └── DSharp_Camera.cs
    │
    ├──  DxGraphics-Base/
    │        │ 
    │        ├── DxModel2D5/
    │        │      └── DxModel_Struct.cs
    │        │    
    │        ├── DxTexture3D/
    │        │      └── DxBitmap.cs
    │        │    
    │        ├── DxLight.cs
    │        ├── DxModel2D5.cs
    │        └── DxTexture3D.cs
    │
    ├──  GLOBAL/
    │        │  
    │        ├── AssemblyAuthorAttribute.cs
    │        └── Config.cs
    │
    ├──  MainWindow/
    │        │
    │        ├── DxWindow_ScenesController/
    │        │      │  
    │        │      ├── Scene_25D/
    │        │      │      │
    │        │      │      ├── DxLightShader/
    │        │      │      │      |
    │        │      │      │      ├── DxShader_ExeDefinitions.cs
    │        │      │      │      └── DxShader_Struct.cs
    │        │      │      │
    │        │      │      ├── DxWindow_Overlay2D-Base/
    │        │      │      │      |
    │        │      │      │      ├── IOverlay_2D.cs
    │        │      │      │      └── Overlay_2D_Base.cs
    │        │      │      │
    │        │      │      ├── IsometricMath/
    │        │      │      │      └── IsometricMath_Struct.cs
    │        │      │      │
    │        │      │      ├── DxCamera.cs
    │        │      │      ├── DxLightShader.cs
    │        │      │      ├── DxWindow_Overlay2D.cs
    │        │      │      └── IsometricMath.cs
    │        │      │
    │        │      ├── Scene_25D-Base/
    │        │      │      │   
    │        │      │      ├── IScene_25D.cs
    │        │      │      ├── Scene_25D_Base.cs
    │        │      │      ├── Scene_25D_Enum.cs
    │        │      │      └── Scene_25D_Struct.cs
    │        │      │  
    │        │      └── Scene_25D_MapEditor.cs
    │        │
    │        ├── HID_Mouse/
    │        │      └── HID_Mouse_Struct.cs
    │        │
    │        ├── DxWindow_ScenesController.cs
    │        └── HID_Mouse.cs
    │
    ├──  RESOURCES/
    │        │
    │        ├── Controls/
    │        │      │ 
    │        │      ├── Control_Menu_NetworkSettings.xaml
    │        │      └── Control_Menu_SensorsSettings.xaml
    │        │      
    │        ├── Styles/
    │        │      │
    │        │      ├── Styles_Button.xaml
    │        │      ├── Styles_CheckBox.xaml
    │        │      ├── Styles_ContextMenu.xaml
    │        │      ├── Styles_MenuItem.xaml
    │        │      ├── Styles_PasswordBox.xaml
    │        │      ├── Styles_ScrollBar.xaml
    │        │      ├── Styles_TabItem.xaml
    │        │      ├── Styles_TextBox.xaml
    │        │      ├── Styles_Thumb.xaml
    │        │      └── Styles_Tooltip.xaml
    │        │
    │        ├── Controls.xaml
    │        └── Styles.xaml
    │
    ├── App.xaml
    ├── AssemblyInfo.cs
    ├── MainWindow.xaml
    └── Resources.xaml

```

Simplified Unit Test:

```
---
```

## ESP32asPLC

  PLC Unit Emulator.

  ![cpu](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/8cb7516e-c657-40a7-8b57-a743e6c7dfca)

```
.
│
├── src/
│   │
│   ├── main.c
│   ├── MCU.c
│   └── MCU/
│         │
│         └── Instructions.c
│
└── include/
      │
      ├── MCU/
      │     │
      │     ├── Instructions.h
      │     └── Instructions
      │            └── Opcode.h
      │
      └── GLOBAL/ <------------------------------------------------ Configuration
            │
            ├── Types.h
            └── Project.h

.
│
└── UnitTest/
      ├── src/
      │     │
      │     ├── UnitTest.cpp
      │     └── pch.cpp (Microsoft::VisualStudio::CppUnitTestFramework)
      │
      └── include/
            │
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

## CrowdSimulation

  Crowd Simulating Project. Mainly designed for optimization. The main premise in developing this project is for the object not to plan steps ahead.
       
  ![crowd](https://github.com/DamianKJKujawski/Base-Projects/assets/160174331/1ed4a9c3-771f-4aa1-a90e-240cb3f08fc6)

```
.
├── src/
│   │
│   └── main.cpp
│         │
│         ├── Scene2D.cpp
│         └── Scene2D
│               │
│               ├── Drawing2D.cpp
│               └── DynamicObject2D
│                      │
│                      ├── DynamicObject2D_Fast.h
│                      └── Base
│                            │
│                            ├── DynamicObject2D.cpp
│                            └── Random.h
│
└── include/
    │
    ├── main
    │     │
    │     ├── Scene2D.h
    │     └── Scene2D
    │            │
    │            ├── Drawing2D.h
    │            └── DynamicObject2D
    │                  │
    │                  ├── DynamicObject2D_Fast.h
    │                  └── Base
    │                        ├── DynamicObject2D.cpp
    │                        └── Random.h
    │
    └── GLOBAL/ <------------------------------------------------ Configuration
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

MIT License

Copyright (c) 2024 Damian K.J. Kujawski

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
