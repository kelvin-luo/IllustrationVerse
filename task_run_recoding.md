G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse\src

260512重构任务:

```shell
cmake位置：D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe
qt6位置；D:\Qt
ninja位置；D:\win10\ninja.exe
TensorRT:D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-12.8
cuda13: "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8"
vulkan目录式：C:\VulkanSDK
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
$env:PATH = "D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-12.8\lib;" + $env:PATH
$env:PATH += ";D:\Qt\6.11.0\msvc2022_64\bin;D:\opencv4130\build\x64\vc16\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8\nvvm\bin"
```

by-cmd: x64 Native Tools Command Prompt for VS2022:

~~cd  /d  G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse~~

```cmd
cd /d G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse

"D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe" -S ".\IllustrationVerse" -B ".\build-msvc" -G "Visual Studio 17 2022" -A x64    -DYOLOV8_WITH_TRT=ON   -DYOLOV8_TRT_ROOT="D:/win10/TensorRT-10.16.1.11.Windows.amd64.cuda-12.8"   -DYOLOV8_CUDA_ROOT="C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.8"   -DCMAKE_PREFIX_PATH="D:/Qt/6.11.0/msvc2022_64"   -DOpenCV_DIR="D:/opencv4130/build" -DSD_BUILD_EXAMPLES=1 -DSD_BUILD_SHARED_LIBS=1  -DSD_CUDA=ON -DSD_VULKAN=ON -DOpenCL=ON  -DSYCL=ON 
  
"D:\win10\cmake-4.2.1-windows-x86_64\bin\cmake.exe" --build ".\build-msvc" --config Release  -j16

set PATH=D:\win10\TensorRT-10.16.1.11.Windows.amd64.cuda-12.8\lib;%PATH%
set PATH=%PATH%;D:\Qt\6.11.0\msvc2022_64\bin;D:\opencv4130\build\x64\vc16\bin;"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8\bin";"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.8\bin\x64"


rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\Anydraw.exe
rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\StableCanvas.exe
rem .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release\StableVerse.exe

cd /d .\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release

.\StableVerse.exe

sd-cli.exe -m .\models\checkpoints\animaPencilXL_v500.safetensors -p  "1 girl," 

# —— 若你只在 PowerShell 里操作，用下面等价写法（不要用 set）：
# $env:PATH = "D:\win10\TensorRT-10.16.1.11\lib;" + $env:PATH
```

260512commd:

```shell
.\sd-cli.exe    -m ./models/checkpoints/animaPencilXL_v500.safetensors -p "1 girl,"  --embd-dir  .\models\embeddings --lora-model-dir .\models\loras -n "bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry, Missing limbs, three arms, bad feet, text font ui, signature, blurry, malformed hands, long neck, mutated hands and fingers :1.5).(long body :1.3),(mutation ,poorly drawn :1.2), disfigured, malformed, mutated, multiple breasts, futa, yaoi, three legs, huge breasts,"  --cfg-scale  6 --strength  0.7  --steps   30 --sampling-method  dpm++2m --scheduler karras -W  768 -H  512 --batch-count  2  -v  -o ../output/_v1-5-pruned-emaonly260512_195046_41.png  -s 41 -t 12  --rng  cuda   --sampler-rng  cuda

sd-cli.exe -m .\models\checkpoints\animaPencilXL_v500.safetensors -p "1 girl,"  --embd-dir  .\models\embeddings --lora-model-dir .\models\loras -n "bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry, Missing limbs, three arms, bad feet, text font ui, signature, blurry, malformed hands, long neck, mutated hands and fingers :1.5).(long body :1.3),(mutation ,poorly drawn :1.2), disfigured, malformed, mutated, multiple breasts, futa, yaoi, three legs, huge breasts,"  --cfg-scale  6 --strength  0.7  --steps   30 --sampling-method  dpm++2m --scheduler  karras -W  1152 -H  896 --batch-count  2  -v -o ../output/_v1-5-pruned-emaonly260512_234219_41.jpg -s 41 -t 12 
```

result:260512-2356:

```shell
G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release>
G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release>sd-cli.exe -m .\models\checkpoints\animaPencilXL_v500.safetensors -p  "1 girl,"
[INFO ] ggml_extend.hpp:63   - ggml_cuda_init: found 1 CUDA devices (Total VRAM: 24454 MiB):
[INFO ] ggml_extend.hpp:63   -   Device 0: NVIDIA GeForce RTX 5090 D v2, compute capability 12.0, VMM: yes, VRAM: 24454 MiB
[INFO ] stable-diffusion.cpp:212  - loading model from '.\models\checkpoints\animaPencilXL_v500.safetensors'
[INFO ] model.cpp:219  - load .\models\checkpoints\animaPencilXL_v500.safetensors using safetensors format
[INFO ] stable-diffusion.cpp:305  - Version: SDXL
[INFO ] stable-diffusion.cpp:333  - Weight type stat:                      f16: 2513
[INFO ] stable-diffusion.cpp:334  - Conditioner weight type stat:          f16: 585
[INFO ] stable-diffusion.cpp:335  - Diffusion model weight type stat:      f16: 1680
[INFO ] stable-diffusion.cpp:336  - VAE weight type stat:                  f16: 248
[INFO ] stable-diffusion.cpp:640  - using VAE for encoding / decoding
[INFO ] auto_encoder_kl.hpp:525  - vae decoder: ch = 128
[WARN ] stable-diffusion.cpp:621  - No valid VAE specified with --vae or --force-sdxl-vae-conv-scale flag set, using Conv2D scale 0.031
  |==================================================| 2513/2513 - 2.07GB/s[K
[INFO ] model.cpp:999  - loading tensors completed, taking 3.09s (process: 0.00s, read: 0.95s, memcpy: 0.00s, convert: 0.00s, copy_to_backend: 2.02s)
[INFO ] stable-diffusion.cpp:873  - total params memory size = 6558.89MB (VRAM 6558.89MB, RAM 0.00MB): text_encoders 1564.36MB(VRAM), diffusion_model 4900.07MB(VRAM), vae 94.47MB(VRAM), controlnet 0.00MB(VRAM), pmid 0.00MB(VRAM)
[INFO ] stable-diffusion.cpp:931  - running in eps-prediction mode
[INFO ] stable-diffusion.cpp:3367 - generate_image 512x512
[INFO ] denoiser.hpp:499  - get_sigmas with discrete scheduler
[INFO ] stable-diffusion.cpp:2814 - sampling using Euler A method
[INFO ] stable-diffusion.cpp:3168 - get_learned_condition completed, taking 0.16s
[INFO ] stable-diffusion.cpp:3401 - generating image: 1/1 - seed 42
  |==================================================| 20/20 - 7.62it/s[K
[INFO ] stable-diffusion.cpp:3432 - sampling completed, taking 2.64s
[INFO ] stable-diffusion.cpp:3452 - generating 1 latent images completed, taking 2.66s
[INFO ] stable-diffusion.cpp:3192 - decoding 1 latents
[INFO ] stable-diffusion.cpp:3208 - latent 1 decoded, taking 0.13s
[INFO ] stable-diffusion.cpp:3212 - decode_first_stage completed, taking 0.13s
[INFO ] stable-diffusion.cpp:3591 - generate_image completed in 2.97s
[INFO ] main.cpp:441  - save result image 0 to 'output.png' (success)
[INFO ] main.cpp:490  - 1/1 images saved

G:\_busi1_MUST_BUSI_APP\proj_IllustrationVerse\qSD_0.1_Windows_MSVC_CC_19.44.35226.0_17_x64_bin\Release>
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



