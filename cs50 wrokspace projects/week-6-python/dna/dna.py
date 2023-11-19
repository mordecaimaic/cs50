import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    # line = []
    with open(sys.argv[1]) as data_csv:
        temp_dict = csv.DictReader(data_csv)
        for i in temp_dict:
            database.append(i)
    attribute_list = list((database[0].keys()))

    # TODO: Read DNA sequence file into a variable
    dna_sequence = ""
    with open(sys.argv[2]) as sequence_file:
        dna_sequence = sequence_file.read()

    match_result = {}
    # TODO: Find longest match of each STR in DNA sequence
    for i in range(1, len(attribute_list)):
        # Iterate all the str given in csv file, and attempt to match in the sequences
        Str_Sequence = attribute_list[i]
        match_result[Str_Sequence] = dna_str_match(dna_sequence, Str_Sequence)

    # print(match_result)

    # TODO: Check database for matching profiles
    for person in database:
        for i in range(1, len(attribute_list)):
            Str_Sequence = attribute_list[i]
            # print(f"{person['name']}")
            # print(f"comparing {person['name']}'s {person[Str_Sequence]} and {match_result[Str_Sequence]}")
            if int(person[Str_Sequence]) != match_result[Str_Sequence]:
                break
            elif i == len(attribute_list) - 1:
                print(person["name"])
                return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# function "dna_str_match" implement the same function as "longest_match", I just try to write it by myself.
def dna_str_match(dna_sequence, str_subsequence):
    dna_length = len(dna_sequence)
    str_length = len(str_subsequence)
    largest_count = 0
    count = 0
    i = 0
    while i < (dna_length - str_length + 1):
        if dna_sequence[i : i + str_length] == str_subsequence:
            count += 1
            i += str_length
        else:
            largest_count = max(largest_count, count)
            count = 0
            i += 1
    return largest_count


main()
