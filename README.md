# Homemade-DiffieHelman

This is a home made Diffie-Helman style key exchange and AES encryption algorithm project.
*(for the learnings of yours truly)*

# INSTALL

just do make and everything gets done.

# USAGE


To get a public/private key combo, do

    ./crypto -k

To get your public key, do

    ./crypto -K

Just enter your private key and it will give you your public key!

To encode a file foo just do

    ./crypto -e foo

To decode a file foo just do

    ./crypto -d foo

To set the output location of either the encoded or decoded file foo to bar do

    ./crypto -e foo -o bar

Thats it! Now you can publish your public key and communicate securely (As long as P != NP).
