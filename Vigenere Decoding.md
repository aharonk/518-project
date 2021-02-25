### Accidental Vigenere Decoding

The most common way of identifying probable keys of a Vigenere Cipher is frequency analysis of the decoded text, and
it's as good a way as any to test random solutions.

##### Step 1: Create Keys

Some large number of times, create a random key, decode the message, and find the total difference between the frequency
of each letter in the decoded message and in English. If the total difference is under some threshold, store the key and
total frequency difference.

##### Step 2: Mutate Keys

Once you have keys with a possibility of being correct, a good way to get better keys is to randomly mutate letters of
the key, hoping to get a better frequency. If they new key is better than its base, add it to your possibilities. At
some point, also narrow your possibilities down to a lower threshold.

##### Step 3: Recombine Keys

Rather than randomly change keys and hope they'll get better, you can take two keys and combine them in different ways
to get keys that will be more accurate, because instead of one key and randomness, you have two keys, so you are off to
a more likely start. If the new key's frequency is better than either of its donors, add it to the list.

The best way to return the list is by probability, rather than alphabetically, so sort it a such.