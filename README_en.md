# ThinAppCopyFileSample

## Overview

When copying a file virtualized by ThinApp using ::CopyFile of C++ in the following environment,there is an issue that the destination file for the copy is corrupted.

This is a sample repository to reproduce this issue.

* Windows 11 22H2
* Windows 10 21H2 installed update KB5025221
  * https://support.microsoft.com/en-us/topic/april-11-2023-kb5025221-os-builds-19042-2846-19044-2846-and-19045-2846-b00c3356-baac-4a41-8342-7f97ec83445a

## How to reproduce 

### Environment

* OS: Windows11 22H2
* ThinApp version: ThinApp 2212
* Build environment: Visual Studio 2019

### Steps

* Prepare the above environment
* Build CopyFileSampleN with Release/x64
* Move the built `CopyFileSampleN\x64\CopyFileSampleN.exe` to `C:\CopyFileSample`
  * For simplicity, pre-built CopyFileSampleN.exe is registered in version control. you can use them.
* Execute `Project\build.bat`
* Execute created `Project\bin\CopyFileSample.exe`
* Check created `%LOCALAPPDATA%\Thinstall\CopyFileSample\%drive_C%\CopyFileSample\testfile_copied.txt`

stfile_copied.txt is currupted.

### Details of Steps

CopyFileSample.exe is a program that just copies `C:\CopyFileSample\testfile.txt` to `C:\CopyFileSample\testfile_copied.txt`.

```
int main()
{
    ::CopyFile(_T("C:\\CopyFileSample\\testfile.txt"), _T("C:\\CopyFileSample\\testfile_copied.txt"), false);
}
```

The source file of `C:\CopyFileSample\testfile.txt` seen from CopyFileSample.exe is `Project\%drive_C%\CopyFileSample\testfile.txt`, and the following text is described.

```
This is a test target file of `CopyFile`.
```

The entity of `testfile.txt` that CopyFileSample.exe is actually looking for is invisible because it is virtualized by ThinApp.
Since it is virtualized, CopyFileSample.exe actually copies the file to `%LOCALAPPDATA%\Thinstall\CopyFileSample\%drive_C%\CopyFileSample\testfile_copied.txt` instead of `C:\CopyFileSample\testfile_copied.txt`.
