# audio-steganography

Proof of concept Audio steganography program to hide secret messages inside unsuspecting Audio Files. This is the first prototype, which only does a basic lsb infection at this time.

# Instructions

Compile and setup

       chmod u+x compile.sh
      ./compile.sh
      
run the following with no arguments to see help instructions on using the program
          
       ./stegbot
       
To infect the mp3 testfile the program requires the following arguments:

       ./stegbot <i> <"secret message"> <soundfile.mp3> 
       
To extract the secret message from the mp3 testfile the program requires the following arguments:

       ./stegbot <x> <soundfile.mp3>
       
       

# Misc

This is a proof of concept. It is not meant to be a complete or very useful program. Just a proof of concept.

When the altered file is open in a GUI Audio Player such as VLC, the AudioFile seems to remain intact and doesn't arise suspicion. If using a graphical
video/audio player to play it.



**Note.1**: the Audiofile becomes unplayable if you replace every lsb of every byte, so message length is a factor. So be careful how long your secret message is. I have not tested boundries but I've tested changing the lsb of every byte in the file, which destroys the soundfile.


**Note.2**: This is a very quick prototype, started and completed in a day, just as a proof of concept. Not much error checking has been added. I don't claim it's as efficient as it could be. Which will be improved upon in future updates.


**Note.3**: This has only been tested against .mp3 soundfiles.


**Note.4**: Don't forget to put your secret message within " " (double quotes , especially if your secret message is more than one word and has special symbols)

**Note.5**: An Mp3 file is already supplied for testing which is then moved to the current directory from the backup audio directory to be used for testing the program against. Once you *./compile.sh* to set the environment up.

# Not being maintained
