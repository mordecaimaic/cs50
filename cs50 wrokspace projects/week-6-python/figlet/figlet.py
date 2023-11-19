import sys
import random
from pyfiglet import Figlet

figlet = Figlet()
# Get all the available font in "Figlet"
font_available = figlet.getFonts()


if len(sys.argv)!= 1 and len(sys.argv) != 3:
    print("Invalid usage")
    sys.exit(1)
if len(sys.argv) == 3:
    if sys.argv[1] == "-f" or sys.argv[1] == "-font":
        font_input = sys.argv[2]
        if font_input not in font_available:
            print("Invalid usage")
            sys.exit(1)
        else:
            figlet.setFont(font= font_input)
    else:
        printf("Invalid usage")
        sys.exit(1)
else:
    rand_index = random.randint(0, len(font_available))
    figlet.setFont(font= font_available[rand_index])

text_input = input("Input: ")

print(figlet.renderText(text_input))

