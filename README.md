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
       
       

# Misc and future to do list

1. Provide other ways of infecting the audio file, at the moment this prototype only does infection by least significant bit.(More infection methods will be added)
2. Create some obsfucation techniques to better hide the secret message inside the audio file to avoid detection from forensic investigation.
3. Ability to encrypt.
