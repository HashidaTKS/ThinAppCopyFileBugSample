# ThinAppCopyFileSample

## 概要

以下の環境でThinAppで仮想化されたファイルをC++の::CopyFileでコピーすると、コピー後のファイルが破損する問題が発生している。
この問題を再現させるためのサンプルリポジトリ。

* Windows 11 22H2
* Windows 10 21H2 の 更新プログラム KB5025221 適用後

## 再現方法

### 環境

* OS: Windows11 22H2
* ThinApp version: ThinApp 2212
* テストプログラムのビルド環境: Visual Studio 2019

### 手順

* 上記の環境を用意する。
* CopyFileSampleNをRelease/x64でビルドする
* ビルドして出来た`CopyFileSampleN\x64\CopyFileSampleN.exe`を`C:\CopyFileSample`に配置する
  * 簡単のため、予めビルドしたCopyFileSampleN.exeをバージョン管理に登録済み。そちらを使って良い。
* `Project\build.bat`を実行する
* `Project\bin\CopyFileSample.exe`ができるので実行する
* `%LOCALAPPDATA%\Thinstall\CopyFileSample\%drive_C%\CopyFileSample\testfile_copied.txt`ができるので中身を確認する

上記の手順を実施すると、testfile_copied.txtが壊れている。

### 手順についての解説

CopyFileSample.exeは`C:\CopyFileSample\testfile.txt`を`C:\CopyFileSample\testfile_copied.txt`にコピーするだけのプログラム。

```
int main()
{
    ::CopyFile(_T("C:\\CopyFileSample\\testfile.txt"), _T("C:\\CopyFileSample\\testfile_copied.txt"), false);
}
```

CopyFileSample.exeからみた`C:\CopyFileSample\testfile.txt`の元となるファイルは`Project\%drive_C%\CopyFileSample\testfile.txt`であり、以下のテキストが記載されている。

```
This is a test target file of `CopyFile`.
```

CopyFileSample.exeが実際に見に行っている`testfile.txt`の実体はThinAppによって仮想化されるので見えない。
仮想化されているので、CopyFileSample.exeが実際にファイルをコピーする先は`C:\CopyFileSample\testfile_copied.txt`ではなく`%LOCALAPPDATA%\Thinstall\CopyFileSample\%drive_C%\CopyFileSample\testfile_copied.txt`となる。
