import csv
import sys

# check input length
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit()

# read file
with open(sys.argv[2]) as DNAfile:
    DNAreader = list(csv.reader(DNAfile))
    # list converts reader file straight into array
    # Note: list is an array, it stores each rows it reads as another array. The output here is actually a "nested" array !

# store it as string. Convert from arrays to string
DNAstring = DNAreader[0][0]

# create dictionary and array
sequences = {}
DNAsequences = []

# Open the databases csv file. As of now, we are only interested in the first row of sequences
with open(sys.argv[1]) as peoplefile:
    people = list(csv.reader(peoplefile))

    # Only extract the first line. Alternatively, use readline
    DNAsequences = people[0]

    # Pop removes item from array. Here, remove the first element 'name'
    DNAsequences.pop(0)


# Here, it assigns each key with value 1 into the dictionary sequence.
for item in DNAsequences:
    sequences[item] = 1

# Counter for DNAsequences found in the DNAstring
for key in sequences:
    keylength = len(key)
    countMax = 0
    count = 0

    for i in range(len(DNAstring)):

        # purpose of this loop is to stop counting after having encountered a similar sequence
        # This will reset the counter  to 0
        while count > 0:
            count -= 1
            continue

        # if there is a segment of DNAstring coresponds to key AND there is a repetition of it, increase counter
        if DNAstring[i: i + keylength] == key:

            # if there is repetition of it immediately after, increase counter
            while DNAstring[i - keylength: i] == DNAstring[i: i + keylength]:
                count += 1
                i += keylength

            # We only need to keep track of longest sequence
            # Hence update it if found a new one
            if count > countMax:
                countMax = count

    # store the longest sequences into the dictionary with the correspondent key
    sequences[key] += countMax

# open the database file with DictReader, and compare it with the files
# this comparision is applicable to both large and small csv files
with open(sys.argv[1], newline='') as peoplefile:
    people = csv.DictReader(peoplefile)
    for person in people:
        sequence_match = 0

        # compares the sequences to every person and print it. Break if there is a match
        for DNA in sequences:
            # if the value of dictionary sequence equals to the integer of persons dictionary sequence
            if sequences[DNA] == int(person[DNA]):
                # match counter plus 1
                sequence_match += 1

        # if the match counter is equal to the total length of the dictionary sequance (ie. exact match)
        if sequence_match == len(sequences):
            print(person['name'])
            exit()

    print("No match")
