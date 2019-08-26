# Fraktalkundschafter

This is a fractal renderer with focus on extensibility to discover (unseen) fractals rendered by the Twin Procedure as defined by Gabi Müller.

## To build on Linux

You'll need the C++ Gtk bindings:


```
sudo apt install libgtkmm-3.0-dev 
```

Then you can compile using ether make

```
make
```

or buildfox and ninja

```
bf && ninja -t clean && ninja
```

This repo contains the latest prebuild binary for AMD64 architecture under bin/

## Customize
In order to add your own formulas, iterations and color-schemes, you only have to add them to the corresponding files: 

- src/fractal_funtions.hpp
- src/iterations.hpp
- src/colors.hpp

and introduce your function/iteration/color-sheme to the UI in setup_combo_entries() in src/main.cpp. The code contains many examples to get you started.


