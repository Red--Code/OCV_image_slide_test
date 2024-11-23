#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

cv::Mat readBinaryImage(const std::string& filePath, int width, int height) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::vector<uint16_t> pixelData;
    uint16_t value;
    while (file >> value) {
        pixelData.push_back(value);
    }
    //std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file), {});
    file.close();
    return cv::Mat(height, width, CV_16UC1, pixelData.data()).clone();
}

int main() {
    const std::string filePath = "buffer_to_show(640IN800).Txt";
    cv::Mat image;
    image = readBinaryImage(filePath, 640, 800);
    cv::imshow("image", image);
    cv::imwrite("image.png", image);
    std::cout << "Press any key for the animation" << std::endl;
    cv::waitKey(0);
    cv::Mat rgbImage;
    cv::cvtColor(image, rgbImage, cv::COLOR_GRAY2BGR);
    cv::resize(rgbImage, rgbImage, cv::Size(), 0.5, 0.5);
    const int canvasWidth = 800;
    const int canvasHeight = 500;
    cv::Mat canvas(canvasHeight, canvasWidth, CV_16UC3, cv::Scalar(0XFFFF, 0XFFFF, 0XFFFF));

    int xPos = 0;
    
    bool dir_flag = false;
    while (true) {
        canvas.setTo(cv::Scalar(0XFFFF, 0XFFFF, 0XFFFF));

        rgbImage.copyTo(canvas(cv::Rect(xPos, 50, rgbImage.cols, rgbImage.rows)));

        cv::imshow("Animation", canvas);

        if (!dir_flag) {
            xPos += 5;
            if (xPos >= (canvasWidth - 320)) dir_flag = true;
        }
        else {
            xPos -= 5;
            if (xPos <= 0) dir_flag = false;
        }
       
        //std::cout << xPos << std::endl;
        if (cv::waitKey(30) >= 0) break;
    }
    cv::destroyAllWindows();
    return 0;
}
