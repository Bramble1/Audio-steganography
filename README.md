# audio-steganography

Proof of concept Audio steganography program. This is the first prototype, which only does a basic lsb infection at this time.

# Instructions

Compile and setup

       u+x compile.sh
      ./compile.sh
      
run the following with no arguments to see help instructions on using the program
          
       ./stegbot
       
To infect the mp3 testfile the program requires the following arguments:

       ./stegbot <i> <"secret message"> <soundfile.mp3> 
       
To extract the secret message from the mp3 testfile the program requires the following arguments:

       ./stegbot <x> <soundfile.mp3>
       
       
