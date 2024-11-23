# Cool Media Player

Made in C++ using SFML-2.6.2

Under Development

It should have the ability to play audio (WAV, OGG/Vorbis and FLAC. MP3 ) and video (libvlcpp)

Make sure to get [tinyfiledialog](https://github.com/native-toolkit/libtinyfiledialogs) and include it to the repo

# Controls

Pause/Resume : Space

Volume Up : Up Arrow

Volume Down : Down Arrow

Forward 1 second : Right Arrow

Backward 1 second : Left Arrow

Exit : Esc

Show information : O

# Dependencies ( Visual Studio 2022 Debug only )

sfml-graphics-s-d.lib;

sfml-window-s-d.lib;

sfml-system-s-d.lib;

sfml-audio-s-d.lib;

%(AdditionalDependencies)

opengl32.lib;

winmm.lib;

gdi32.lib;

freetype.lib;

comdlg32.lib;

ole32.lib;

openal32.lib;

flac.lib;

vorbisenc.lib;

vorbisfile.lib;

vorbis.lib;

ogg.lib;

**For the release remove the `-d` from anything above `%(AdditionalDependencies)`**
