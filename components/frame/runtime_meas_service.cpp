#include "runtime_meas_service.h"


frame::RuntimeMeasService::RuntimeMeasService(const TS& algoStartTime) 
  : _algoStartTime(algoStartTime) {}

void frame::RuntimeMeasService::startMeas(std::string name) {
  _meas.erase(name); // In case the key does not exist at all, this does nothing
  RuntimeMeas meas;
  meas.running = true;
  meas.startTime = std::chrono::high_resolution_clock::now();
  _meas.insert({name, meas});
}

void frame::RuntimeMeasService::endMeas(std::string name) {
  if(_meas.find(name) == _meas.end()) {
    std::cout << "WARNING: Can not end runtime meas: " << name << " does not exist!" << std::endl;
  }
  else {
    _meas.at(name).running = false;
    _meas.at(name).endTime = std::chrono::high_resolution_clock::now();
    _meas.at(name).duration = std::chrono::duration<double, std::milli>(_meas.at(name).endTime - _meas.at(name).startTime);
  }
}

void frame::RuntimeMeasService::printToConsole() {
  std::cout << std::endl;
  for(auto& [key, value]: _meas) {
    if(!value.running) {
      const std::string keyStr = key + ":";
      std::cout << std::left << std::setw(30) << std::setfill(' ') << keyStr <<
        std::right << std::setw(10) << std::setfill(' ') << std::fixed << std::setprecision(4) << value.duration.count() << " ms" << std::endl;
    }
  }
}

std::vector<com_out::RuntimeMeas> frame::RuntimeMeasService::serializeMeas() {
  std::vector<com_out::RuntimeMeas> measVec;
  for(auto& [key, value]: _meas) {
    if(!value.running) {
      auto startTs = static_cast<long int>(std::chrono::duration<double, std::micro>(value.startTime - _algoStartTime).count());
      measVec.push_back({key, startTs, value.duration.count()});
    }
  }
  return measVec;
}
