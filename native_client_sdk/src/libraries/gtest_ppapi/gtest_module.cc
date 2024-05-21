// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "gtest_ppapi/gtest_instance.h"
#include "ppapi/cpp/module.h"

// GTestModule is a NaCl module dedicated to running gtest-based unit tests.
// It creates an NaCl instance based on GTestInstance.
class GTestModule : public pp::Module {
 public:
  GTestModule() : pp::Module() {}
  ~GTestModule() {}

  virtual pp::Instance* CreateInstance(PP_Instance instance) {
    return new GTestInstance(instance);
  }
};

namespace pp {

Module* CreateModule() {
  return new GTestModule();
}

}  // namespace pp
