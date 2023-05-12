#include <windows.h>
#include <tchar.h>

int main()
{
    ::CopyFile(_T("C:\\CopyFileSample\\testfile.txt"), _T("C:\\CopyFileSample\\testfile_copied.txt"), false);
}
