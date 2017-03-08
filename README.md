# Audio_responder
Basic OpenCV colour filter that uses system("mplayer") to play audio corresponding to object location.

Demo available on https://www.youtube.com/watch?v=6hNC-waXiZM

This repo contains the following files:

- The main code (track_aud.cpp)
- shell file for Linux users
- Audio responses from 0-9

The current code will work on Linux systems. To run on Windows, replace 

system("mplayer file.mp3");	

with:

system("start C:\\path_to\\file.mp3");

Note:- Every audio response delays a frame by its own length in seconds. Thus, if you need to add your own responses,
ensure that they're as short as possible
