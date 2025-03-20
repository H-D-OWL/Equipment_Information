# Equipment_Information
## Description
The plugin adds nodes that provide information about CPU, GPU, RAM and displays.

## Requirement

Target version : UE5.0 ～ 5.5

Target platform : Windows

## Contents
* Get CPU Info
  - Info: Returns all available information about the CPU. **For example: Intel(R) Core(TM) i7-9700K CPU @ 3.60GHz**
  - Core: Returns number of cores. **For example: 8**
* Get Specific Info (CPU)
  - Info: Requires Info (Get CPU Info).
  - Specific Infomation to Received: Select the specific information you want to receive from Specific Info. **For example: Compane, Name, Number, Series.**
  - Specidic Info: Returns specific information depending on the selection of Specific Infomation to Received. **For example: Compane - Intel(R), Name -Core(TM), Number -i7, Series -9700K.**

![Снимок 1](https://github.com/user-attachments/assets/61485cd8-d706-412c-bd06-314553c6aefe)

* Get GPU Info Name, Number,  Name, Number, 
  - Info: Returns all available information about the GPU.  **For example: NVIDIA GeForce RTX 2080**
* Get Specific Info (GPU)
  - Info: Requires Info (Get GPU Info).
  - Specific Infomation to Received: Select the specific information you want to receive from Specific Info. **For example: Compane, Name, Mark, Model, Minimum Model, Series.**
  - Specidic Info: Returns specific information depending on the selection of Specific Infomation to Received. **For example: Compane - NVIDIA, Name - GeForce, Mark - RTX, Model - 2080, Minimum Model - 2080, Series - 2000.**

![Снимок 2](https://github.com/user-attachments/assets/af89519f-0644-49ba-b5e4-889d00f25fff)

* Get RAM Info
  - Total Physical Memory: Returns total physical memory in GB. **For example: 32**
  - Used Physical Memory: Returns used physical memory in GB. **For example: 17,5**
  - Free Physical Memory: Returns free physical memory in GB. **For example: 14,5**

![Снимок 3](https://github.com/user-attachments/assets/42263f2b-ab12-45d0-8cc3-6503df27bbda)

* Get Displays Info
  - Displays: Returns an array of the "Display Info" structure. The "Display Info" structure contains: String "Name", String "ID", int "Native Width", int "Native Height", int Point "Max Resolution" Structure, bool "Is Primary", int "DPI".  **For example: Name - AUS2707, ID - MONITOR\AUS2707\{4d36e96e-e325-11ce-bfc1-08002be10318}\0001, Native Width - 2560, Native Height - 1440, Max Resolution - , Is Primary - true, DPI - 107**
  - Max FPS Primary Monitor: Returns Max FPS Primary Monitor.  **For example: 60**

![Снимок 4](https://github.com/user-attachments/assets/2461c07d-d196-49df-ae04-be464468a4dd)
