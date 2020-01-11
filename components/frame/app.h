#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "data_reader/sensor_storage.h"
#include "data_reader/storage_service.h"
#include "com_out/ibroadcast.h"
#include "com_out/irequest_listener.h"
#include "runtime_meas_service.h"
// #include "object_detection/detector.h"
#include <signal.h>


namespace frame {
  class App: public com_out::IRequestListener {
  public:
    App(const std::string& sensorConfigPath);

    void run(const com_out::IBroadcast& broadCaster);
    void handleRequest(const std::string& requestType, const nlohmann::json& requestData, nlohmann::json& responseData) override;

  private:
    data_reader::StorageService _storageService;
    data_reader::SensorStorage _sensorStorage;
    // object_detection::Detector _detector;
    RuntimeMeasService _runtimeMeasService;

    // Actions to take for recordings
    bool _pause;
    bool _stepForward;
    bool _stepBackward;
    bool _updateTs;
    bool _record;

    int64_t _jumpToTs;
    bool _isRecording;
    int64_t _recLength;
    int _maxFrames;

    // Current output state sent to the clients
    std::string _outputState;
    int64_t _ts; // algo timestamp of the current frame
    int _frame; // current frame counter
  };
}
