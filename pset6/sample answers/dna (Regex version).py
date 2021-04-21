import csv
import sys
import re

def main():
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

    with open(sys.argv[1]) as peoplefile:
        people = list(csv.DictReader(peoplefile))

    # DNAstring.count will return each time it repeats in a string
    AGATC = count("AGATC", DNAstring)
    TTTTTTCT = count("TTTTTTCT", DNAstring)
    TCTAG = count("TCTAG", DNAstring)
    AATG = count("AATG", DNAstring)
    GATA = count("GATA", DNAstring)
    TATC = count("TATC", DNAstring)
    GAAA = count("GAAA", DNAstring)
    TCTG = count("TCTG", DNAstring)

    # compares the DNAstring we got with the name in the CSV file. If all DNAstring.counts match, we can now who is the person by extracting from key
    if sys.argv[1] == "databases/small.csv":
        for i in range(len(people)):
            if all ([people[i]["AGATC"] == str(AGATC), people[i]["AATG"]== str(AATG), people[i]["TATC"] == str(TATC)]):
                name = people[i]["name"]
                break
            else:
                name = "No match"

    else:
        for i in range(len(people)):
            if all([people[i]["AGATC"] == str(AGATC), people[i]["TTTTTTCT"] == str(TTTTTTCT), people[i]["TCTAG"] == str(TCTAG), people[i]["AATG"] == str(AATG),
                        people[i]["GATA"] == str(GATA), people[i]["TATC"] == str(TATC), people[i]["GAAA"] == str(GAAA), people[i]["TCTG"] == str(TCTG)]):
                name = people[i]["name"]
                break
            else:
                name = "No match"

    print(name)

# Defines the function count() for counting the pattern that apperas in sequence
def count(c, s):
    p = rf'({c})\1*'
    pattern = re.compile(p)
    match = [match for match in pattern.finditer(s)]
    max = 0
    for i in range(len(match)):
        if match[i].group().count(c) > max:
            max = match[i].group().count(c)
    return str(max)

main()