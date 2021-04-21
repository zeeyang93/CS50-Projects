import cs50

# get input
while True:
    change = cs50.get_float("Change owed: ")
    if change > 0:
        break

# Cast to int, round it up and convert to cents
cents = round(int(change*100))

# coins counter, starting from 0
coins = 0
while cents > 0:
    while cents >= 25:
        coins += 1
        cents -= 25
    while cents >= 10:
        coins += 1
        cents -= 10
    while cents >= 5:
        coins += 1
        cents -= 5
    while cents >= 1:
        coins += 1
        cents -= 1

print(coins)