while True:
    print("\n=== LABORATORY ACTIVITY: Conditional Statements ===")
    print("1. Check if a Number is Positive or Negative")
    print("2. Even or Odd Number")
    print("3. Determine if Eligible to Vote")
    print("4. Grade Classification")
    print("5. Simple Discount Calculator")
    print("6. Largest Among Three Numbers")
    print("7. Salary Bonus Calculator")
    print("8. Simple ATM Menu")
    print("9. Selecting a Beverage")
    print("10. Horoscope Finder")
    print("Q. Quit")

    choice = input("Enter your choice: ").strip().upper()

    if choice == "1":
        num = float(input("Enter a number: "))
        if num > 0:
            print("The number is positive.")
        elif num < 0:
            print("The number is negative.")
        else:
            print("The number is zero.")

    elif choice == "2":
        try:
            n = int(input("Enter a number: "))
            if n % 2 == 0:
                print(f"{n} is even.")
            else:
                print(f"{n} is odd.")
        except ValueError:
            print("Invalid input. Please enter an integer.")

    elif choice == "3":
        try:
            age = int(input("Enter your age: "))
            if age >= 18:
                print("You are eligible to vote.")
            else:
                print("You are not eligible to vote.")
        except ValueError:
            print("Please enter a valid integer for age.")

    elif choice == "4":
        try:
            grade = float(input("Enter grade (0-100): "))
            if grade < 0 or grade > 100:
                print("Grade must be between 0 and 100.")
            elif grade >= 90:
                print("Excellent")
            elif grade >= 80:
                print("Very Good")
            elif grade >= 70:
                print("Good")
            elif grade >= 60:
                print("Needs Improvement")
            else:
                print("Failed")
        except ValueError:
            print("Please enter a valid number.")

    elif choice == "5":
        try:
            amt = float(input("Enter total amount: "))
            if amt >= 1000:
                print(f"Discounted amount: {amt * 0.9}")
            else:
                print(f"No discount. Total amount: {amt}")
        except ValueError:
            print("Invalid amount.")

    elif choice == "6":
        try:
            a = float(input("Enter first number: "))
            b = float(input("Enter second number: "))
            c = float(input("Enter third number: "))
            if a >= b and a >= c:
                print(f"The largest number is {a}")
            elif b >= a and b >= c:
                print(f"The largest number is {b}")
            else:
                print(f"The largest number is {c}")
        except ValueError:
            print("Invalid input. Please enter numbers.")

    elif choice == "7":
        try:
            salary = float(input("Enter salary: "))
            years = float(input("Enter years of service: "))
            if years >= 10:
                salary *= 1.10
            elif years >= 5:
                salary *= 1.05
            print(f"Final salary with bonus: {salary}")
        except ValueError:
            print("Please enter numeric values only.")

    elif choice == "8":
        print("\nATM Menu")
        print("1. Balance Inquiry")
        print("2. Deposit")
        print("3. Withdraw")
        print("4. Exit")
        atm_choice = input("Enter your choice: ")
        if atm_choice == "1":
            print("You chose Balance Inquiry.")
        elif atm_choice == "2":
            print("You chose Deposit.")
        elif atm_choice == "3":
            print("You chose Withdraw.")
        elif atm_choice == "4":
            print("You chose Exit.")
        else:
            print("Invalid choice.")

    elif choice == "9":
        print("\n1. Coke\n2. Sprite\n3. Royal\n4. Water\n5. Coffee")
        beverage = input("Input number of beverage choice: ")
        if beverage == "1":
            print("You chose COKE")
        elif beverage == "2":
            print("You chose SPRITE")
        elif beverage == "3":
            print("You chose ROYAL")
        elif beverage == "4":
            print("You chose WATER")
        elif beverage == "5":
            print("You chose COFFEE")
        else:
            print("Invalid choice.")

    elif choice == "10":
        print("\nAvailable zodiac signs:")
        print("Aries, Taurus, Gemini, Cancer, Leo, Virgo, Libra, Scorpio, Sagittarius, Capricorn, Aquarius, Pisces")
        sign = input("Enter your zodiac sign: ").strip().lower()
        if sign == "scorpio":
            print("You will have a lucky day. Lucky color is blue. Lucky number is 3.")
        elif sign == "aries":
            print("Be bold today — new opportunities may come your way.")
        elif sign == "taurus":
            print("Slow and steady progress will benefit you. Trust the process.")
        elif sign == "gemini":
            print("A conversation could spark an interesting idea. Listen carefully.")
        elif sign == "cancer":
            print("Take time for self-care; it will recharge your energy.")
        elif sign == "leo":
            print("Your confidence attracts attention — use it kindly.")
        elif sign == "virgo":
            print("Organization will bring clarity to a messy situation.")
        elif sign == "libra":
            print("Seek balance. A choice will require finding the middle ground.")
        elif sign == "sagittarius":
            print("Adventure calls — consider a short trip or new class.")
        elif sign == "capricorn":
            print("Hard work pays off; focus on steady goals.")
        elif sign == "aquarius":
            print("Innovative thinking helps you solve a problem.")
        elif sign == "pisces":
            print("Creativity is high — make time for a hobby or art.")
        else:
            print("Unknown zodiac sign.")

    elif choice == "Q":
        print("Exiting the program. Goodbye!")
        break

    else:
        print("Invalid choice. Please try again.")
