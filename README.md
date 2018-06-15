

# LinkedListsCPP

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c24f1655cc534243b8ab5bcd60c8302c)](https://www.codacy.com/app/AlexanderJDupree/LinkedListsCPP?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AlexanderJDupree/LinkedListsCPP&amp;utm_campaign=Badge_Grade)
[![Build Status](https://travis-ci.org/AlexanderJDupree/LinkedListsCPP.svg?branch=master)](https://travis-ci.org/AlexanderJDupree/LinkedListsCPP)
[![codecov](https://codecov.io/gh/AlexanderJDupree/LinkedListsCPP/branch/master/graph/badge.svg)](https://codecov.io/gh/AlexanderJDupree/LinkedListsCPP)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/AlexanderJDupree/LinkedListsCPP/master/LICENSE)

C++ Template Library for Linked Lists Data Structures

TODO Description on linked lists qualities, time and space complexity. 

- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Execute unit tests](#execute-unit-tests)
- [Deployment](#deployment)
- [Built With](#built-with)
- [Contributing](#contributing)
- [Versioning](#versioning)
- [Authors](#authors)
- [License](#license)

## Getting Started

TODO instructions for geting a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

TODO Required software, links, and installation instruction.

```
Give examples
```

### Installation

TODO Step by Step instructions for including this repo into a C++ project

```
Code Example
```

### Usage

TODO Instructions on basic usage of linkedLists library

```
Code Example
```

## Execute Unit Tests

To execute Unit Tests, you must first build the project. Once built, the resulting executeable will reside in **tests/debug/runTests**

- Command Line

Building and executing from the command line is simple!
To build, navigate to the project's home directory (where you cloned it) and enter the following:
```
make
```
Afterwards, execute by entering the following:
```
./tests/debug/runTests
```

The first time you enter _make_ may take a minute, as it must build the [catch2 framework](https://github.com/catchorg/Catch2). However, _make_ will keep all of the resulting obj files in the _tests/bin/_ directory. Afterwards, _make_ will only build files you have updated, and link them together again.

If you find it necessary, you may **remove** the obj files from _tests/bin/_ by entering the following
```
make clean
```
Of course, the next time you use _make_ it will take a minute to build everything again.

- TODO Visual Studio Code

## Deployment

TODO add notes on how to deploy this onto a system

## Built With

* [Catch2](https://github.com/catchorg/Catch2) - Unit Testing framework used

## Contributing

Please read [CONTRIBUTING.md](https://github.com/AlexanderJDupree/LinkedListsCPP/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/AlexanderJDupree/LinkedListsCPP/tags). 

## Authors

* **Alexander DuPree** - *Initial work* - [GitHub](https://github.com/alexanderjdupree)
* **Jacob Bickle** - *Co-Author* - [GitHub](https://github.com/jake-bickle)

See also the list of [contributors](https://github.com/AlexanderJDupree/LinkedListsCPP/graphs/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/AlexanderJDupree/LinkedListsCPP/blob/master/LICENSE) file for details
