# Convex Hull

A small C++ project implementing classic computational geometry concepts—focused on convex hull algorithms. Includes helper types such as points, lines, line segments, circles, and more. Also contains test data and utilities for visualizing or verifying results.

---


## What’s in here

This repository includes:

- Geometric primitives: `Point`, `Line`, `LineSegment`, `Circle`, etc.  
- Convex Hull implementation(s) (incremental / Graham scan / others).  
- Utility / helper modules to compute intersections, distances, checks.  
- A `test.dat` file with sample input(s) for manual testing.  
- A “presentation” (`prezi.cpp`) or visual demo code to illustrate behavior.

---

## Structure

Here are the key directories / files:

| File / Folder | Purpose |
|---------------|---------|
| `point.hpp` / `.cpp` | Definition and operations on 2D points |
| `line.hpp` / `.cpp` | Lines, line equations, intersection checks |
| `linesegment.hpp` | Segments between two points, segment‐line/segment‐segment intersection |
| `circle.hpp` / `.cpp` | Circle shapes, maybe used for specialized hull or inclusion checks |
| `helper.cpp` / `.hpp` | Utility functions: maybe orientation, sorting, distance, comparisons |
| `common.hpp` | Shared types/macros/utilities used across modules |
| `circle.cpp`, `line.cpp`, etc. | Implementation files |
| `prezi.cpp` | Demo / visualization / example code |
| `test.dat` | Sample test data input for verifying behavior |

---

## How to build

Assuming you have a C++ compiler (g++, clang++, MSVC) that supports C++17 or later:

```bash
git clone https://github.com/zstarczali/convex-hull.git
cd convex-hull

# Example build using g++
g++ -std=c++17 point.cpp line.cpp linesegment.cpp circle.cpp helper.cpp prezi.cpp -o convex-hull-demo

# Or build parts separately if you only want the core hull/challenge modules:
g++ -std=c++17 point.cpp line.cpp linesegment.cpp helper.cpp circle.cpp -o hullcore
```

On Windows / Visual Studio, you can open the files as a project, or compile via the command line similarly.

## Usage
Once compiled, you can run the executable with sample data in test.dat or feed your own input:
`./convex-hull-demo test.dat`
Make sure your input format matches what the core code expects (points, maybe edges, etc.). (See `prezi.cpp` for example of usage.)

If you want to integrate or reuse modules (point, line, intersection), you can include header files in your own project.

## Tests
There is a sample input file test.dat to help you try out and verify the behavior. You can compare output of your convex hull implementation with expected shape, or test edge cases:

  - All points colinear
  - Small number of points (e.g. 0, 1, 2)
  - Large random point clouds
  - Points on the boundary versus strictly inside

## License
This project is licensed under the GPL-3.0 License. See the LICENSE file for full details.
