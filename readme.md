# Scientific Calculator

A feature-rich scientific calculator built with **C++** using **SFML** for the graphical interface and advanced mathematical computations. This calculator supports basic arithmetic, trigonometric functions, logarithmic operations, and more.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Operators](#supported-operators)
- [Dependencies](#dependencies)
- [Configuration](#configuration)
- [Examples](#examples)
- [Troubleshooting](#troubleshooting)
- [Contributors](#contributors)

## Introduction
This scientific calculator application offers a simple yet powerful interface for performing complex mathematical calculations. Built using **C++** and **SFML**, it includes support for both basic operations (addition, subtraction, multiplication, division) and advanced functions such as trigonometry and logarithms.

## Features
- Graphical user interface built using **SFML**.
- Supports both **binary** and **unary** mathematical operations.
- Functional buttons for trigonometric, logarithmic, and other advanced calculations.
- Clear button (`AC`) to reset the display.
- Real-time calculation results displayed.

## Installation
To install and run the scientific calculator, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML
    ```
   
2. **Install SFML** (if not already installed):
    - On Ubuntu:
      ```bash
      sudo apt-get install libsfml-dev
      ```
    - On Windows, download from the [official SFML website](https://www.sfml-dev.org/download.php).

3. **Build the project** using `make` or any compatible build tool:
    ```bash
    make
    ```

4. **Run the executable**:
    ```bash
    ./scientific_calculator
    ```

## Usage
- Use the graphical interface to input numbers and select the desired mathematical operation.
- Operations include basic arithmetic, trigonometric functions (sin, cos, tan), logarithms, square root, and exponentiation.
- Press the `=` button to compute the result.
- The `AC` button clears the current input.

## Supported Operators
The calculator supports the following operators with parentheses:

| Operator | Definition         | Type  |
|----------|--------------------|-------|
| +        | Addition            | Binary|
| -        | Subtraction         | Binary|
| *        | Multiplication      | Binary|
| /        | Division            | Binary|
| x^2      | Squared             | Binary|
| x^y      | Exponential         | Binary|
| neg()    | Negation            | Unary |
| abs()    | Absolute Value      | Unary |
| sqrt()   | Square Root         | Unary |
| sin()    | Sine                | Unary |
| cos()    | Cosine              | Unary |
| tan()    | Tangent             | Unary |

## Dependencies
- **SFML** (Simple and Fast Multimedia Library): Used for rendering the calculator UI and handling events.
- **C++ Standard Library**: Used for mathematical operations and other core functionalities.

## Configuration
No special configuration is required. Ensure that SFML is installed and properly linked during the compilation process.

## Preview
![Example 1](https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML/blob/main/Resources/Screenshot-2024-10-22%20115609.png)
![Example 2](https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML/blob/main/Resources/Screenshot-2024-10-22%20115738.png)
![Example 3](https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML/blob/main/Resources/Screenshot-2024-10-22%20115758.png)
![Example 4](https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML/blob/main/Resources/Screenshot-2024-10-22%20115838.png)
![Example 5](https://github.com/SafalNarsingh/Scientific-Calculator-with-SFML/blob/main/Resources/Screenshot-2024-10-22%20115956.png)

## Examples
1. **Addition**:
    - Input: `5 + 3`
    - Output: `8`

2. **Square Root**:
    - Input: `sqrt(16)`
    - Output: `4`

3. **Trigonometric Function**:
    - Input: `sin(30)`
    - Output: `0.5`

## Troubleshooting
- **SFML Not Found**: Ensure that SFML is properly installed and linked during the build process. Check your `Makefile` or build configuration.
- **Incorrect Calculations**: Ensure that you are entering valid mathematical expressions.

## Contributors
- Safal Narshing Shrestha - Developer

> Last updated by Safal Narhsing Shrestha on Oct 22, 2024, 12:24. </br> Copyright © 2024 Safal Narshing Shrestha. All rights reserved.
#
