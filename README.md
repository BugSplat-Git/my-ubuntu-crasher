[![BugSplat](https://s3.amazonaws.com/bugsplat-public/npm/header.png)](https://www.bugsplat.com)

# myUbuntuCrasher
This sample demonstrates Linux crash reporting with BugSplat and Crashpad. MyUbuntuCrasher includes a prebuilt version of Crashpad as well as the Breakpad tools dump_syms and symupload.

## Steps
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

## Other
Make sure that every time you build you increment the version number and generate/upload new symbol files. If you fail to generate and upload symbol files your crash reports will not contain file names and source line numbers.
