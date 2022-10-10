program test;

{$mode objfpc}{$H+}

uses
  classes, sysutils, dynlibs;

var
  FileName, Version: String;
  Lib: TLibHandle;
  TessVersionFunction: function: PChar; cdecl;
  TessVersion: String;
begin
  FileName := ExpandFileName(ParamStr(1));
  Version := ParamStr(2);

  Lib := LoadLibrary(FileName);
  if (Lib = NilHandle) then
  begin
    WriteLn('Loading library failed: ' + GetLoadErrorStr());
    Halt(1);
  end;

  Pointer(TessVersionFunction) := GetProcAddress(Lib, 'TessVersion');
  if not Assigned(TessVersionFunction) then
  begin
    WriteLn('TessVersionFunction = nil');
    Halt(1);
  end;

  TessVersion := String(TessVersionFunction());
  if (TessVersion <> Version)  then
  begin
    WriteLn('Tesseract version failed: "' + TessVersion + '" <> "' + Version + '"');
    Halt(1);
  end;

  WriteLn('Tesseract version: ', TessVersion);
  WriteLn('Tesseract library success!');
end.

