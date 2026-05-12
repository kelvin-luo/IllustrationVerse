G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse\src

260512重构任务:

```shell
cmake位置：D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe
qt6位置；D:\Qt
ninja位置；D:\win10\ninja.exe
TensorRT:D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-13.2
cuda13: "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2"
考虑基于msvc2022-64进行编译运行。

stable-diffusion.cpp是一个第三方的库，不要修改；
StableVerse是我写的一个应用封装的主程序，可以修改。
现在希望程序是一个基于插件式的架构。
StableVerse作为开源代码开放，也是作为主程序。

以下插件库作为商业版的组件：
StableVerse_Activator打算做成一个机器绑定的收费验证模块，用于实现订阅收费；收费策略关联机器码，月份，软件版本号；其中对于小版本一次授权后不再重新收费；对于大版本更新则重新计费；文件夹和其他名字都可以修改；
代码中资源文件中有二维码可以收费。
另有打赏界面、广告界面在首页弹窗中，当付费后，不再提示打赏界面和广告界面。

StableVerse_Enhance打算做成一个增强的插件库，文件夹和其他名字都可以修改；
StableCanvas也是打算做成另一个增强的插件库，文件夹和其他名字都可以修改；
Anydraw也是打算做成另一个增强的插件库，文件夹和其他名字都可以修改；

现在对项目进行修改重构。
注意：代码要精炼；非必要不添加新的代码；但是必须要改的就直接改。
```
~~一个用户id记录的登陆模块，以及收费验证模块，用于实现订阅收费~~



#### a、build-by-msvc: x64 Native Tools Command Prompt for VS2022: cuda13:

by-poweshell:

```powershell
$env:PATH = "D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-13.2\lib;" + $env:PATH
$env:PATH += ";D:\Qt\6.11.0\msvc2022_64\bin;D:\opencv4130\build\x64\vc16\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2\nvvm\bin"
```

by-cmd: x64 Native Tools Command Prompt for VS2022:

~~cd  /d  G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse~~

```cmd
cd /d G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse

"D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe" -S ".\IllustrationVerse" -B ".\build-msvc" -G "Visual Studio 17 2022" -A x64    -DYOLOV8_WITH_TRT=ON   -DYOLOV8_TRT_ROOT="D:/win10/TensorRT-10.16.1.11.Windows.amd64.cuda-13.2"   -DYOLOV8_CUDA_ROOT="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.2"   -DCMAKE_PREFIX_PATH="D:/Qt/6.11.0/msvc2022_64"   -DOpenCV_DIR="D:/opencv4130/build" -DSD_BUILD_EXAMPLES=1 -DSD_BUILD_SHARED_LIBS=1
  
"D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe" --build ".\build-msvc" --config Release

set PATH=D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-13.2\lib;%PATH%
set PATH=%PATH%;D:\Qt\6.11.0\msvc2022_64\bin;D:\opencv4130\build\x64\vc16\bin;"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2\bin";"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v13.2\bin\x64"


rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\Anydraw.exe
rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\StableCanvas.exe
rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\StableVerse.exe

cd /d .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release

.\StableVerse.exe

sd-cli.exe -m .\models\checkpoints\animaPencilXL_v500.safetensors -p  "1 girl," 

# —— 若你只在 PowerShell 里操作，用下面等价写法（不要用 set）：
# $env:PATH = "D:\win10\TensorRT-10.16.1.11\lib;" + $env:PATH
```

commd:

```shell
./sd-cli.exe    -m ./models/checkpoints/animaPencilXL_v500.safetensors -p "1 girl,"  --embd-dir  .\models\embeddings --lora-model-dir .\models\loras -n "bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry, Missing limbs, three arms, bad feet, text font ui, signature, blurry, malformed hands, long neck, mutated hands and fingers :1.5).(long body :1.3),(mutation ,poorly drawn :1.2), disfigured, malformed, mutated, multiple breasts, futa, yaoi, three legs, huge breasts,"  --cfg-scale  6 --strength  0.7  --steps   30 --sampling-method  dpm++2m --scheduler karras -W  1152 -H  896 --batch-count  2  -v  -o ../output/_v1-5-pruned-emaonly260512_195046_41.png  -s 41 -t 12  --rng  cuda   --sampler-rng  cuda   
  
```

result:

```shell

```

#### b、build-by-ucrt64:

```shell
cd /e/sub_sub/_t_OCR/proj_ucrt64_cmk_cv_qt6_yolo/code

cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_PREFIX_PATH=/ucrt64/lib/cmake \
  -DYOLOV8_WITH_TRT=OFF

cmake --build build

#./build/yolov8_oiv7_demo.exe
../yolov8_oiv7_demo__MinGW_GNU_ucrt_CC_15.2.0_17_x86_64_bin/yolov8_oiv7_demo.exe
```

result:
```shell

```



