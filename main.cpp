/**	 © 2014, Brandon T. All Rights Reserved.
  *
  *	 This file is part of the LibTesseract Library.
  *	 LibTesseract is free software: you can redistribute it and/or modify
  *	 it under the terms of the GNU General Public License as published by
  *	 the Free Software Foundation, either version 3 of the License, or
  *	 (at your option) any later version.
  *
  *	 LibTesseract is distributed in the hope that it will be useful,
  *	 but WITHOUT ANY WARRANTY; without even the implied warranty of
  *	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *	 GNU General Public License for more details.
  *
  *	 You should have received a copy of the GNU General Public License
  *	 along with LibTesseract.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "exports.h"

#if defined(_WIN32) || defined(_WIN64)

HMODULE module = nullptr;

extern "C" EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	module = hinstDLL;

	return TRUE;
}
#endif
