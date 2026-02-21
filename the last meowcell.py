import json
import random
import os
import sys

# ---------- File Saves ----------
PROJECT_DIR = os.path.dirname(os.path.abspath(__file__))
SAVE_FILE = os.path.join(PROJECT_DIR, "the_meow_players.json")
QUESTION_FILE = os.path.join(PROJECT_DIR, "the_meow_questions.json")

# ---------- Sample question bank ----------
SAMPLE_QUESTIONS = [
  {
    "subject": "Math",
    "question": "What is 8 * 7?",
    "choices": ["54", "56", "58", "64"],
    "answer": "56",
    "hint": "Think 8 groups of 7.",
    "difficulty": "easy"
  },
  {
    "subject": "Science",
    "question": "Water's chemical formula is?",
    "choices": ["H2O", "CO2", "O2", "NaCl"],
    "answer": "H2O",
    "hint": "Two hydrogens and one oxygen.",
    "difficulty": "easy"
  },
  {
    "subject": "History",
    "question": "Who was the first President of the United States?",
    "choices": ["Abraham Lincoln", "Thomas Jefferson", "George Washington", "John Adams"],
    "answer": "George Washington",
    "hint": "He crossed the Delaware.",
    "difficulty": "easy"
  },
  {
    "subject": "Geography",
    "question": "What is the capital of France?",
    "choices": ["Lyon", "Paris", "Marseille", "Nice"],
    "answer": "Paris",
    "hint": "City of lights.",
    "difficulty": "easy"
  },
  {
    "subject": "Biology",
    "question": "How many bones does an adult human have?",
    "choices": ["186", "206", "226", "246"],
    "answer": "206",
    "hint": "It's between 200-210.",
    "difficulty": "medium"
  },
  {
    "subject": "Literature",
    "question": "Who wrote 'Romeo and Juliet'?",
    "choices": ["Jane Austen", "William Shakespeare", "Charles Dickens", "Mark Twain"],
    "answer": "William Shakespeare",
    "hint": "Famous English playwright.",
    "difficulty": "easy"
  },
  {
    "subject": "Physics",
    "question": "What is the SI unit of force?",
    "choices": ["Joule", "Newton", "Pascal", "Watt"],
    "answer": "Newton",
    "hint": "Named after a famous scientist.",
    "difficulty": "easy"
  },
  {
    "subject": "Math",
    "question": "What is the square root of 144?",
    "choices": ["10", "11", "12", "13"],
    "answer": "12",
    "hint": "12 * 12 = 144.",
    "difficulty": "easy"
  },
  {
    "subject": "History",
    "question": "In what year did World War II end?",
    "choices": ["1943", "1944", "1945", "1946"],
    "answer": "1945",
    "hint": "It's in the 1940s.",
    "difficulty": "medium"
  },
  {
    "subject": "Art",
    "question": "Who painted the Mona Lisa?",
    "choices": ["Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso", "Michelangelo"],
    "answer": "Leonardo da Vinci",
    "hint": "Italian Renaissance master.",
    "difficulty": "easy"
  },
  {
    "subject": "Technology",
    "question": "What does CPU stand for?",
    "choices": ["Central Process Unit", "Central Processing Unit", "Computer Personal Unit", "Central Processor Utility"],
    "answer": "Central Processing Unit",
    "hint": "The brain of the computer.",
    "difficulty": "easy"
  },
  {
    "subject": "Sports",
    "question": "How many players are on a basketball team on the court?",
    "choices": ["4", "5", "6", "7"],
    "answer": "5",
    "hint": "Each side has the same number.",
    "difficulty": "easy"
  },
  {
    "subject": "Geography",
    "question": "What is the largest ocean on Earth?",
    "choices": ["Atlantic", "Indian", "Arctic", "Pacific"],
    "answer": "Pacific",
    "hint": "It covers the most area.",
    "difficulty": "easy"
  },
  {
    "subject": "Music",
    "question": "How many strings does a standard guitar have?",
    "choices": ["4", "5", "6", "7"],
    "answer": "6",
    "hint": "Think of EADGBE.",
    "difficulty": "easy"
  },
  {
    "subject": "Chemistry",
    "question": "What is the chemical symbol for Gold?",
    "choices": ["Go", "Gd", "Au", "Ag"],
    "answer": "Au",
    "hint": "From the Latin name Aurum.",
    "difficulty": "easy"
  },
  {
    "subject": "Biology",
    "question": "What is the powerhouse of the cell?",
    "choices": ["Nucleus", "Ribosome", "Mitochondria", "Chloroplast"],
    "answer": "Mitochondria",
    "hint": "It produces energy.",
    "difficulty": "easy"
  },
  {
    "subject": "History",
    "question": "In what year did the Titanic sink?",
    "choices": ["1910", "1912", "1915", "1920"],
    "answer": "1912",
    "hint": "Early 1900s.",
    "difficulty": "medium"
  },
  {
    "subject": "Geography",
    "question": "What is the smallest country in the world?",
    "choices": ["Monaco", "Vatican City", "San Marino", "Liechtenstein"],
    "answer": "Vatican City",
    "hint": "It's in Rome.",
    "difficulty": "easy"
  },
  {
    "subject": "Literature",
    "question": "Who wrote 'To Kill a Mockingbird'?",
    "choices": ["Harper Lee", "F. Scott Fitzgerald", "Ernest Hemingway", "John Steinbeck"],
    "answer": "Harper Lee",
    "hint": "American author from the South.",
    "difficulty": "easy"
  },
  {
    "subject": "Advanced Math",
    "question": "Boss Challenge: Solve for x: 3x² - 12x + 9 = 0",
    "choices": ["x = 1 or x = 3", "x = 2 or x = 2", "x = 1 or x = 1", "x = 0 or x = 3"],
    "answer": "x = 1 or x = 3",
    "hint": "Factor out 3 first, then use the quadratic formula or factoring.",
    "difficulty": "boss"
  },
  {
    "subject": "Logic Puzzle",
    "question": "Boss Challenge: If all roses are flowers, and some flowers fade quickly, what can we conclude?",
    "choices": ["All roses fade quickly", "Some roses fade quickly", "No roses fade quickly", "Roses never fade"],
    "answer": "Some roses fade quickly",
    "hint": "Use logical reasoning: if only SOME flowers fade, roses might be among them.",
    "difficulty": "boss"
  },
  {
    "subject": "Astronomy",
    "question": "Boss Challenge: Which planet is known as the 'Red Planet'?",
    "choices": ["Venus", "Mars", "Mercury", "Jupiter"],
    "answer": "Mars",
    "hint": "Its surface has iron oxide (rust).",
    "difficulty": "boss"
  },
  {
    "subject": "Chemistry",
    "question": "Boss Challenge: What is the atomic number of Carbon?",
    "choices": ["4", "6", "8", "12"],
    "answer": "6",
    "hint": "It has 6 protons.",
    "difficulty": "boss"
  },
  {
    "subject": "World Capitals",
    "question": "Boss Challenge: What is the capital of Australia?",
    "choices": ["Sydney", "Melbourne", "Canberra", "Brisbane"],
    "answer": "Canberra",
    "hint": "It's purpose-built and located inland.",
    "difficulty": "boss"
  },
  {
    "subject": "Literature",
    "question": "Boss Challenge: In '1984' by George Orwell, what is the totalitarian government called?",
    "choices": ["The Ministry", "The Party", "Big Brother", "The State"],
    "answer": "The Party",
    "hint": "It's the controlling political organization.",
    "difficulty": "boss"
  },
  {
    "subject": "Calculus",
    "question": "Boss Challenge: What is the derivative of x³ + 2x² - 5x + 7?",
    "choices": ["3x² + 4x - 5", "3x² + 4x + 5", "x² + 4x - 5", "3x + 4"],
    "answer": "3x² + 4x - 5",
    "hint": "Apply power rule to each term.",
    "difficulty": "boss"
  },
  {
    "subject": "Philosophy",
    "question": "Boss Challenge: Who proposed 'Cogito, ergo sum' (I think, therefore I am)?",
    "choices": ["Plato", "Aristotle", "René Descartes", "Immanuel Kant"],
    "answer": "René Descartes",
    "hint": "A French philosopher from the 17th century.",
    "difficulty": "boss"
  },
  {
    "subject": "Genetics",
    "question": "Boss Challenge: What percentage of human DNA do we share with chimpanzees?",
    "choices": ["78%", "85%", "95%", "99%"],
    "answer": "95%",
    "hint": "It's surprisingly high but not quite complete overlap.",
    "difficulty": "boss"
  },
  {
    "subject": "Advanced Biology",
    "question": "Boss Challenge: What is the process by which plants convert sunlight into chemical energy?",
    "choices": ["Respiration", "Photosynthesis", "Fermentation", "Decomposition"],
    "answer": "Photosynthesis",
    "hint": "Uses light energy.",
    "difficulty": "boss"
  },
  {
    "subject": "Economics",
    "question": "Boss Challenge: What economic term describes a general increase in prices and fall in purchasing value?",
    "choices": ["Deflation", "Inflation", "Stagflation", "Recession"],
    "answer": "Inflation",
    "hint": "Money becomes worth less.",
    "difficulty": "boss"
  },
  {
    "subject": "  Mythology",
    "question": "Boss Challenge: In Greek mythology, who is the king of the gods?",
    "choices": ["Poseidon", "Hades", "Zeus", "Apollo"],
    "answer": "Zeus",
    "hint": "Rules from Mount Olympus.",
    "difficulty": "boss"
  },
  {
    "subject": "  Advanced Chemistry",
    "question": "Boss Challenge: What is the pH of a neutral solution?",
    "choices": ["5", "6", "7", "8"],
    "answer": "7",
    "hint": "Neither acidic nor basic.",
    "difficulty": "boss"
  }
]

