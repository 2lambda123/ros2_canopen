// Copyright (c) 2022, Stogl Robotics Consulting UG (haftungsbeschränkt)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


//----------------------------------------------------------------------
/*!\file
 *
 * \author  Lovro Ivanov lovro.ivanov@gmail.com
 * \date    2022-06-29
 *
 */
//----------------------------------------------------------------------

#ifndef CANOPEN_ROS2_CONTROL__CANOPEN_SYSTEM_HPP_
#define CANOPEN_ROS2_CONTROL__CANOPEN_SYSTEM_HPP_

#include <string>
#include <vector>

#include "canopen_core/device_container_node.hpp"
#include "canopen_ros2_control/visibility_control.h"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/executors.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp_lifecycle/state.hpp"




namespace canopen_ros2_control
{
class CanopenSystem : public hardware_interface::SystemInterface
{
public:
    TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
    ~CanopenSystem();
  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  hardware_interface::CallbackReturn on_init(
    const hardware_interface::HardwareInfo & info) override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  hardware_interface::return_type read(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  TEMPLATES__ROS2_CONTROL__VISIBILITY_PUBLIC
  hardware_interface::return_type write(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  std::vector<double> hw_commands_;
  std::vector<double> hw_states_;

  std::shared_ptr<DeviceContainerNode> device_manager_;
  std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> executor_;
  std::shared_ptr<rclcpp_components::ComponentManager> component_manager_;
  std::shared_ptr<rclcpp::Node> node_;

  std::unique_ptr<std::thread> spin_thread_;
  std::unique_ptr<std::thread> init_thread_;
  void spin();
  void initDeviceManager();
};

}  // namespace canopen_ros2_control

#endif  // CANOPEN_ROS2_CONTROL__CANOPEN_SYSTEM_HPP_
