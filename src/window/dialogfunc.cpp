#ifdef _WIN32
    #include <Windows.h>
#endif

#include "common.hpp"
#include "window/dialogfunc.hpp"
#include "file/filefunc.hpp"
#include "util/mathfunc.hpp"
#include "util/stringfunc.hpp"


#ifndef _WIN32

bool detectEnvironment(string env)
{
    char buf[MAX_COMMAND];
    string command = "which " + env;
    bool found;
    FILE *f;

    f = popen(&command[0], "r");
    found = (fgets(buf, sizeof(buf), f) != NULL && !strchr(buf, ':'));
    pclose(f);
    
    return found;
}

int getEnvironment()
{
    if (detectEnvironment("kdialog"))
        return ENV_KDIALOG;
    
    if (detectEnvironment("osascript"))
        return ENV_APPLE;
    
    return -1;
}

#endif

EXPORT Base::List<string> Base::dialogOpenFile(string title, string location, List<string> filters, bool multiSelect)
{
    List<string> selFiles;
/*
#ifdef _WIN32 // Windows
	
    string filterString = "", defaultExt = stringSplit(filters[1], ";")[0];
    wchar_t buf[MAX_MULTIPLE * MAX_FILENAME];
    OPENFILENAMEW ofn;

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = 0;

    ofn.lpstrFile = buf;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(buf);

    // Generate filter string
    for (uint i = 0; i < filters.size(); i++)
        filterString += filters[i] + '\0';
    filterString += '\0';

    ofn.lpstrFilter = &filterString[0];
    ofn.nFilterIndex = 0;
    ofn.lpstrInitialDir = &location[0];
    ofn.lpstrTitle = &title[0];

    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    if (multiSelect)
        ofn.Flags |= OFN_ALLOWMULTISELECT;
    
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_FILENAME + MAX_EXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.lpstrDefExt = NULL;
    if (defaultExt != ".*")
        ofn.lpstrDefExt = &defaultExt[0];
    
    if (!GetOpenFileNameW(&ofn))
        return selFiles; // Cancel
    
    if (buf[wcslen(buf) + 1] == '\0') // Single file
        selFiles.push_back(buf);
    else
    {
        // Buffer starts with the directory, then each file (short) separated by 0. Last one ends with 00.
        string dir = buf;
        wchar_t *p = buf;
        do
        {
            p += wcslen(p) + 1;
            selFiles.push_back(dir + "\\" + p);
        }
        while (*(p + wcslen(p) + 1) != '\0');
    }

#else // Mac, Linux

    static int env = getEnvironment();
    char buf[MAX_MULTIPLE * MAX_FILENAME], *p;
    string command;
    FILE *f;

    switch (env)
    {
        case ENV_KDIALOG:
        {
            // https://techbase.kde.org/Development/Tutorials/Shell_Scripting_with_KDE_Dialogs#Example_28._--getopenfilename_dialog_box
            command = "kdialog --getopenfilename";

            if (!location.empty())
                command += stringToString(location);
            else
                command += " :";
            

            // Add filters
            if (filters.size())
            {
                command += " \"";

                for (int i = 1; i < filters.size(); i += 2)
                    command += stringReplace(stringToString(filters[i]), ";", " ") + " ";
                
                command += "|";
                for (int i = 0; i < filters.size(); i += 2)
                {
                    if (i > 0)
                        command += ", ";
                    command += stringEscapeQuotes(stringToString(filters[i]));
                }

                command += "\"";

            }

            if (multiSelect)
                command += " --multiple --separate-output";

            break;
        }

        case ENV_APPLE:
        {
            // https://developer.apple.com/library/mac/documentation/AppleScript/Conceptual/AppleScriptLangGuide/reference/ASLR_cmds.html#//apple_ref/doc/uid/TP40000983-CH216-SW4
            command = "osascript -e '";

            if (multiSelect) // Store results in a list
                command += "set fileList to ";
            else
                command += "POSIX path of (";
            
            command += "choose file";

            // Add filters
            if (filters.size())
            {
                int filterN = 0;

                command += " of type {";

                for (int i = 1; i < filters.size(); i += 2)
                {
                    List<string> filterList = stringSplit(filters[i], ";");
                    for (int j = 0; j < filterList.size(); j++)
                    {
                        if (filterN++ > 0)
                            command += ", ";
                        command += "\"" + stringReplace(stringToString(filterList[j]), "*", "public") + "\"";
                    }
                }

                command += "}";
            }

            if (!title.empty())
                command += " with prompt \"" + stringEscapeQuotes(stringToString(title)) + "\"";
            
            if (!location.empty())
                command += " default location \"" + stringToString(location) + "\"";
            
            if (multiSelect)
            {
                command += " multiple selections allowed true'";
                command += " -e 'set fileString to POSIX path of item 1 in fileList'";
                command += " -e 'repeat with i from 2 to the count of fileList'";
                command += " -e 'set fileString to fileString & \"\\n\"'";
                command += " -e 'set fileString to fileString & POSIX path of item i of fileList'";
                command += " -e 'end repeat'";
                command += " -e 'fileString'";
            }
            else
                command += ")'";

            break;
        }

        default:
            return selFiles; // Cancel
    }
    cout << command << endl;

    // Execute command
    if (!(f = popen(&command[0], "r")))
        return selFiles;

    // Read results (one line per file selected)
    buf[0] = '\0';
    p = buf;
    while (fgets(p, MAX_FILENAME, f) != NULL)
    {
        *(p + strlen(p) - 1) = '\0';
        selFiles.push_back(stringTostring(p));
        p += strlen(p);
    }

    pclose(f);

#endif
*/
    return selFiles;
}

EXPORT string Base::dialogSaveFile(string title, string location, List<string> filters)
{
    
    string selFile;
/*
#ifdef _WIN32

    string filterString = "", defaultExt = stringSplit(filters[1], ";")[0];
    wchar_t buf[MAX_FILENAME];
    OPENFILENAMEW ofn;

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = 0;

    ofn.lpstrFile = buf;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(buf);

    // Generate filter string
    for (uint i = 0; i < filters.size(); i++)
        filterString += filters[i] + '\0';
    filterString += '\0';

    ofn.lpstrFilter = &filterString[0];
    ofn.nFilterIndex = 0;
    ofn.lpstrInitialDir = &location[0];
    ofn.lpstrTitle = &title[0];

    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = MAX_FILENAME + MAX_EXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.lpstrDefExt = NULL;
    if (defaultExt != ".*")
        ofn.lpstrDefExt = &defaultExt[0];
    
    if (!GetSaveFileNameW(&ofn))
        return selFile; // Cancel
    
    selFile = buf;
    
#else

#endif
*/
    return selFile;
}