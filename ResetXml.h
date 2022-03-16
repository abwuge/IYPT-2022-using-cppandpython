#pragma once

#include <string>
#include <sstream>

using namespace std;

class Cylinder
{
public:
	Cylinder();
	Cylinder(double, double, double);
private:
	double height;
	double radius;
	double mass;
	double color_r;
	double color_g;
	double color_b;
	double color_a;
	string color;
	stringstream c_s;
	double visual_origin_x;
	double visual_origin_y;
	double visual_origin_z;
	string visual_origin_xyz;
	stringstream v_o_x_s;
	double visual_origin_roll;
	double visual_origin_pitch;
	double visual_origin_yaw;
	string visual_origin_rpy;
	stringstream v_o_r_s;
	double collision_origin_x;
	double collision_origin_y;
	double collision_origin_z;
	string collision_origin_xyz;
	stringstream c_o_x_s;
	double collision_origin_roll;
	double collision_origin_pitch;
	double collision_origin_yaw;
	string collision_origin_rpy;
	stringstream c_o_r_s;
	double inertial_origin_x;
	double inertial_origin_y;
	double inertial_origin_z;
	string  inertial_origin_xyz;
	stringstream i_o_x_s;
	double inertial_origin_roll;
	double inertial_origin_pitch;
	double inertial_origin_yaw;
	string  inertial_origin_rpy;
	stringstream i_o_r_s;
	double inertia_ixx;
	double inertia_iyy;
	double inertia_izz;
	double inertia_ixy;
	double inertia_ixz;
	double inertia_iyz;
	friend void update(const char*, Cylinder*);
};

void update(const char*, Cylinder*);
