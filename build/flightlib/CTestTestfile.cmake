# CMake generated Testfile for 
# Source directory: /root/workspace/catkin_ws/flightmare_ws/src/flightmare/flightlib
# Build directory: /root/workspace/catkin_ws/flightmare_ws/build/flightlib
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_flightlib_gtest_flightlib_tests "/root/workspace/catkin_ws/flightmare_ws/build/flightlib/catkin_generated/env_cached.sh" "/usr/bin/python3.6" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/root/workspace/catkin_ws/flightmare_ws/build/flightlib/test_results/flightlib/gtest-flightlib_tests.xml" "--return-code" "/root/workspace/catkin_ws/flightmare_ws/devel/lib/flightlib/flightlib_tests --gtest_output=xml:/root/workspace/catkin_ws/flightmare_ws/build/flightlib/test_results/flightlib/gtest-flightlib_tests.xml")
subdirs("externals/pybind11-src")
subdirs("/root/workspace/catkin_ws/flightmare_ws/src/flightmare/flightlib/externals/yaml-build")
subdirs("gtest")
