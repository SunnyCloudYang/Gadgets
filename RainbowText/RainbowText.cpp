/**
* @author : GoodNullName
* @note : input your words, choose the format,
    and paste the output to where supports markdown&LaTeX
* @version : 1.0.0 add a forbidden char '~', fixed some bugs
             1.2.0 supported char '^' and '~', supported auto-linefeed
             1.5.0 supported autocopy to clipboard
             1.5.1 optimized color display for short string, add "k"
             1.5.5 optimized color display for short string, adjust "k"
             1.5.6 keep rainbowing text until press Enter
             1.6.0 support Chinese characters(inavailable with g++)
             1.6.1 catch err when zn-CN.936 is not supported
             1.6.2 cancel copy confirm
             1.6.3 optimized finder for escape chars
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <windows.h>
using namespace std;

const string VERSION = "version 1.6.3";
const wstring PREFIX = L"\\color{";
const wstring JOINT = L"}{";
const wstring postfix[2] = {L"}", L"}}"};
const wstring math_pref[2] = {L"", L"\\mathrm{"};
vector<wstring> colors = {L"#ff0000", L"#f42700", L"#e94f00", L"#dd7700",
                          L"#d29f00", L"#b6b800", L"#88c400", L"#5bcf00",
                          L"#2ddb00", L"#00e600", L"#00db2d", L"#00cf5b",
                          L"#00c488", L"#00b8b6", L"#009fd2", L"#0077dd",
                          L"#004fe9", L"#0027f4", L"#0000ff", L"#3300fa",
                          L"#6600f4", L"#9900ee", L"#cc00e9", L"#e900cc",
                          L"#ee0099", L"#f40066", L"#fa0033"};
map<wchar_t, wstring> esc_char = {
    {' ', L"\\ "}, {'\\', L"\\\\"}, {'{', L"\\{"}, {'}', L"\\}"},
    {'#', L"\\#"}, {'$', L"\\$"}, {'%', L"\\%"}, {'&', L"\\&"}, 
    {'_', L"\\_"}, {'^', L"\\wedge"}, {'~', L"\\sim"}};
const int LINE_SIZE = 29;
int ncolors = colors.size();

wstring RainbowText(wstring origin_text, bool mathrm);
string AddToCpy(wstring str);

int main()
{
    cout << VERSION << endl;

    try
    {
        locale loc(".936");
        wcin.imbue(loc);
        wcout.imbue(loc);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << "\n\n";
        std::cout << "Sorry, seems that Chinese is not supported by this compiler."<< "\n\n";
    }

    wstring origin_text;
    wstring rainbow_text;
    string cmathrm;
    int mathrm = 1;
    cout << "Your text: ";
    getline(wcin, origin_text);
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
        wcout << rainbow_text << endl;
        cout << "-----------Rainbow text code end-----------" << endl;
        cout << AddToCpy(rainbow_text) << endl;
        cout << "\nYour text(Enter to exit): ";
        getline(wcin, origin_text);
    }
    return 0;
}

wstring RainbowText(wstring origin_text, bool mathrm)
{
    const int STRLEN = origin_text.length();
    wstring rainbow_text = L"$";

    float k = (STRLEN < colors.size() ? 16 * pow(STRLEN, -0.866) : 1);

    if (STRLEN > LINE_SIZE)
    {
        rainbow_text += L"\\begin{aligned}\n&";
    }

    for (int i = 0; i < STRLEN; i++)
    {
        if (!(i % LINE_SIZE) && i != 0)
        {
            rainbow_text += L"\\\\&";
        }

        rainbow_text += PREFIX
                      + colors[(ncolors + int(k * i + 0.5) % ncolors) % ncolors]
                      + JOINT
                      + math_pref[mathrm];

        if (esc_char.find(origin_text[i]) != esc_char.end())
        {
            rainbow_text += esc_char[origin_text[i]];
        }
        else
            rainbow_text += origin_text[i];

        rainbow_text += postfix[mathrm] + L"\n";
    }

    if (STRLEN > LINE_SIZE)
    {
        rainbow_text += L"\\end{aligned}\n";
    }
    rainbow_text[rainbow_text.length() - 1] = L'$';
    return rainbow_text;
}

string AddToCpy(wstring str)
{
    HGLOBAL hClip;
    if (OpenClipboard(NULL))
    {
        EmptyClipboard(); // relax, it won't clear all, just current content
        hClip = GlobalAlloc(GMEM_MOVEABLE, (str.length() + 1) * sizeof(wchar_t));
        wchar_t* buff = (wchar_t *)GlobalLock(hClip);
        wcscpy(buff, str.c_str());
        GlobalUnlock(hClip);
        SetClipboardData(CF_UNICODETEXT, hClip);
        CloseClipboard();
        return "Already copied to the clipboard.";
    }
    else
    {
        return "Failed to open clipboard, please copy it manually.";
    }
}