# ---------- ASCII Cats ----------
CORRECT_CATS = [
r"""
 /\_/\  
( ^.^ )  Purr-fect! Correct!
 > ^ <
""",
r"""
 /\_/\  
( =^.^=)  Right on! 🐾
 > ^ <
""",
r"""
 /\_/\  
( ^_~ )  Nice! You got it!
 > ^ <
"""
]

WRONG_CATS = [
r"""
 /\_/\  
( o.o )  Wrong! Try again!
 > ^ <
""",
r"""
 /\_/\  
( =O.O= )  Oops! Incorrect!
 > ^ <
""",
r"""
 /\_/\  
( >.< )  That’s not right! 😿
 > ^ <
"""
]

NIP_CATS = [
r"""
 /\_/\  
( >.< )  You used Catnip! +1 life
 > ^ <
""",
r"""
 /\_/\  
( ^o^ )  Catnip activated! Extra life!
 > ^ <
"""
]

DEAD_CAT = r"""
 /\_/\  
( X_X )  Your cat braincell is gone... 🪦
 > ^ <
"""

HINT_CATS = [
r"""
 /\_/\  
( o.o )  Whisker Hint activated!
 > ^ <
""",
r"""
 /\_/\  
( -.- )  Hmm… here’s a clue…
 > ^ <
"""
]

