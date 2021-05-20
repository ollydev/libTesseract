Downloads are available here https://github.com/ollydev/libtesseract/releases

-----

This is a shared library (dll, so, dylib) which exports basic C [Tesseract-OCR](https://github.com/tesseract-ocr/tesseract) functions for basic text recognition. Tesseract and it's dependencies have been statically linked so only a single library is required.

The following methods are exported:
```c++
tesseract::TessBaseAPI* Tesseract_Create();
void Tesseract_Delete(tesseract::TessBaseAPI* &tesseract_ptr);
int Tesseract_Init(tesseract::TessBaseAPI* tesseract_ptr, const char* datapath, const char* language);
void Tesseract_End(tesseract::TessBaseAPI* &tesseract_ptr);
void Tesseract_SetImage(tesseract::TessBaseAPI* tesseract_ptr, const unsigned char* imagedata, int width, int height, int bytes_per_pixel, int bytes_per_line);
const char* Tesseract_GetUTF8Text(tesseract::TessBaseAPI* tesseract_ptr, uint32_t* len);
void Tesseract_FreeUTF8Text(char* &utf8_text_ptr);
bool Tesseract_SetVariable(tesseract::TessBaseAPI* tesseract_ptr, const char* name, const char* value);
void Tesseract_Clear(tesseract::TessBaseAPI* tesseract_ptr);
int Tesseract_GetLineCount(tesseract::TessBaseAPI* tesseract_ptr); 
int Tesseract_GetWordCount(tesseract::TessBaseAPI* tesseract_ptr); 
int Tesseract_GetCharacterCount(tesseract::TessBaseAPI* tesseract_ptr); 
void Tesseract_GetLineMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, char* &text, int* len, float* confidence, int* x1, int* y1, int* x2, int* y2); 
void Tesseract_GetWordMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, char* &text, int* len, float* confidence, int* x1, int* y1, int* x2, int* y2); 
void Tesseract_GetCharacterMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, char* &text, int* len, float* confidence, int* x1, int* y1, int* x2, int* y2);
```
Example Pascal header:

```pascal
function Tesseract_Init(ptr: Pointer; datapath, language: PChar): Int32; external 'libtesseract32.dll'
```
----

See the [Github Action](https://github.com/ollydev/libTesseract/blob/master/.github/workflows/build.yml) to see how this is built. Thanks to [SoftwareNetwork](https://github.com/SoftwareNetwork/sw) for making this a lot easier than it used to be. 
