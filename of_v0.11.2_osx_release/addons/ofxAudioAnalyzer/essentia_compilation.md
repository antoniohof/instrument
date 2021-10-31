## Essentia static build compilation

 Essentia and Fftw3 static builds in /libs were compiled using Essentia's source at *commit a71fcb548fe41a2a732f93723de85d27f823bf72* .

### Compilation

Source: https://github.com/MTG/essentia/blob/master/FAQ.md

#### Install dependencies
For building lightweight version, only fftw is necessary:
* On Linux:
`apt-get install libfftw3-dev`

* On OSX:
  - Xcode Command-Line Tools: Install Command Line Tools for Xcode. Even if you install Xcode from the app store you must configure command-line compilation by running:
  `xcode-select --install`

  - Install Brew: Paste command from:  http://brew.sh/

  - Install homebrew formula (https://github.com/MTG/homebrew-essentia):

    * Install homebrew tap: `brew tap MTG/essentia`
    * Install Essentia compiling the code (slower): `brew install essentia --HEAD`



#### Compile static lightweight version of Essentia:
* Download Essentia source code from https://github.com/MTG/essentia.

* Configure compilation:

 `./waf configure --mode=release --build-static --lightweight=fftw`

- Compile (to: build/src/libessentia.a)

 `./waf`


#### Compile static Fftw:

* On Linux:
  `apt-get install yasm cmake`
* On OSX:
  `brew install yasm cmake wget`

* Compile :

  `cd packaging/debian_3rdparty`

  `build_fftw3.sh`