# ---------- Utilities ----------
def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def pause(msg="Press Enter to continue..."):
    input(msg)

def save_players(data):
    try:
        with open(SAVE_FILE, "w", encoding="utf-8") as f:
            json.dump(data, f, indent=2)
    except Exception as e:
        print("Could not save players:", e)

def load_players():
    if os.path.exists(SAVE_FILE):
        try:
            with open(SAVE_FILE, "r", encoding="utf-8") as f:
                return json.load(f)
        except Exception:
            return {}
    return {}

def banner():
    print(r"""
  /\_/\   
 ( o.o )  🐾 The Last Meowcell 🐾
  > ^ <   Meow or never — can you save your last meowcell?
""")

def cat_hearts(lives):
    return " ".join(["🧠"] * lives) if lives > 0 else "💀"

# ---------- Question Bank ----------
class QuestionBank:
  def __init__(self, questions=None):
    self.questions = questions or SAMPLE_QUESTIONS.copy()
    # Ensure each question has a difficulty field.
    # If the question text contains 'boss challenge' we mark it as hard, otherwise default to easy.
    for q in self.questions:
      if "difficulty" not in q:
        qt = str(q.get("question", "")).lower()
        if "boss challenge" in qt:
          q["difficulty"] = "hard"
        else:
          q["difficulty"] = "easy"

  def load_from_file(self, path):
    if not os.path.exists(path):
      return False
    with open(path, "r", encoding="utf-8") as f:
      self.questions = json.load(f)
    return True

  def topics(self):
    return sorted(set(q["subject"] for q in self.questions))

  def get_random(self, subject=None, difficulty=None):
    # By default (difficulty is None) exclude explicit boss questions so they only
    # appear when requested (e.g., every 10th survival round).
    if difficulty is None:
      pool = [q for q in self.questions if (subject is None or q["subject"].lower() == subject.lower()) and str(q.get("difficulty", "")).lower() != "boss"]
    else:
      d = str(difficulty).lower()
      if d == "mixed":
        # mixed: include non-boss questions only by default
        pool = [q for q in self.questions if (subject is None or q["subject"].lower() == subject.lower()) and str(q.get("difficulty", "")).lower() != "boss"]
      elif d == "boss":
        pool = [q for q in self.questions if (subject is None or q["subject"].lower() == subject.lower()) and str(q.get("difficulty", "")).lower() == "boss"]
      else:
        pool = [q for q in self.questions if (subject is None or q["subject"].lower() == subject.lower()) and str(q.get("difficulty", "")).lower() == d]
    return random.choice(pool) if pool else None

  

