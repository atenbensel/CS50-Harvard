from cs50 import get_string

def count_letters(text):
    letters = 0
    for char in text:
        if char in text:
            if char.isalpha():
                letters += 1
    return letters

def count_words(text):
    words = text.split()
    return len(words)

def count_sentences(text):
    sentences = 0
    for char in text:
        if char in ['.', '!', '?']:
            sentences += 1
    return sentences

def coleman_liau_index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    return index

def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    index = coleman_liau_index(letters, words, sentences)

    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")

if __name__ == "__main__":
    main()
