#pragma once

#include <string>
#include <sstream>

using namespace std;

class Cylinder
{
public:
	Cylinder();
	Cylinder(float, float, float);
private:
	float height;
	float radius;
	float mass;
	float color_r;
	float color_g;
	float color_b;
	float color_a;
	string color;
	stringstream c_s;
	float visual_origin_x;
	float visual_origin_y;
	float visual_origin_z;
	string visual_origin_xyz;
	stringstream v_o_x_s;
	float visual_origin_roll;
	float visual_origin_pitch;
	float visual_origin_yaw;
	string visual_origin_rpy;
	stringstream v_o_r_s;
	float collision_origin_x;
	float collision_origin_y;
	float collision_origin_z;
	string collision_origin_xyz;
	stringstream c_o_x_s;
	float collision_origin_roll;
	float collision_origin_pitch;
	float collision_origin_yaw;
	string collision_origin_rpy;
	stringstream c_o_r_s;
	float inertial_origin_x;
	float inertial_origin_y;
	float inertial_origin_z;
	string  inertial_origin_xyz;
	stringstream i_o_x_s;
	float inertial_origin_roll;
	float inertial_origin_pitch;
	float inertial_origin_yaw;
	string  inertial_origin_rpy;
	stringstream i_o_r_s;
	double inertia_ixx;
	double inertia_iyy;
	double inertia_izz;
	float inertia_ixy;
	float inertia_ixz;
	float inertia_iyz;
	friend void update(const char*, Cylinder*);
};

void update(const char*, Cylinder*);
