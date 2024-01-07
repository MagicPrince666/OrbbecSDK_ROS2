/*******************************************************************************
* Copyright (c) 2023 Orbbec 3D Technology, Inc
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "orbbec_camera/ros_param_backend.h"

namespace orbbec_camera {
ParametersBackend::ParametersBackend(rclcpp::Node *node)
    : node_(node), logger_(node_->get_logger()) {}

ParametersBackend::~ParametersBackend() {
  if (ros_callback_) {
#if !defined(USE_ELOQUENT_VERSION) && !defined(USE_DASHING_VERSION)
    node_->remove_on_set_parameters_callback(
        (rclcpp::node_interfaces::OnSetParametersCallbackHandle *)(ros_callback_.get()));
#endif
    ros_callback_.reset();
  }
}

void ParametersBackend::addOnSetParametersCallback(
#if defined(USE_IRON_VERSION)
    rclcpp::node_interfaces::NodeParametersInterface::OnSetParametersCallbackType callback
#else
    rclcpp::node_interfaces::NodeParametersInterface::OnParametersSetCallbackType callback
#endif
) {
#if defined(USE_ELOQUENT_VERSION) || defined(USE_DASHING_VERSION)
  if(callback) {
    // 待适配
    // ros_callback_ = node_->set_on_parameters_set_callback((void)callback);
  }
#else
  ros_callback_ = node_->add_on_set_parameters_callback(callback);
#endif
}

}  // namespace orbbec_camera
