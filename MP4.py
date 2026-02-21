
def exercise1():
    # I. Enter 5 numbers, sort, and sum
    numbers = []
    for i in range(5):
        num = float(input(f"Enter number {i+1}: "))
        numbers.append(num)
    numbers.sort()
    print("Sorted list:", numbers)
    print("Sum:", sum(numbers))


def exercise2():
    # II. Tuple of colors
    colors = ('red', 'green', 'blue', 'yellow', 'orange')
    print("First color:", colors[0])
    print("Last color:", colors[-1])
    print("Number of colors:", len(colors))


def exercise3():
    # III. Modify fruit list
    fruits = ['apple', 'banana', 'mango']
    fruits.append('orange')
    fruits.remove('banana')
    print("Updated list:", fruits)


def exercise4():
    # IV. Convert list <-> tuple 
    animals = ['dog', 'cat', 'bird']
    print("Current list:", animals)

    choice = input("Do you want to convert this list to a tuple? (y/n): ").lower()

    if choice == 'y':
        animals_tuple = tuple(animals)
        print("Converted to tuple:", animals_tuple)

        back_choice = input("Do you want to convert it back to a list? (y/n): ").lower()
        if back_choice == 'y':
            animals_back = list(animals_tuple)
            print("Converted back to list:", animals_back)
        elif back_choice == 'n':
            print("Staying as tuple:", animals_tuple)
        else:
            print("Error: invalid choice. Please enter only 'y' or 'n'.")

    elif choice == 'n':
        print("The list stays the same:", animals)
    else:
        print("Error: invalid choice. Please enter only 'y' or 'n'.")


def exercise5():
    # V. Student records
    students = (('Anna', 85), ('Mark', 90), ('Luke', 88))
    print("Students and Scores:")
    for name, score in students:
        print(f"{name} - {score}")

    top_student = max(students, key=lambda x: x[1])
    print(f"Top student: {top_student[0]} ({top_student[1]})")


# --- Main Program Loop ---
while True:
    print("\n=== Python Programming Exercises: Lists and Tuples ===")
    print("1. Enter 5 numbers, sort, and sum")
    print("2. Tuple of colors")
    print("3. Modify fruit list")
    print("4. Convert list <-> tuple")
    print("5. Student records")
    print("6. Exit")

    choice = input("Choose an exercise (1-6): ")

    if choice == '1':
        exercise1()
    elif choice == '2':
        exercise2()
    elif choice == '3':
        exercise3()
    elif choice == '4':
        exercise4()
    elif choice == '5':
        exercise5()
    elif choice == '6':
        print("Goodbye!")
        break
    else:
        print("Error: Please choose a number from 1 to 6.")
