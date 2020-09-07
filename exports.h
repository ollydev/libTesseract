/**  © 2014, Brandon T. All Rights Reserved.
  *
  *  This file is part of the LibTesseract Library.
  *  LibTesseract is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  LibTesseract is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with LibTesseract.  If not, see <http://www.gnu.org/licenses/>.
  */


#ifndef EXPORTS_HXX_INCLUDED
#define EXPORTS_HXX_INCLUDED

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#if defined _WIN32 || defined _WIN64
#define EXPORT __declspec(dllexport)
#include <windows.h>
extern HINSTANCE hInstance;
#else
#define EXPORT
#include <dlfcn.h>
#endif

static const char* PascalExports[] =
{
	(char*)"Tesseract_Create", (char*)"Function Tesseract_Create(): Pointer;",
	(char*)"Tesseract_Delete", (char*)"Procedure Tesseract_Delete(var tesseract_ptr: Pointer);",
	(char*)"Tesseract_Init", (char*)"Function Tesseract_Init(tesseract_ptr: Pointer; datapath, language: String): Integer;",
	(char*)"Tesseract_End", (char*)"Procedure Tesseract_End(var tesseract_ptr: Pointer);",
	(char*)"Tesseract_SetImage", (char*)"Procedure Tesseract_SetImage(tesseract_ptr: Pointer; const imagedata: Pointer; width, height, bytes_per_pixel, bytes_per_line: Integer);",
	(char*)"Tesseract_GetUTF8Text", (char*)"Function Tesseract_GetUTF8Text(tesseract_ptr: Pointer; var len: UInt32): PChar;",
	(char*)"Tesseract_FreeUTF8Text", (char*)"Procedure Tesseract_FreeUTF8Text(var utf8_text_ptr: PChar);",
	(char*)"Tesseract_SetVariable", (char*)"Function Tesseract_SetVariable(tesseract_ptr: Pointer; name, value: String): Boolean;",
	(char*)"Tesseract_Clear", (char*)"Procedure Tesseract_Clear(tesseract_ptr: Pointer);"
};

static const char* PascalTypes[] =
{
	""
};

static const long int PascalExportCount = sizeof(PascalExports) / (sizeof(PascalExports[0]) * 2);
static const long int PascalTypeCount = sizeof(PascalTypes) / (sizeof(PascalTypes[0]) * 2);


extern "C"
{
    EXPORT tesseract::TessBaseAPI* Tesseract_Create();
    EXPORT void Tesseract_Delete(tesseract::TessBaseAPI* &tesseract_ptr);
    EXPORT int Tesseract_Init(tesseract::TessBaseAPI* tesseract_ptr, const char* datapath, const char* language);
    EXPORT void Tesseract_End(tesseract::TessBaseAPI* &tesseract_ptr);
    EXPORT void Tesseract_SetImage(tesseract::TessBaseAPI* tesseract_ptr, const unsigned char* imagedata, int width, int height, int bytes_per_pixel, int bytes_per_line);
    EXPORT const char* Tesseract_GetUTF8Text(tesseract::TessBaseAPI* tesseract_ptr, uint32_t* len);
    EXPORT void Tesseract_FreeUTF8Text(char* &utf8_text_ptr);
    EXPORT bool Tesseract_SetVariable(tesseract::TessBaseAPI* tesseract_ptr, const char* name, const char* value);
    EXPORT void Tesseract_Clear(tesseract::TessBaseAPI* tesseract_ptr);

    EXPORT int GetPluginABIVersion();
    EXPORT int GetFunctionCount();
    EXPORT int GetTypeCount();
    EXPORT int GetFunctionInfo(int Index, void** Address, char** Definition);
    EXPORT int GetTypeInfo(int Index, char** Type, char** Definition);
}

#endif // EXPORTS_HXX_INCLUDED
