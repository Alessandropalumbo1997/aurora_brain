# CMake generated Testfile for 
# Source directory: /home/masta-p/aurora_test_ws/src/brain
# Build directory: /home/masta-p/aurora_test_ws/src/brain/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_brain_roslaunch-check_launch "/home/masta-p/aurora_test_ws/src/brain/build/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/masta-p/aurora_test_ws/src/brain/build/test_results/brain/roslaunch-check_launch.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/masta-p/aurora_test_ws/src/brain/build/test_results/brain" "/opt/ros/melodic/share/roslaunch/cmake/../scripts/roslaunch-check -o \"/home/masta-p/aurora_test_ws/src/brain/build/test_results/brain/roslaunch-check_launch.xml\" \"/home/masta-p/aurora_test_ws/src/brain/launch\" ")
subdirs("gtest")
