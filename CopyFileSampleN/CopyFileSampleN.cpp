// CopyFileSampleN.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <tchar.h>

int main()
{
    ::CopyFile(_T("C:\\CopyFileSample\\testfile.txt"), _T("C:\\CopyFileSample\\testfile_copied.txt"), false);
}
