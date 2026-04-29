// simple_ocr.h
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>


// 导出宏：保持与之前一致
#ifdef PPAPI_EXPORTS
#define PPAPI __declspec(dllexport)
#else
#define PPAPI __declspec(dllimport)
#endif

// 1. 定义纯数据结构的配置项
struct PPAPI SimpleOCRConfig {
    std::string det_model_dir;
    std::string rec_model_dir;
    std::string cls_model_dir;
    bool use_gpu;
    int cpu_threads;
    // 可以添加其他基本类型的配置
};

// 2. 定义纯数据结构的返回结果
struct PPAPI OCRResult {
    std::vector<std::vector<std::string>> res;  // 识别的文字
    //float confidence;           // 置信度
    // 使用简单的坐标结构，代替 cv::Point
    //std::vector<std::pair<int, int>> points;
};

// 3. 对外暴露的主类
class PPAPI SimpleOCR {
public:
    SimpleOCR(const SimpleOCRConfig& config);
    ~SimpleOCR();

    // 核心接口：
    // 1. 输入是图片路径 (std::string)，而不是 cv::Mat
    // 2. 输出是标准 vector，不需要依赖 OpenCV 的内存管理
    OCRResult process_image(const std::string& image_path);
    OCRResult processMat(cv::Mat mat);

private:
    // --- Pimpl 惯用法核心 ---
    // 声明一个类，但不定义它（不完整类型）
    // 这样头文件的使用者就不需要知道 Impl 里面有什么，也就无需包含复杂的头文件
    class Impl;

    // 使用指针持有实现类
    // 也可以用 std::unique_ptr<Impl> 来自动管理内存
    Impl* m_impl;
};
