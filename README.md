# WavefrontCubicTexturePacker [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

WavefrontCubicTexturePacker despite its long name does something very simple. It take an obj file with the associated png and try to pack the texture in the smallest possible size.

To do this it extract the quads from the obj file and then try to de-duplicate the similar textures.

# Build
This project was made in C++ 2017 and can be built with CMake, the generated Makefile will be located under cmake-build-debug/

# Usage
A basic example is `./wavefronttexturepacker mymodel`
It will retrieve an obj at ./mymodel.obj and an associated png at ./mymodel.png then output the results at ./output.obj and ./output.png.

The default is to not pack any identical parts of the texture and allow any dimension for the outputted texture.  
See the optional __-e__ to force the texture to be even or a power of two.

Multiples options can be specified:
* __--png__ \<FILE> specify the file path of the png file used for input
* __--obj__ \<FILE> specify the file path of the obj file used for input

* __-o, --output__ \<FILE NAME> specify the file path without the extension to use for output of both png and obj files
* __-e, --even-level__ \<NUMBER> how many times the size of the output texture remains even when divided by two;  
   for example __-e 1__ will allow any size divisible by 2, __-e 2__ divisible by 4 and so on.  
 Using __-e -1__ will make the output size a power of two like 16, 32, 64...  
 Using __-e 0__ is the same as not specifying the even level, any size is allowed.
 * __-p, --pack-similar__ if specified this flag will allow removal of duplicated texture parts;
  any faces of the same size with identical pixels values will be considered equals.
  * __-h, --help__ show the help message.
  
# Limits
The project is currently limited in its efficiency.  
It cannot parse any kind of wavefront files, it will only accept one where each group of four texture coordinates (vt ...) represent a quad.

The packing algorithm cannot save space by overlapping quads with identical portion of texture. Only the quads with strictly identical texture will be optimized.

It only pack in square textures atlas.