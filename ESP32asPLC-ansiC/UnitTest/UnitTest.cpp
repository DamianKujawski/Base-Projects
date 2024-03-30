#include "pch.h"
#include "CppUnitTest.h"

#include "..\MEMO\MCU.h"
#include "..\MEMO\Opcode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;





namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
        public:

            TEST_METHOD(TestMethod1)
            {
                // Define the ROM program
                unsigned char _romProgram[] = {
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

                Assert::AreEqual(static_cast<unsigned char>(6), _ramData[1], L"Value at index 1 should be 6");

                // Free memory
                delete[] _mcuSimulation->rom.data;
                delete[] _mcuSimulation->ram.data;
                delete _mcuSimulation;
            }
	};
}
