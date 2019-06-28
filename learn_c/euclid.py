""" implementation of Euclids Algorithm to find GCD of two numbers in C """
def euclid(x, y):
    while y:
        x, y = y, x % y
    return x

user_input = input("Please two natural numbers where the second number is greater than the first, \
    separated by a space: ").split(" ")
x, y = int(user_input[0]), int(user_input[1])
print(f"You have entered {x} and {y}, the GCD is {euclid(x, y)}")