# MMS-BM-STM32F405-software-base
Minimum software config for MMS base module board with  STM32F405 mcu.

# How to create software project for new MMS module.
## Creating your own module software repo.
1. Make  a fork of this repo on KoNarRobotics.
2. Name the repo as **MMS-MODULE_NAME-software** where MODULE_NAME is the name of your module.
3. Clone your forked repo to your local machine:
  ```bash
  git clone <YOUR FORKED REPO URL>
  ```
4. Cd into the cloned repo:
  ```bash
  cd MMS-MODULE_NAME-software
  ```
5. Add remote for the base project to be able to pull future updates:
  ```bash
  git remote add upstream git@github.com:KoNarRobotics/MMS-BM-STM32F405-software-base.git
  ```
6. Now you are ready to setup the project. 

## Setting up the pc to build the project.
For more info about setting up the project see **[StmEpic getting started](https://stmepic.d3lab.dev/md_docs_pages_geting_started.html)**
Go through the **Requirements** section.

## After cloning the repo.
1. Open the project in your VSCode.
2.  In **CMakeLists.txt** change the project name.:
```cmake
set(CMAKE_PROJECT_NAME YOUR_PROJECT_NAME_HERE)
```
3. To init all the submodules
  ```bash
  git submodule update --init --recursive
  ``` 

4. Build the project to make sure everything is working.
```bash
./compile.sh
```


## Writing your code for the module.
In the **src/module.cpp** file you can add your custom module initialization code in the `init_board()` function.
You can also add your custom code in there as needed.
Declaration can be added to **src/module.hpp**.
Callbacks should be added in **src/module_callbacks.cpp**.

You can always create your own files and include them in CMakeLists.txt .
**Do not modify files** like **main_prog.cpp** or **main_prog.hpp** unless you really know what you are doing.


# Configuring project
### Change project name

### In files:
- **.vscode/launch.json**  (debug config for vscode)
 in **"inputs" -> "id":"stlink_id" -> "default"** set to your stlink serial number of the board you want to program (only for local programing when you are physically connected to the board via usb adapter or if you are working over ssh wth the board from the OBC) 

-  **".vscode/tasks.json"** 
 in **"inputs" -> "stlinkID" -> "options"** you can add multiple stlink ids if you have multiple boards with the same software, You can add them some fancy names to recognize them easel.


If you want to keep it by creating a new branch, this may be a good time
# black magic
soon to be added


# ModuCard Generate Interface
1. Generate dummy interface only required to be run once.
```bash
python3 src/moducard_firmware/moducard_generators/mc_generator.py -f -d --force  src/moducard_firmware/moducard_generators/modules/mcan_basic_module_dummy.yaml
```
2. Generate real interface for the module you are working on. You should use the example **src/moducard_firmware/moducard_generators/examples/example_module_config.yaml** as a template for your module configuration.
```bash
python3 src/moducard_firmware/moducard_generators/mc_generator.py -f --force  your_module_config.yaml
```
3. This will generate the interface files in **generated/firmware**. 
Now you can add include in **module.hpp**
```cpp
#include "your_generated_interface.hpp"
```
4. Change the code in **module.hpp** to use the generated interface namespace.
in the **ModuleType** line; 
```cpp
using ModuleType = mcan::your_generated_interface ... ;
```
5. Add write callbacks for the generated interface.
the callbacks that are listed in a generated file called **your_generated_interface.hpp**
In a class called **McCanSlaveInterface_t** after the  **//Write callbacks** comment.
The callback function are called when the master updates the interface variables. You can use them to update your module variables or perform any actions needed when the master sends new values.
For example, if you have a variable called **my_variable** in your generated interface, you
have to add a callback function for it like this:
```cpp
mcan::your_generated_interface::McCanSlaveInterface_t::callback_write_my_variable(MyVariable& ver){
  // ver - is the new value sent by the master for my_variable
  // you can add some actions here.
  // ...
} 
```

6. Now you can use the generated interface in your module code. You can access the interface variables and functions through the **module->get_interface()** function. For example, if you have a variable called **my_variable** in your generated interface, you can access it like this:
```cpp
module->get_interface().my_variable
```
This variables are automatically updated when the master sends new values for them, and you can also update them so the master driver will be able to read the new values. To update the variable, you can simply assign a new value to it like this:
```cpp
module->get_interface().my_variable = new_value;
```