/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2015, Thorsten Gedicke
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
*********************************************************************/

#ifndef CAMERA_CONSTRAINTS_H
#define CAMERA_CONSTRAINTS_H

#include <tf/transform_datatypes.h>

#include <string>

struct CameraConstraints
{
  std::string frame_id;
  double height_min;
  double height_max;
  double pitch_min;
  double pitch_max;
  double hfov;
  double vfov;
  double range_min;
  double range_max;
  double roll;
  
  CameraConstraints()
  : frame_id("")
  , height_min(0.0)
  , height_max(0.0)
  , pitch_min(0.0)
  , pitch_max(0.0)
  , hfov(0.0)
  , vfov(0.0)
  , range_min(0.0)
  , range_max(0.0)
  , roll(0.0)
  {}

  static tf::Vector3 sphericalToCartesian(const double & range, const double & elevation, const double & azimuth)
  {
      using namespace std;
      return range * tf::Vector3(cos(elevation) * cos(azimuth), cos(elevation) * sin(azimuth), sin(elevation));
  }
};

#endif // CAMERA_CONSTRAINTS_H

