#pragma once

#include <tuple>
#include "icam.h"


namespace data_reader {
  class VideoCam : public ICam {
  public:
    VideoCam(const std::string& filename);
    virtual std::tuple<const bool, const int64, cv::Mat> getFrame(
      const std::chrono::time_point<std::chrono::high_resolution_clock>& algoStartTime,
      const int64 jumpToTs = -1) override;
    const double getFrameRate() const override { return _frameRate; }
    const bool isRecording() const override { return true; }
    const int64 getRecLength() const override { return _recLength; }

  private:
    cv::VideoCapture _stream;
    const std::string _filename;
    double _frameRate;
    int64 _recLength; // length of recording in [us]
  };
}