# ---------- Player ----------
class Player:
    def __init__(self, name):
        self.name = name
        self.lives = 3
        self.score = 0
        self.catnip = 0
        self.achievements = []

    def to_dict(self):
        return {"name": self.name, "lives": self.lives, "score": self.score, "catnip": self.catnip, "achievements": self.achievements}

    @staticmethod
    def from_dict(d):
        p = Player(d.get("name","Player"))
        p.lives = d.get("lives",3)
        p.score = d.get("score",0)
        p.catnip = d.get("catnip",0)
        p.achievements = d.get("achievements",[])
        return p

# ---------- Game ----------
class TheMeowGames:
  def __init__(self):
    # Always use the embedded sample questions; do not load external files
    self.bank = QuestionBank(SAMPLE_QUESTIONS.copy())
    self.players_db = load_players()
    self.current_player = None

  def main_menu(self):
    while True:
      clear()
      banner()
      print("Main Menu:")
      print("1) Survival Mode - How long your meowcell last?")
      print("2) Quiz Mode - Prove your knowledge in 10 rounds")
      print("3) Save & Exit The Meow Games")
      choice = input("Choose your challenge: ").strip()
      if choice == "1":
        self.play_survival()
      elif choice == "2":
        self.play_quiz(10)
      elif choice == "3":
        self.exit_game()
      else:
        print("Meow? That's not valid. Try again.")
        pause()

  def select_or_create_player(self):
    clear()
    print("Who's playing? (enter new name to create)")
    if self.players_db:
      print("Saved players:")
      for idx, name in enumerate(sorted(self.players_db.keys()),1):
        score = self.players_db[name].get("score", 0)
        # Right-align score with padding
        print(f"{idx}) {name:<30} Score: {score:>6}")
    name = input("Player name: ").strip()
    if not name:
      name = "CatPlayer"
    if name in self.players_db:
      player = Player.from_dict(self.players_db[name])
    else:
      player = Player(name)
      self.players_db[name] = player.to_dict()
      save_players(self.players_db)
    self.current_player = player
    return player

  def ask_question(self, q):
    while True:
      clear()
      banner()
      print(f"Subject: {q['subject']}    Player: {self.current_player.name}    Lives: {cat_hearts(self.current_player.lives)}    Catnip: {self.current_player.catnip}")
      print("-"*60)
      print("Q:", q["question"])
      for i, c in enumerate(q.get("choices", []), 1):
        print(f"  {i}) {c}")
      print("\nType 'hint' for Whisker Hint (-1 score), 'nip' to use catnip (+1 life).")

      answer = input("Answer (number or exact text): ").strip()

      # Handle hint or catnip
      if answer.lower() == "hint":
        print(random.choice(HINT_CATS))
        print("Whisker Hint:", q.get("hint", "No hint available."))
        self.current_player.score = max(0, self.current_player.score - 1)
        pause()
        continue
      if answer.lower() == "nip":
        if self.current_player.catnip > 0:
          self.current_player.catnip -= 1
          self.current_player.lives += 1
          print(random.choice(NIP_CATS))
          pause()
        else:
          print("No Catnip! Keep playing.")
          pause()
        continue

      # Validate numeric input
      if answer.isdigit():
        idx = int(answer) - 1
        if 0 <= idx < len(q.get("choices", [])):
          chosen = q["choices"][idx]
        else:
          print("Invalid number. Try again.")
          pause()
          continue
      # Validate text input
      elif answer in q.get("choices", []):
        chosen = answer
      else:
        print("Invalid input. Enter the number or exact choice text.")
        pause()
        continue

      # Check correctness
      correct = str(chosen).strip().lower() == str(q["answer"]).strip().lower()
      if correct:
        self.current_player.score += 10
        print(random.choice(CORRECT_CATS))
      else:
        self.current_player.lives -= 1
        if self.current_player.lives > 0:
          print(random.choice(WRONG_CATS))
          print("Correct answer was:", q["answer"])
        else:
          print(DEAD_CAT)
      pause()
      return correct

  def play_survival(self):
    player = self.select_or_create_player()
    pause("Survival Mode: Keep answering correct questions. Press Enter to start...")
    question_count = 0
    while player.lives > 0:
      question_count += 1
      # Every 10th question is a boss (hard) round
      if question_count % 10 == 0:
        # Prefer explicit boss questions on boss rounds; fall back to hard then mixed
        q = self.bank.get_random(difficulty="boss")
        if q is None:
          q = self.bank.get_random(difficulty="hard")
        if q is None:
          q = self.bank.get_random()
      else:
        q = self.bank.get_random()
      if q is None:
        break
      self.ask_question(q)
    print("Returning to main menu...")
    self.players_db[player.name] = player.to_dict()
    save_players(self.players_db)
    pause()

  def play_quiz(self, count=10):
    player = self.select_or_create_player()
    # Ask player for desired difficulty
    diff_choice = None
    while diff_choice is None:
      clear()
      print("Choose difficulty for Quiz Mode:")
      print("1) Easy")
      print("2) Medium")
      print("3) Hard")
      print("4) Mixed")
      dc = input("Select (1-4): ").strip()
      mapping = {"1": "easy", "2": "medium", "3": "hard", "4": "mixed"}
      if dc in mapping:
        diff_choice = mapping[dc]
      else:
        print("Invalid selection. Try again.")
        pause()
    pause(f"Quiz Mode: {count} questions ({diff_choice}). Press Enter to start...")
    asked = set()
    for _ in range(count):
      if player.lives <= 0:
        break
      q = self.bank.get_random(difficulty=diff_choice)
      tries = 0
      while q and json.dumps(q) in asked and tries < 10:
        q = self.bank.get_random(difficulty=diff_choice)
        tries += 1
      if q is None:
        break
      asked.add(json.dumps(q))
      self.ask_question(q)
    print(f"Quiz finished. Score: {player.score}")
    self.players_db[player.name] = player.to_dict()
    save_players(self.players_db)
    pause()

  def exit_game(self):
    save_players(self.players_db)
    print("Bye! May your braincells stay nimble. =^._.^=")
    sys.exit(0)

# ---------- Main ----------
def main():
    game = TheMeowGames()
    try:
        game.main_menu()
    except KeyboardInterrupt:
        print("\nCat naps happen. Exiting.")
        save_players(game.players_db)

if __name__ == "__main__":
    main()

