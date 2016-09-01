#include "pixelmap.h"

using namespace pixelmap;

namespace pixelmap {

RippleVisualization::RippleVisualization(Input* input, int size, int smoothing)
    : Visualization(input, size),
      smoothing_length_(smoothing) {
  smoothing_ = new double[smoothing_length_];

  for (int i = 0; i < smoothing_length_; i++) {
    smoothing_[i] = 0.0;
  }
}


RippleVisualization::~RippleVisualization() {
  delete[] smoothing_;
}

void RippleVisualization::update() {
  double value = input->getInput();

  double sum = 0.0;
  for (int i = 0; i < smoothing_length_; i++) {
    sum += smoothing_[i];
  }
  sum += value;
  value = sum / (double)(smoothing_length_ + 1);

  PushQueue(smoothing_, smoothing_length_, value);

  int hue = 192 + (-value * 192);
  int val = 255;
  if (value < 0.001) { val = 0; }
  CRGB color = CHSV(hue, 255, val);
  PushQueue(viz, size_, color);
}

} // end namespace pixelmap
