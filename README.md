
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/pawbar94/comlint_cpp/windows-release-build.yml?label=Windows%20release%20build) ![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/pawbar94/comlint_cpp/linux-release-build.yml?label=Linux%20release%20build) [![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

# Comlint for C++
Table of contents:

[What is it?](#what_is_it)

[How to build and install](#how_to_build_and_install)

&emsp;[How to build comlint_cpp repository](#how_to_build_comlint_cpp_repository)

&emsp;[How to embed Comlint into your project](#how_to_embed_comlint_into_your_project)

&emsp;[How to use Comlint release package](#how_to_use_comlint_release_package)

[Conventions used](#conventions_used)

[How to use](#how_to_use)

&emsp;[Creating command line interface](#creating_command_line_interface)

&emsp;&emsp;[Adding commands](#adding_commands)

&emsp;&emsp;[Adding options](#adding_options)

&emsp;&emsp;[Adding flags](#adding_flags)

&emsp;[Parsing command line interface](#parsing_command_line_interface)

&emsp;[Running command line interface](#running_command_line_interface)

## <a name="what_is_it"></a>What is it?

Comlint is a framework which allows user to create a command line interface (CLI) for C++ command line applications in an easy way. It works both on Windows and Linux and is built using CMake, so it should be convenient to use for every C++ developer. If your application is written in Python, check out [Comlint for Python](https://github.com/pawbar94/comlint_py).

## <a name="how_to_build_and_install"></a>How to build and install

### <a name="how_to_build_comlint_cpp_repository"></a>How to build comlint_cpp repository

The preffered way of building this project is to use build.bat or build.sh script (depending on whether you are on Windows or Linux). These scripts take only one optional argument which is build type (Debug by default or Release), so if you want to build a Debug version, just go to _scripts_ folder and call `build.bat` (Windows) or `./build.sh` (Linux).

If for any reason build script fails, to build the ComlintCpp library manually, call from the repository root:

```
mkdir build 
cd build
cmake ..
cmake --build .
cmake --install .
```
And to build Comlint examples:
```
cd examples
mkdir build 
cd build
cmake ..
cmake --build .
cmake --install .
```

### <a name="how_to_embed_comlint_into_your_project"></a>How to embed Comlint into your project
Embedding Comlint into your project is very easy and (assuming that comlint is in root of your project) the minimum CMakeLists.txt file that you need is:

```
cmake_minimum_required(VERSION 3.10)

project(ExampleComlintApp)

add_subdirectory(comlint_cpp)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/comlint_cpp/include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ComlintCpp
)
```

After that you can start using comlint in main.cpp file.

### <a name="how_to_use_comlint_release_package"></a>How to use Comlint release package

* Download .zip package from one of the Comlint releases on github
* In the archive you will find folder comlint_cpp - extract it
* Inside the comlint_cpp folder you will find ComlintCpp.dll library and public headers
* Asuming that you put that folder in the root of your project, the minimum required CMakeLists.txt file is:

```
cmake_minimum_required(VERSION 3.10)

project(ExampleComlintApp)

set(COMLINT_CPP_DIR ${CMAKE_SOURCE_DIR}/comlint_cpp)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${COMLINT_CPP_DIR}/include
)

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/main.cpp
)

find_library(COMLINT_CPP_LIB NAMES ComlintCpp HINTS ${COMLINT_CPP_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${COMLINT_CPP_LIB}
)
```
After that you can start using comlint in main.cpp file.

## <a name="conventions_used"></a>Conventions used

Comlint splits all command line interface elements into 3 categories: **commands**, **options** and **flags**.

**Command** is a keyword specifying an action which should be executed during the application run. Comlint is a command-focused framework, so command is always placed directly after executable name. Command may take a value which details its behavior, but it's not required. For example, when calling `git pull`, _git_ is a program name and _pull_ is a command - command, which does not take any value. Another example may be `git add /some/file.txt`, where _git_ is a program name and _add_ is a command which takes a value which is _/some/file.txt_. So the general scheme of usage is:

`[program_name] [command_name]`

or

`[program_name] [command_name] [command_value]`


**Option** is a keyword which may parametrize command execution. Option is always prefixed with a single dash "-" and always takes a value. For example, calling `pip install -r requirements.txt`, _pip_ is a program name, _install_ is a command and _-r_ is the option which has been given the value _requirements.txt_. Therefore, the general scheme of usage is:

`[program_name] [command_name] [option_name] [option_value]`

**Flag** is a keyword enabling or disabling some functionalities during command execution. It is always prefixed with a double dash "--" and, because it represents a boolean switch, it never takes any value. For example, when calling `git pull --rebase`, _git_ is a program name, _pull_ is a command and _--rebase_ is the flag. The scheme of usage in this case is:

`[program_name] [command_name] [flag_name]`

## <a name="how_to_use"></a>How to use

The basis for all actions is creation of instance of Comlint command line interface object:

```cpp
comlint::CommandLineInterface cli(argc, argv);
```

Comlint bases on the user command line input, so there are 2 required constructor's parameters: argc and argv. However, you may customize your command line interface help by providing program name and program description.

```cpp
comlint::CommandLineInterface cli(argc, argv, "MyProgram", "Description of MyProgram");
```

Additionally, you may decide whether you want to allow user to run your program without any input arguments. By default, user is allowed to run application without any input arguments, but if you want to disable it, set `allow_no_arguments` to false:

```cpp
comlint::CommandLineInterface cli(argc, argv, "MyProgram", "Description of MyProgram", false);
```

### <a name="creating_command_line_interface"></a>Creating command line interface

First step to a create command line application is to design an interface by adding supported commands, options and flags.

#### <a name="adding_commands"></a>Adding commands

The easiest way to add a supported command to the interface is by using:

```cpp
cli.AddCommand("command_name", "Command description");
```

By default, such command does not take any value. There are also no options or flags that can be used together with this command. To allow this command to take a single value, use:

```cpp
cli.AddCommand("command_name", "Command description", 1U);
```

Such call means that your command requires one value and it can be any value. If you want the command to accept only one of the predefined values, pass all these allowed values in form of a vector as a next argument:

```cpp
cli.AddCommand("command_name", "Command description", 1U, {"value1", "value2"});
```

In such case, calling both `program.exe command_name value1` or `program.exe command_name value2` will be ok, but calling `program.exe command_name value_3` will result in an error because you defined your command to accept only values _value1_ and _value2_, not _value3_.

A command may be associated with a set of options which are allowed for this particular command. By default, no options are allowed, but you can pass allowed options as a next parameter after command description (in case of command not taking value) or after allowed command values (in case of commands accepting a value):

```cpp
cli.AddCommand("command", "Command description", {"-a", "-b"});
```

Such code adds a command which can be used together only with 2 options: _-a_ and _-b_. There can be other options supported by the interface, but this particular command can be used only with these two. Similary in case if you want to add command accepting any value with the same list of allowed options:

```cpp
using namespace comlint;
cli.AddCommand("command", "Command description", 1U, ANY, {"-a", "-b"});
```

The same when it comes to adding allowed flags:

```cpp
using namespace comlint;
cli.AddCommand("command", "Command description", NONE, {"--flag"});
cli.AddCommand("command", "Command description", 1U, ANY, NONE, {"--flag"});
```

First of the above lines adds command with no allowed options and one allowed flag _--flag_. Second of the above lines does the same, but for the command accepting any single value.

The last feature is the ability to add required options - in contrast to the allowed options (which **may** be used with a command), required options **must** be used with the particular command. For example:

```cpp
using namespace comlint;
cli.AddCommand("command", "Command description", {"-a", "-b"}, NONE, {"-a"});
```

Command defined in such way has two allowed options (_-a_ and _-b_), but option _-a_ must be used any time the command is called - otherwise an error will be thrown.

#### <a name="adding_options"></a>Adding options

Adding options is very similar to adding commands:

```cpp
cli.AddOption("-option", "Option description");
```

Such option accepts by default any value. If you want to limit option values which user may pass, provide it in form of a vector:

```cpp
cli.AddOption("-option", "Option description", {"value1", "value2"});
```

#### <a name="flags"></a>Adding flags

Because flags accept no values (see the [Conventions used](#conventions-used)), adding a flag limits to only two parameters - its name and description:

```cpp
cli.AddOption("--flag", "Flag description");
```

### <a name="parsing_command_line_interface"></a>Parsing command line interface

After the definition of the command line interface is ready, you can parse the input provided by the user, calling:

```cpp
const comlint::ParsedCommand parsed_command = cli.Parse();
```

In this way, you will be given a structure which contains:
* command name used by the user
* command values provided by the user
* map of options, where key is the option name and value is option value
* map of flags, where key is the flag name and value is bool flag indicating whether flag was used or not

You are able to check whether an option has been used by the user by calling:

```cpp
if (parsed_command.IsOptionUsed("-option")) {
    // Option used!
}
```

In case of flags, you don't have to check for their presence before the usage because flags which were not used by the user have assigned _false_ value.

```cpp
parsed_command.flags["--flag"]; // this returns false if --flag was not used
```

### <a name="running_command_line_interface"></a>Running command line interface

WIP