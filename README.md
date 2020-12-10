# C++ programming project

This is an initial git repository for your programming project.
It contains an initial directory structure that we wish you could
use as follows:

  * `plan/` -- Your project plan should be put here. You may use different sources,
    but we hope to get the plan **also as a pdf file**.

  * `doc/` -- The documentation sources related to your project should be put here.
    You may use different tools for documentation (e.g. latex),
    but we hope to get the final version of the document
    **also as pdf file**.

  * `src/` -- Here are the C++ source files. You can have subfolders as needed.

  * `test/` -- Unit tests.

  * `resource/` -- Resources used in the project (fonts, pictures, ...).

  * `README.md` -- This file. You should modify it to represent your project.

You may also add other new directories as needed, for example
for testing tools.


### Dependencies
- CMake 3.16.3+
- SFML 2.5.1
- Python 3.6+ (for google unit test framework)
- Git

### Running the program
Step 1: Clone the project from repo
```shell
git clone git@courses-git.comnet.aalto.fi:CPP-F2020/dungeon-2020-4.git
```
Step 2: Create Makefile and build it
```shell
cd dungeon-2020-4
mkdir build
cd build
cmake .
make dungeon
```
Step 3: Execute the program
```shell
./dungeon

```

### Testing
`TextUI` is an Text-based user interface used for debugging purpose. 
To run the program, run the code showing below in the root directory of project. 
 ```shell
cd build
make TEXT_UI
./TEXT_UI
```
There are also some unit tests available. For instance, unit test for `Coord` class 
can be executed by running the following code in the root directory of project
 ```shell
cd build
make coordtest
./coordtest
```