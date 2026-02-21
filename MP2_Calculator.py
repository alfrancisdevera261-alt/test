##Calculator
print("===== Basic Calculator =====")
print("Choose the operation you want to perform:")
print("1. Addition (+)")
print("2. Subtraction (-)")
print("3. Multiplication (*)")
print("4. Division (/)")
print("5. Modulus (%)")
print("6. Exponentiation (**)")
print("7. Reciprocal (1/x)")
print("8. Square Root (√x)")
operation = input("Enter the number corresponding to the operation (1-8): ")

print("=================================")
print("       Basic  Calculator         ")
print("=================================")
if operation == '1':
    number1 = float(input("Enter the first number: "))
    number2 = float(input("Enter the second number: "))
    result = number1 + number2
    print(f"The sum is: {result}")
elif operation == '2':
    number1 = float(input("Enter the first number: "))
    number2 = float(input("Enter the second number: "))
    result = number1 - number2
    print(f"The difference is: {result}")
elif operation == '3':
    number1 = float(input("Enter the first number: "))
    number2 = float(input("Enter the second number: "))
    result = number1 * number2
    print(f"The product is: {result}")
elif operation == '4':
    number1 = float(input("Enter the first number: "))
    number2 = float(input("Enter the second number: "))
    if number2 != 0:
        result = number1 / number2
        print(f"The quotient is: {result}")
    else:
        print("Error: Division by zero is not allowed.")
elif operation == '5':
    number1 = float(input("Enter the first number: "))
    number2 = float(input("Enter the second number: "))
    result = number1 % number2
    print(f"The modulus is: {result}")
elif operation == '6':
    number1 = float(input("Enter the base number: "))
    number2 = float(input("Enter the exponent: "))
    result = number1 ** number2
    print(f"The result of exponentiation is: {result}")
elif operation == '7':
    number1 = float(input("Enter the number: "))
    if number1 != 0:
        result = 1 / number1
        print(f"The reciprocal is: {result}")
    else:
        print("Error: Reciprocal of zero is not defined.")
elif operation == '8':
    number1 = float(input("Enter the number: "))
    if number1 >= 0:
        result = number1 ** 0.5
        print(f"The square root is: {result}")
    else:
        print("Error: Square root of a negative number is not defined.")
else:
    print("Invalid operation selected.")
print("=================================")