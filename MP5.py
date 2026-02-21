# Python Programming Exercises: Python Sets

# ------------------------------
# I. Create and modify a set
# ------------------------------
numbers = {1, 2, 3, 4, 5}
print("I. Original set:", numbers)
numbers.add(6)
print("After adding 6:", numbers)
print("-" * 40)

# ------------------------------
# II. Update fruits set
# ------------------------------
fruits = {'apple', 'banana', 'mango', 'orange'}
fruits.remove('banana')
fruits.add('grape')
print("II. Updated set:", fruits)
print("-" * 40)

# ------------------------------
# III. Union and Intersection
# ------------------------------
set1 = {1, 2, 3, 4}
set2 = {3, 4, 5, 6}
print("III. Union:", set1.union(set2))
print("Intersection:", set1.intersection(set2))
print("-" * 40)

# ------------------------------
# IV. Difference and Symmetric Difference
# ------------------------------
A = {'red', 'green', 'blue'}
B = {'yellow', 'green', 'orange'}
print("IV. Difference (A - B):", A - B)
print("Symmetric difference:", A.symmetric_difference(B))
print("-" * 40)

# ------------------------------
# V. Check if an animal is in the set
# ------------------------------
animals = {'dog', 'cat', 'bird', 'fish'}
animal = input("V. Enter an animal: ").lower()

if animal in animals:
    print(animal, "is in the set.")
else:
    print(animal, "is not in the set.")

print("Animals in the set:")
for a in animals:
    print(a)
print("-" * 40)
