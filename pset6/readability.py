import cs50

# Text input
text = cs50.get_string("Text: ")

# Initialise variables
letters = 0
words = 1  # additional word for every number of space
sentences = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1

    if text[i] == " ":
        words += 1

    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Apply formula
L = (letters / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print grades
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")