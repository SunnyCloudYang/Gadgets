/**
* @author : GoodNullName
* @note : input your words, choose the format,
    and copy the output to where supports md &LaTeX
* @version : 1.0.0 add a forbidden char '~', fixed some bugs
             1.2.0 supported char '^' and '~', supported auto-linefeed
             1.5.0 supported autocopy to clipboard
             1.5.1 optimized color display for short string, add "k"
             1.5.5 optimized color display for short string, adjust "k"
             1.5.6 keep rainbowing text until press Enter
*/
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

const string VERSION = "version 1.5.6";
const string PREFIX = "\\color{";
const string JOINT = "}{";
const string postfix[2] = {"}", "}}"};
const string math_pref[2] = {"", "\\mathrm{"};
vector<string> colors = {"#ff0000", "#f42700", "#e94f00", "#dd7700",
                         "#d29f00", "#b6b800", "#88c400", "#5bcf00",
                         "#2ddb00", "#00e600", "#00db2d", "#00cf5b",
                         "#00c488", "#00b8b6", "#009fd2", "#0077dd",
                         "#004fe9", "#0027f4", "#0000ff", "#3300fa",
                         "#6600f4", "#9900ee", "#cc00e9", "#e900cc",
                         "#ee0099", "#f40066", "#fa0033"};
vector<char> esc_char = {' ', '\\', '{', '}', '#', '$', '%', '&', '_'};
const char ctrl_char[2] = {'^', '~'};
const int LINE_SIZE = 29;

string RainbowText(string origin_text, bool mathrm);
void AddToCpy(string str);

int main()
{
    string origin_text;
    string rainbow_text;
    string cmathrm;
    int mathrm = 1;
    cout << VERSION << endl;
    cout << "Your text: ";
    getline(cin, origin_text);
    while (origin_text.length() != 0)
    {
        cout << "Enable mathrm?(y/n): ";
        getline(cin, cmathrm);

        if (cmathrm == "n" || cmathrm == "N")
        {
            mathrm = 0;
        }

        rainbow_text = RainbowText(origin_text, mathrm);
        cout << "----------Rainbow text code begin----------" << endl;
        cout << rainbow_text << endl;
        cout << "-----------Rainbow text code end-----------" << endl;
        AddToCpy(rainbow_text);
        cin.get();
        cout << "\nYour text(Enter to exit): ";
        getline(cin, origin_text);
    }
    return 0;
}

string RainbowText(string origin_text, bool mathrm)
{
    const int STRLEN = origin_text.length();
    string rainbow_text = "$";

    float k = 1.0;
    if (STRLEN < colors.size())
    {
        k = 16 * pow(STRLEN, -0.866);
    }

    if (STRLEN > LINE_SIZE)
    {
        rainbow_text += "\\begin{aligned}\n&";    
    }

    for (int i = 0; i < STRLEN; i++)
    {
        if (!(i % LINE_SIZE) && i != 0)
        {
            rainbow_text += "\\\\&";
        }

        rainbow_text += PREFIX + colors[int(k * i + 0.5) % colors.size()] +
                        JOINT + math_pref[mathrm];

        if (origin_text[i] == ctrl_char[0])
        {
            rainbow_text += "\\wedge";
        }
        else if (origin_text[i] == ctrl_char[1])
        {
            rainbow_text += "\\sim";
        }
        else
        {
            auto Finder = [origin_text, i](char c) -> bool
            { return origin_text[i] == c; };
            if (any_of(esc_char.begin(), esc_char.end(), Finder))
            {
                rainbow_text += "\\";
            }
            rainbow_text += origin_text[i];
        }
        rainbow_text += postfix[mathrm] + "\n";
    }
    if (STRLEN > LINE_SIZE)
    {
        rainbow_text += "\\end{aligned}\n";
    }
    rainbow_text[rainbow_text.length() - 1] = '$';
    return rainbow_text;
}

void AddToCpy(string str)
{
    HGLOBAL hClip;
    if (OpenClipboard(NULL))
    {
        EmptyClipboard(); // relax, it won't clear all, just current content
        hClip = GlobalAlloc(GMEM_MOVEABLE, str.length() + 1);
        char *buff = (char *)GlobalLock(hClip);
        strcpy(buff, str.c_str());
        GlobalUnlock(hClip);
        SetClipboardData(CF_TEXT, hClip);
        CloseClipboard();
        cout << "Already copied to the clipboard.";
    }
    else
    {
        cout << "Failed to open clipboard, please copy it manually.";
    }
}