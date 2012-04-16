#include "osinterop.h"
#include "resource.h"
#ifdef Q_OS_WIN
#include <windows.h>

#define UNIQUE_WINDOW_TITLE "OpenTuring-3F2AF4E0-4F89-11D3-9A0C-0305E82C3301::EventReceiver"

// A bunch of code is borrowed from the ready to program editor that was used by turing

namespace OSInterop {
//! creates a registry key
static bool MyCreateRegEntry (const char *pmKeyName, const char *pmKeyValue)
{
    HKEY	myKeyHandle;
    DWORD	myDisposition;
    int		myResult;

    //
    // Create key
    //
    myResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, pmKeyName, 0, "",
                               REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                               NULL, &myKeyHandle, &myDisposition);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    //
    // If there's a value, set it.
    //
    if (pmKeyValue != NULL)
    {
        myResult = RegSetValueEx (myKeyHandle, NULL, 0, REG_SZ,
                                  (const BYTE*)pmKeyValue, strlen (pmKeyValue));
        if (myResult != ERROR_SUCCESS)
        {
            return false;
        }
    }

    //
    // Close key
    //
    myResult = RegCloseKey (myKeyHandle);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
} // MyCreateRegEntry

static bool MyClearTree (const char *pmKeyName)
{
    LONG 	myResult;
    HKEY	myKeyHandle;
    char	mySubKey [1024];
    char	myNewKey [1024];
    DWORD	mySubKeyLength;

    if ((pmKeyName == NULL) || (pmKeyName [0] == 0))
    {
        return false;
    }

    // Open the key
    myResult = RegOpenKeyEx (HKEY_CLASSES_ROOT, pmKeyName, 0,
                             KEY_ENUMERATE_SUB_KEYS | DELETE, &myKeyHandle);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    while (true)
    {
        mySubKeyLength = 1024;
        myResult = RegEnumKeyEx (myKeyHandle, 0, mySubKey, &mySubKeyLength,
                                 NULL, NULL, NULL, NULL);
        // No more keys.  Delete the top item.
        if (myResult == ERROR_NO_MORE_ITEMS)
        {
            myResult = RegDeleteKey (HKEY_CLASSES_ROOT, pmKeyName);
            if (myResult != ERROR_SUCCESS)
            {
                return false;
            }
            break;
        }

        // Check for other errors wrt to enumeration
        if (myResult != ERROR_SUCCESS)
        {
            return false;
        }

        // Recursively delete subkeys
        wsprintf (myNewKey, "%s\\%s", pmKeyName, mySubKey);
        if (!MyClearTree (myNewKey))
        {
            return false;
        }
    } // while (true)

    myResult = RegCloseKey (myKeyHandle);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
} // MyClearTree

static bool	MyCreateAssocEntry (const char *pmAssocName,
                        const char *pmFileSuffix, const char *pmFileDescription,
                        int pmIconNumber, const char *pmCommandName)
{
    HKEY	myKeyHandle;
    char	myKeyName [1024];
    char	myApplicationPath[1024];
    char	myIconNumber [256];
    int		myResult;

    //
    // Clear the previous tree
    //
    MyClearTree (pmAssocName);

    //
    // File type description I.E "Turing File"
    //
    if (!MyCreateRegEntry (pmAssocName, pmFileDescription))
    {
        return false;
    }

    //
    // Create Ready.java\DefaultIcon and set to "[..]\apps\Ready\Ready.exe,-6"
    //
    wsprintf (myKeyName, "%s\\DefaultIcon", pmAssocName);
    GetModuleFileName (NULL, myApplicationPath, 1024);
    wsprintf (myIconNumber, ",-%d", pmIconNumber);
    strcat (myApplicationPath, myIconNumber);
    if (!MyCreateRegEntry (myKeyName, myApplicationPath))
    {
        return false;
    }

    //
    // Create Ready.java\shell
    //
    wsprintf (myKeyName, "%s\\shell", pmAssocName);
    if (!MyCreateRegEntry (myKeyName, NULL))
    {
        return false;
    }

    //
    // Create Ready.java\shell\open and set to "&Open with Ready to Program"
    //
    wsprintf (myKeyName, "%s\\shell\\open", pmAssocName);
    if (!MyCreateRegEntry (myKeyName, pmCommandName))
    {
        return false;
    }

    //
    // Was: Create Ready.java\shell\open\command and set to ""[..]\apps\Ready\Ready.exe" "%1""
    // Now: Create Ready.java\shell\open\command and set to ""[..]\apps\Ready\Ready.exe" -nowindow"
    //
    wsprintf (myKeyName, "%s\\shell\\open\\command", pmAssocName);
    myApplicationPath [0] = '"';
    GetModuleFileName (NULL, &myApplicationPath [1], 1024);
    strcat (myApplicationPath, "\" \"%1\"");
    if (!MyCreateRegEntry (myKeyName, myApplicationPath))
    {
        return false;
    }

    //
    // Add in some extra values for the main key
    //
    // Open key
    //
    myResult = RegOpenKeyEx (HKEY_CLASSES_ROOT, pmAssocName, 0, KEY_ALL_ACCESS,
                             &myKeyHandle);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    //
    // Write always display extension
    //
    myResult = RegSetValueEx (myKeyHandle, "AlwaysShowExt", 0, REG_SZ, (const BYTE*)"", 0);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    //
    // Close key
    //
    myResult = RegCloseKey (myKeyHandle);
    if (myResult != ERROR_SUCCESS)
    {
        return false;
    }

    //
    // Create link from file suffix (Set .t to Turing.t)
    //
    if (!MyCreateRegEntry (pmFileSuffix, pmAssocName))
    {
        return false;
    }

    return true;
} // MyCreateAssocEntry

bool associateTuringFiles() {
    if (!MyCreateAssocEntry ("OpenTuring.t", ".t",
                             "Turing Program", IDI_TURINGFILE,
                             "&Open with Open Turing"))
    {
        return false;
    }
    if (!MyCreateAssocEntry ("OpenTuring.tu", ".tu",
                             "Turing Unit", IDI_TURINGFILE,
                             "&Open with Open Turing"))
    {
        return false;
    }
}


} // end namespace
#endif // Q_OS_WIN
