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

This sample demonstrates Linux C++ crash reporting with [BugSplat](https://bugsplat.com) and [Crashpad](https://chromium.googlesource.com/crashpad/crashpad/+/master/README.md). The `my-ubuntu-crasher` sample includes a [prebuilt version](https://github.com/BugSplat-Git/my-ubuntu-crasher/tree/main/crashpad/lib) of Crashpad and [symbol-upload](https://github.com/BugSPlat-Git/symbol-upload) to create `.sym` files and upload them to BugSplat.

## Steps 🥾

1. Ensure `git`, `git-lfs`, `llvm`, `build-essential`, and `clang` are installed on your machine
2. Clone this repository and ensure all files, including git-lfs artifact `symbol-upload-linux` were downloaded correctly
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

4. Generate and upload symbols to BugSplat using symbol-upload and the `--dumpSyms` flag

```bash
$CRASHPAD_DIR/tools/symbol-upload-linux -b $BUGSPLAT_DATABASE \
    -a $BUGSPLAT_APP_NAME \
    -v $BUGSPLAT_APP_VERSION \
    -u $BUGSPLAT_EMAIL \
    -p $BUGSPLAT_PASSWORD \
    -d $PROJECT_DIR/out \
    -f $MODULE_NAME \
    --dumpSyms
```

5. Run the output executable to generate a crash report

```bash
./out/myUbuntuCrasher

# [10939:10939:20240705,155021.774184:ERROR file_io_posix.cc:144] open /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq: No such file or directory (2)
# [10939:10939:20240705,155021.774253:ERROR file_io_posix.cc:144] open /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq: No such file or directory (2)
# Segmentation fault
```

7. Log into [BugSplat](https://bugsplat.com) using our public account `fred@bugsplat.com` and password `Flintstone`
8. Navigate to the [Crashes]([https://app.bugsplat.com/v2/crashes](https://app.bugsplat.com/v2/crashes?c0=appName&f0=CONTAINS&v0=myUbuntuCrasher&database=Fred)) page and click the link in the ID column to see a detailed crash report

<img width="1728" alt="myUbuntuCrasher crash on BugSplat" src="https://github.com/BugSplat-Git/my-ubuntu-crasher/assets/2646053/07c97d9c-29ea-486b-808e-785a6fc2597d">

## Other ℹ️

Please ensure that you increment the version number every time you build and generate/upload new symbol files. If you fail to create and upload symbol files, your crash reports will not contain file names and source line numbers.
