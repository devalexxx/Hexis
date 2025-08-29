# Hexis

**Hexis** is a C++ utility library containing commonly used tools and helpers to simplify development.  
It is organized into **components**, making it easy to include only what you need. Currently, it has two main components: **Core** and **Math**.

## Components

### Core
The Core component includes utilities for general C++ development:

- **EnumArray** – A container that allows using an `enum` as a key for an array.
- **ThreadPool** – A simple task manager to execute asynchronous tasks efficiently.
- **TypeList** – A compile-time list of types with useful type manipulation utilities.
- **Demangled Typename** – Retrieve human-readable type names at runtime.
- **LambdaAsFuncPtr** – Converts a lambda into a real function pointer by creating a functor and returning the underlying function.

### Math
The Math component provides numeric utilities:

- **Float equality with epsilon** – Compare floating-point numbers with a configurable tolerance.

## Installation

Build options:
- `mode`: `debug` or `release` (default: `debug`)
- `shared`: `y` or `n` (default: `n`)
- `unittest`: `y` or `n` (default: `n`)
- `math`: `y` or `n` (default: `n`)

### From Github

```bash
    # Clone the repository
    git clone https://github.com/hexis-framework/hexis.git && cd hexis
    
    # Configure the target (--<module_name>=y to add any module) (configuration are optional)
    xmake f --mode=<debug|release> ...
    
    # Build and install
    xmake
```

### From xrepo

```bash
    # Add the repository
    xrepo add-repo hexis-repo https://github.com/devalexxx/xmake-repo.git main
    
    # Install the package
    xrepo install "mode=<release|debug>,..." hexis
```

## Usage

````lua
    add_rules("mode.debug", "mode.release")
    
    set_language("c++23")
    
    add_repositories("hexis-repo https://github.com/devalexxx/xmake-repo.git")
    
    -- Or add path to the folder previously builded
    add_requires("orion", { config = { debug = is_mode("debug") } })
    
    target("test")
        set_kind("binary")
        add_files("src/*.cpp")
    
        add_packages("hexis")
````

```c++
    #include <Hexis/Core/EnumArray.h>
    
    enum class MyEnum { A, B, C };
    
    int main(int argc, char** argv) 
    {
        Hx::EnumArray<MyEnum, int> array {{
            {MyEnum::A, 1},
            {MyEnum::B, 2},
            {MyEnum::C, 3}
        }};
        
        auto value = array[MyEnum::A];
        // value == 1
        
        return EXIT_SUCCESS;
    }    
```
