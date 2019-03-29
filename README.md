

# LinkedListsCPP

[![CircleCI](https://circleci.com/gh/AlexanderJDupree/LinkedListsCPP.svg?style=svg)](https://circleci.com/gh/AlexanderJDupree/LinkedListsCPP)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c24f1655cc534243b8ab5bcd60c8302c)](https://www.codacy.com/app/AlexanderJDupree/LinkedListsCPP?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AlexanderJDupree/LinkedListsCPP&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/AlexanderJDupree/LinkedListsCPP/branch/master/graph/badge.svg)](https://codecov.io/gh/AlexanderJDupree/LinkedListsCPP)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/AlexanderJDupree/LinkedListsCPP/master/LICENSE)


- [Getting Started](#getting-started)
- [Usage](#usage)
- [Execute unit tests](#execute-unit-tests)
- [Built With](#built-with)
- [Contributing](#contributing)
- [Versioning](#versioning)
- [Authors](#authors)
- [License](#license)

## Introduction

**LinkedListsCPP** project features a collection of linked list data structures. These linked lists are fully templated and mirror the syntax and functionality of the C++ standard library containers. Currently only the linear linked list is implemented, but stay tuned for doubly and circular linked list releases!

## Getting Started

- Download the latest [release here](https://github.com/AlexanderJDupree/LinkedListsCPP/releases).

### Prerequisites
- linked_list.hpp utilizes C++ 11 language features and will **NOT** compile in older C++ language standards. In the future, compiler and language standard detection will be added for compatibility. If you want to work on this feature, feel free to contribute!

### Usage

All releases are header only, so just drop the .hpp file into your includes and start using the linked list like this:

```c++
#include <iostream>
#include "linear_linked_list.hpp"

int main()
{
    linear_linked_list<char> list { 'H', 'E', 'L', 'L', 'O', '!', '\n' };

    for(const char& letter : list)
    {
        std::cout << letter;
    }

    // Prints "HELLO!" to the console
    
    return 0;
}
```
Extensive documentation can be expected for the future. For right now, however, please the read header comments or examine how the linked lists are used in the unit tests for usage instructions.

## Execute Unit Tests

For those who wish to contribute, you'll need to build and run the unit tests. This repo utilizes [Premake5](https://github.com/premake/premake-core) to build the necessary project files. After you Premake5 is installed you can start building the project.

- First, clone the repository
```bash
git clone https://github.com/AlexanderJDupree/LinkedListsCPP.git
```

- Navigate to the project directory
```bash
cd LinkedListsCPP
```

- And run premake5 <action> to generate the project files for your platform. For example to build GNU Makefiles run:
```bash
premake5 gmake
```
- To run the unit tests, just build the application.

```
cd gmake && make
```

- If you need to rerun the tests, they are located in bin/tests/

## Built With

* [Catch2](https://github.com/catchorg/Catch2) - Unit Testing framework used
* [Premake5](https://github.com/premake/premake-core) - Build System

## Contributing

Please read [CONTRIBUTING.md](https://github.com/AlexanderJDupree/LinkedListsCPP/blob/master/CONTRIBUTING.md) for details on our code of conduct.

All contributions are welcome: bug fixes, recommendations, issues, features.

Plase see the [issues](https://github.com/AlexanderJDupree/LinkedListsCPP/issues) before you submit a pull request or raise an issue to avoid duplication. 

To contribute to this repository:

- [Fork the project to your own GitHub profile](https://help.github.com/articles/fork-a-repo/)

- Download the project using git clone:
```
git clone git@github.com:<YOUR_USERNAME>/LinkedListsCPP.git
```
- Create a new branch with a descriptive name:
```
git checkout -b descriptive_branch_name
```
- Write some code, fix something, and add a test to prove that it works. **No pull request will be accepted without tests passing, or without new tests if new features are added.**

- Commit your code and push it to GitHub

- [Open a new pull request](https://help.github.com/articles/creating-a-pull-request/) and describe the changes you have made.

- We'll accept your changes after review.

Simple!

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/AlexanderJDupree/LinkedListsCPP/tags). 

## Authors
* **Alexander DuPree** - *Initial work* - [GitHub](https://github.com/alexanderjdupree)
* **Jacob Bickle** - *Co-Author* - [GitHub](https://github.com/jake-bickle)

See also the list of [contributors](https://github.com/AlexanderJDupree/LinkedListsCPP/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/AlexanderJDupree/LinkedListsCPP/blob/master/LICENSE) file for details

## Special Thanks

This readme and the contributing guidelines are based off this great [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
