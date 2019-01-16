

# LinkedListsCPP

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c24f1655cc534243b8ab5bcd60c8302c)](https://www.codacy.com/app/AlexanderJDupree/LinkedListsCPP?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AlexanderJDupree/LinkedListsCPP&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/AlexanderJDupree/LinkedListsCPP.svg?branch=release)](https://travis-ci.org/AlexanderJDupree/LinkedListsCPP)
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

**LinkedListsCPP** is a fully templated linked list data structure repository that will, in the future, contain C++ implementations of different linked lists. Currently, only the linear linked list structure is implemented in the release build. 

Linked lists are sequence containers that allow for constant time insertion and removal operations within the sequence. The linear linked list is a singly-linked structure where each element in the sequence is linked to the next element in the sequence. The main drawback of linked lists is the inability to directly access elements by position. Linked lists require traversal to access elements not located on the front or end of the list. The linear linked list is further hampered by the inability to freely traverse its contents. linear linked lists can only be traversed from beginning to end by use of iterators. However, linked lists can expand and contract in size dynamically at runtime, this makes them a very useful data structure.   

## Getting Started

- Download the latest [release here](https://github.com/AlexanderJDupree/LinkedListsCPP/releases).

### Prerequisites
- LinkedList.hpp utilizes C++ 11 language features and will **NOT** compile in older C++ language standards.

All releases are header only, meaning all you need to do to get started is drop the header into a visible include path for your project. Once the file is reachable from your project you can start using the linked list container like this:

```c++
#include <iostream>
#include "linked_list.hpp"

int main()
{
    linear_linked_list<char> list { 'H', 'E', 'L', 'L', 'O', '!' };

    for(const char& letter : list)
    {
        std::cout << letter;
    }

    // Prints "HELLO!" to the console

    return 0;
}
```


### Usage

Extensive documentation can be expected for the future. For right now, however, please read header comments or examine how the linked lists are used in the unit tests for usage instructions.

## Execute Unit Tests

For those who wish to contribute and execute the unit tests follow these instructions:

_Windows users, ensure you have **MinGW-Make** installed and included in your PATH._
_For instructions see this [link](http://mingw.org/wiki/Getting_Started)_

- First, clone the repository
```bash
git clone https://github.com/AlexanderJDupree/LinkedListsCPP.git
```

- Navigate to the project directory
```bash
cd LinkedListsCPP
```

- And just call make
```bash
make
```
- Now you can execute the unit tests by typing

```
./tests/debug/run_tests
```

The first time you enter _make_ may take a minute, as it must build the [Catch2 framework](https://github.com/catchorg/Catch2). However, _make_ will keep all of the resulting obj files in the _tests/bin/_ directory. Afterwards, _make_ will only build files you have updated, and link them together again.

If you find it necessary, you may **remove** the obj files from _tests/bin/_ by entering the following
```
make clean
```
Of course, the next time you use _make_ it will take a minute to build everything again.

## Built With

* [Catch2](https://github.com/catchorg/Catch2) - Unit Testing framework used

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
