# import library
import cs50

# Get input from user

# Python while loop as always true
while True:
    height = cs50.get_int("Height: ")

    # breaks loop if fulfill condition
    if height > 0 and height <= 8:
        break

# Range is exclusive!
for i in range(height):

    # print spaces
    print(" " * (height - 1 - i), end="")

    # print #
    print("#" * (i + 1))