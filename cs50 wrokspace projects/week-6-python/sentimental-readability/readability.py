# TODO
text = input("Text: ")
text_copy = ""
letter_counts = 0
sentence_counts = 0

for i in range(len(text)):
    if text[i].isalpha() or text[i] == " ":
        text_copy += text[i]
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentence_counts += 1


words = text_copy.split()
word_counts = len(words)
letter_counts = 0

for word in words:
    for letter in word:
        letter_counts += 1

# print(f"{letter_counts} letters")
# print(f"{word_counts} words")
# print(f"{sentence_counts} sentences")

L = 100 * letter_counts / word_counts
S = 100 * sentence_counts / word_counts

index = int(round(0.0588 * L - 0.296 * S - 15.8))

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade:{index}")
