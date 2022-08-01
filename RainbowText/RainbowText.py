# @author: GoodNullName
# @note: input your words, choose the format,
#        and copy the output to where supports md&LaTeX
# @version: 1.2.0 add a forbidden char '~', fixed some bugs
#           1.3.0 remove forbid_char, support '^' and '~'
#           1.3.5 some small modifications
#           1.3.6 automatically copy to clipboard
#           1.3.7 optimized color display for short string
#           1.4.0 support auto linefeed, left-aligned
import os
import pyperclip

# global str variable
YourRainbowText = ""
version = "version 1.4.0"

class RainbowText:

    __prefix = "\\color{"
    __joint = "}{"
    __postfix = ("}", "}}")
    __mathpref = ("", "\\mathrm{")
    __rainbowColors = ("#ff0000", "#f42700", "#e94f00", "#dd7700",
                       "#d29f00", "#b6b800", "#88c400", "#5bcf00",
                       "#2ddb00", "#00e600", "#00db2d", "#00cf5b",
                       "#00c488", "#00b8b6", "#009fd2", "#0077dd",
                       "#004fe9", "#0027f4", "#0000ff", "#3300fa",
                       "#6600f4", "#9900ee", "#cc00e9", "#e900cc",
                       "#ee0099", "#f40066", "#fa0033")
    __esc = {" ": "\\ ", "\\": "\\\\", "{": "\\{",
             "}": "\\}", "#": "\\#", "$": "\\$",
             "%": "\\%", "&": "\\&", "_": "\\_",
             "^": "\\wedge", "~": "\\sim"}
    __origText = ""
    __rainbowText = ""

    def __init__(self, inputText) -> None:
        self.__origText = inputText

    def rainbow(self, mathrm=1) -> str:
        line_size = 29
        self.__rainbowText += "$"
        strlen = len(self.__origText)
        colors = len(self.__rainbowColors)
        k = 1
        if strlen < 9:
            k = 3
        if strlen > line_size:
            self.__rainbowText += "\\begin{align}\n&"

        for i in range(strlen):
            if (i % line_size == 0) & (i != 0):
                self.__rainbowText += "\\\\&"
                
            self.__rainbowText += (self.__prefix +
                                   self.__rainbowColors[k * i % colors] +
                                   self.__joint +
                                   self.__mathpref[mathrm])

            if self.__origText[i] in self.__esc:
                self.__rainbowText += self.__esc[self.__origText[i]]
            else:
                self.__rainbowText += self.__origText[i]
            self.__rainbowText += self.__postfix[mathrm] + "\n"

        else:
            if strlen > line_size:
                self.__rainbowText += "\\end{align}\n"
            self.__rainbowText = self.__rainbowText[:-1] + "$"

        return self.__rainbowText

print(version)
YourRainbowText = input("\nYour text to be rainbowed: ")
mathrm = int(input("Enable mathrm?(1/0): "))
print("\n--------Rainbow Text Code Begin--------")
print(RainbowText(YourRainbowText).rainbow(mathrm))
print("---------Rainbow Text Code End---------")
pyperclip.copy(RainbowText(YourRainbowText).rainbow(mathrm))
print("Already copied to clipboard.")
input()
