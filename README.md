## libTesseract

This is a shared library (dll, so, dylib) which exports basic [Tesseract-OCR](https://github.com/tesseract-ocr/tesseract) functions. Tesseract and it's dependencies have been statically linked so no other libraries are required.

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
void Tesseract_GetLineMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, float* confidence, int* x1, int* y1, int* x2, int* y2); 
void Tesseract_GetWordMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, float* confidence, int* x1, int* y1, int* x2, int* y2); 
void Tesseract_GetCharacterMatch(tesseract::TessBaseAPI* tesseract_ptr, int index, float* confidence, int* x1, int* y1, int* x2, int* y2);
```

See the [Github Action](https://github.com/ollydev/libTesseract/blob/master/.github/workflows/build.yml) to see how this is built. Thanks to [SoftwareNetwork](https://github.com/SoftwareNetwork/sw) for making this so simple! 
