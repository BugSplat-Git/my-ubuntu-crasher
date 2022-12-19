[![bugsplat-github-banner-basic-outline](https://user-images.githubusercontent.com/20464226/149019306-3186103c-5315-4dad-a499-4fd1df408475.png)](https://bugsplat.com)
<br/>
# <div align="center">BugSplat</div> 
### **<div align="center">Crash and error reporting built for busy developers.</div>**
<div align="center">
    <a href="https://twitter.com/BugSplatCo">
        <img alt="Follow @bugsplatco on Twitter" src="https://img.shields.io/twitter/follow/bugsplatco?label=Follow%20BugSplat&style=social">
    </a>
    <a href="https://discord.gg/K4KjjRV5ve">
        <img alt="Join BugSplat on Discord" src="https://img.shields.io/discord/664965194799251487?label=Join%20Discord&logo=Discord&style=social">
    </a>
</div>

## Introduction 👋

This sample demonstrates Linux C++ crash reporting with [BugSplat](https://bugsplat.com) and [Crashpad](https://chromium.googlesource.com/crashpad/crashpad/+/master/README.md). The `my-ubuntu-crasher` sample includes a [prebuilt version](https://github.com/BugSplat-Git/my-ubuntu-crasher/tree/main/crashpad/lib) of Crashpad as well as the [Breakpad](https://chromium.googlesource.com/breakpad/breakpad/) tools dump_syms and symupload.

## Steps 🥾

1. Ensure git, python, llvm and clang are installed on your machine
2. Clone this repository
3. Build main.cpp with debug information and a build ID and link the Crashpad libraries using clang

```bash
clang++ -pthread $PROJECT_DIR/main.cpp \
    $CRASHPAD_DIR/lib/libcommon.a \
    $CRASHPAD_DIR/lib/libclient.a \
    $CRASHPAD_DIR/lib/libutil.a \
    $CRASHPAD_DIR/lib/libbase.a \
    -I$CRASHPAD_DIR/include \
    -I$CRASHPAD_DIR/include/third_party/mini_chromium/mini_chromium \
    -I$CRASHPAD_DIR/include/out/Default/gen \
    -o$OUT_DIR/$MODULE_NAME \
    -g \
    -Wl,--build-id
```

4. Generate .sym files for the output executable

```bash
export SYM_FILE=$OUT_DIR/$MODULE_NAME.sym
$CRASHPAD_DIR/tools/dump_syms $PROJECT_DIR/out/$MODULE_NAME > $SYM_FILE
```
5. Upload the generated .sym file to BugSplat

```bash
export SYM_FILE=$OUT_DIR/$MODULE_NAME.sym
$CRASHPAD_DIR/tools/symupload $SYM_FILE "https://$BUGSPLAT_DATABASE.bugsplat.com/post/bp/symbol/breakpadsymbols.php?appName=$BUGSPLAT_APP_NAME&appVer=$BUGSPLAT_APP_VERSION"
```

6. Run the output executable to generate a crash report
7. Log into BugSplat using our public account fred@bugsplat.com and password Flintstone
8. Navigate to the Crashes page and click the link in the ID column to see a detailed crash report

## Other ℹ️

Make sure that every time you build you increment the version number and generate/upload new symbol files. If you fail to generate and upload symbol files your crash reports will not contain file names and source line numbers.
