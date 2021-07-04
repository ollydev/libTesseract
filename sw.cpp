void build(Solution &s)
{
    auto &tess = s.addProject("google.tesseract", "master");
    tess += Git("https://github.com/tesseract-ocr/tesseract", "", "{v}");

    auto cppstd = cpp17;

    auto &libtesseract = tess.addTarget<LibraryTarget>("libtesseract");
    {
        libtesseract.setChecks("libtesseract");

        libtesseract.PackageDefinitions = true;

        libtesseract += cppstd;

        libtesseract += "TESS_API"_api;
        libtesseract += "include/.*"_rr;
        libtesseract += "src/.*"_rr;
        libtesseract -= "src/lstm/.*\\.cc"_rr;
        libtesseract -= "src/training/.*"_rr;

        libtesseract -=
            "src/api/tesseractmain.cpp",
            "src/viewer/svpaint.cpp";

        libtesseract.Public += "include"_idir;
        libtesseract.Protected +=
            "src/opencl"_id,
            "src/ccmain"_id,
            "src/api"_id,
            "src/dict"_id,
            "src/viewer"_id,
            "src/wordrec"_id,
            "src/ccstruct"_id,
            "src/cutil"_id,
            "src/textord"_id,
            "src/ccutil"_id,
            "src/lstm"_id,
            "src/classify"_id,
            "src/arch"_id,
            "src/training"_id;

        if (libtesseract.getCompilerType() == CompilerType::MSVC ||
            libtesseract.getCompilerType() == CompilerType::ClangCl)
        {
            libtesseract += "__SSE4_1__"_def;
            libtesseract.CompileOptions.push_back("-arch:AVX2");

            // openmp
            //if (libtesseract.getOptions()["openmp"] == "true")
            if (0)
            {
                if (libtesseract.getCompilerType() == CompilerType::MSVC)
                    libtesseract.CompileOptions.push_back("-openmp");
                else
                    libtesseract.CompileOptions.push_back("-fopenmp");
                libtesseract += "_OPENMP=201107"_def;
                if (libtesseract.getBuildSettings().Native.ConfigurationType == ConfigurationType::Debug)
                    libtesseract += "vcompd.lib"_slib;
                else
                    libtesseract += "vcomp.lib"_slib;
            }
        }

        auto win_or_mingw =
            libtesseract.getBuildSettings().TargetOS.Type == OSType::Windows ||
            libtesseract.getBuildSettings().TargetOS.Type == OSType::Mingw
            ;

        // check fma flags
        libtesseract -= "src/arch/dotproductfma.cpp";

        if (libtesseract.getBuildSettings().TargetOS.Type != OSType::Windows)
        {
            libtesseract["src/arch/dotproductavx.cpp"].args.push_back("-mavx");
            libtesseract["src/arch/dotproductsse.cpp"].args.push_back("-msse4.1");
            libtesseract["src/arch/intsimdmatrixsse.cpp"].args.push_back("-msse4.1");
            libtesseract["src/arch/intsimdmatrixavx2.cpp"].args.push_back("-mavx2");
        }
        if (!win_or_mingw)
            libtesseract += "pthread"_slib;

        libtesseract.Public += "HAVE_CONFIG_H"_d;
        libtesseract.Public += "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS=1"_d;
        //libtesseract.Public += "HAVE_LIBARCHIVE"_d;

        libtesseract.Public += "org.sw.demo.danbloomberg.leptonica"_dep;
        // libtesseract.Public += "org.sw.demo.libarchive.libarchive"_dep;

        if (win_or_mingw)
        {
            libtesseract.Public += "ws2_32.lib"_slib;
            libtesseract.Protected += "NOMINMAX"_def;
        }

        if (libtesseract.getCompilerType() == CompilerType::MSVC)
            libtesseract.Protected.CompileOptions.push_back("-utf-8");

        libtesseract.Variables["TESSERACT_MAJOR_VERSION"] = libtesseract.Variables["PACKAGE_MAJOR_VERSION"];
        libtesseract.Variables["TESSERACT_MINOR_VERSION"] = libtesseract.Variables["PACKAGE_MINOR_VERSION"];
        libtesseract.Variables["TESSERACT_MICRO_VERSION"] = libtesseract.Variables["PACKAGE_PATCH_VERSION"];
        libtesseract.Variables["TESSERACT_VERSION_STR"] = "master";
        libtesseract.configureFile("include/tesseract/version.h.in", "tesseract/version.h");
    }
}

void check(Checker &c)
{
    auto &s = c.addSet("libtesseract");
    s.checkFunctionExists("getline");
    s.checkIncludeExists("dlfcn.h");
    s.checkIncludeExists("inttypes.h");
    s.checkIncludeExists("memory.h");
    s.checkIncludeExists("stdint.h");
    s.checkIncludeExists("stdlib.h");
    s.checkIncludeExists("string.h");
    s.checkIncludeExists("sys/stat.h");
    s.checkIncludeExists("sys/types.h");
    s.checkIncludeExists("tiffio.h");
    s.checkIncludeExists("unistd.h");
    s.checkTypeSize("long long int");
    s.checkTypeSize("size_t");
    s.checkTypeSize("void *");
    s.checkTypeSize("wchar_t");
    {
        auto &c = s.checkSymbolExists("snprintf");
        c.Parameters.Includes.push_back("stdio.h");
    }
}

