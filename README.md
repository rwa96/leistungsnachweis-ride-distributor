# Ride distributor

Solution to the Self-driving rides problem statement for the [Online Qualification Round of Hash Code 2018](https://hashcode.withgoogle.com/2018/tasks/hashcode2018_qualification_task.pdf).

## Getting Started

Use CMake to generate a Visual Studio project, after cloning this repo. From then on use ".build/RideDistributor.sln" to work on the project.

### Installing

Create Workspace

```shell
cmake . -B".build" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug
```

Create Executable

```shell
cmake --build .build --target all
```

Debug informations are printed to the console by default. They can be deactivated by defining "NDEBUG".

Create Documentation

```shell
cmake --build .build --target doc
```

## Unit Tests (create executable first)

```shell
cd .build && ctest -VV
```

## Usage

RideDistributor takes two parameters. The first one is the path to the input file, the second one the path to the output file.

Example for the a_example.in file given by Google

```shell
RideDistributor.exe ..\..\resources\a_example.in ..\..\resources\a_example.out
```

The score of the output file can be checked using [nikosk93/hashcode2018_grader](https://github.com/nikosk93/hashcode2018_grader).

## Results

The following table shows benchmarks from all versions of this project:
*(each of the columns links to the commit of that version)*

|                     | [Heuristic Beam Search] | [Best-first search (using points)] | [Best-first search (using times left + points)] |
| :------------------ | :---------------------: | :--------------------------------: | :---------------------------------------------: |
| a_example.in        | 10                      | 8                                  | 10                                              |
| b_should_be_easy.in | 124,373                 | 168,815                            | 176,877                                         |
| c_no_hurry.in       | 8,747,443               | 9,133,444                          | 14,825,711                                      |
| d_metropolis.in     | 1,708,208               | 4,403,978                          | 3,015,856                                       |
| e_high_bonus.in     | 2,503,182               | 3,363,963                          | 21,465,945                                      |
| Total               | 13,083,216              | 17,070,208                         | 39,484,399                                      |

[Heuristic Beam Search]: https://github.com/ob-algdatii-ss18/leistungsnachweis-ride-distributor/tree/f7e62f75816e76f720a8996a9e8c475ab3343053
[Best-first search (using points)]: https://github.com/ob-algdatii-ss18/leistungsnachweis-ride-distributor/tree/159ce4224aa3974086f4b4e08e330543555b7478
[Best-first search (using times left + points)]: https://github.com/ob-algdatii-ss18/leistungsnachweis-ride-distributor/tree/eb81ece48d004fe83487926999c8ef1079212033

## Built With

* [CMake 3.11.0](https://cmake.org/cmake/help/v3.11/) - Compiler-independent management of the build process
* [Doxygen 1.8.13](https://www.stack.nl/~dimitri/doxygen/manual/index.html) - Documentation generator
* [Visual Studio Code 1.35.1](https://code.visualstudio.com) - IDE
* [Artistic Style 3.1](http://astyle.sourceforge.net) - Code Autoformat

## Authors

* **Robin Wismeth** - [rwa96](https://github.com/rwa96)
* **David Askari** - [dahpu](https://github.com/dahpu)

## Acknowledgments

* Roy Jonker for the [C implementation of LAPJV](https://web.archive.org/web/20051030203159/http://www.magiclogic.com/assignment/lap_cpp.zip)
* [hrldcpr](https://github.com/hrldcpr/pyLAPJV) for the updated LAPJV implementation
* [nikosk93](https://github.com/nikosk93/hashcode2018_grader) for the score checking tool
