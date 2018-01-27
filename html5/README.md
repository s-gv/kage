Kage
====

The html5 version of Kage can be played in web browsers that support WebGL.

Dependencies
------------

- Emscripten 1.37

Notes
-----

- Audio should be mono, in 44-byte header WAV, with samples in 16bit signed (little-endian) format, and sampled at 44.1 kHz. (If needed, convert with, `sox -v 0.5 input.wav -c 1 -r 44100 -e signed-integer --endian little output.wav`)