#include <iostream>
#include "tinyxml2.h"
#include "ResetXml.h"

using namespace std;
using namespace tinyxml2;

Cylinder::Cylinder()
{
	this->height = (float)0.2;
	this->radius = (float)0.1732;
	this->mass = (float)1.0;
	this->color = "0 0.4 0.8 1";
	this->visual_origin_xyz = "0 0 0";
	this->visual_origin_rpy = "0 0 0";
	this->collision_origin_xyz = "0 0 0";
	this->collision_origin_rpy = "0 0 0";
	this->inertial_origin_x = this->radius;
	this->inertial_origin_y = this->radius;
	this->inertial_origin_z = (float)1.0 / (float)2.0 * this->height;
	this->inertial_origin_rpy = "0 0 0";
	this->inertia_ixx = 1.0 / 12.0 * this->mass * this->height * this->height + 1.0 / 4.0 * this->mass * this->radius * this->radius;
	this->inertia_iyy = 1.0 / 12.0 * this->mass * this->height * this->height + 1.0 / 4.0 * this->mass * this->radius * this->radius;
	this->inertia_izz = 1.0 / 2.0 * this->mass * this->radius * this->radius;
	this->inertia_ixy = (float)0.0;
	this->inertia_ixz = (float)0.0;
	this->inertia_iyz = (float)0.0;
	this->i_o_x_s << this->inertial_origin_x << " " << this->inertial_origin_y << " " << this->inertial_origin_z;
	this->i_o_x_s >> this->inertial_origin_xyz;
}
Cylinder::Cylinder(float height, float radius,float mass)
{
	this->height = height;
	this->radius = radius;
	this->mass = mass;
	this->color = "0 0.4 0.8 1";
	this->visual_origin_xyz = "0 0 0";
	this->visual_origin_rpy = "0 0 0";
	this->collision_origin_xyz = "0 0 0";
	this->collision_origin_rpy = "0 0 0";
	this->inertial_origin_xyz = "0 0 0";
	this->inertial_origin_rpy = "0 0 0";
	this->inertia_ixx = 1.0 / 12.0 * this->mass * this->height * this->height + 1.0 / 4.0 * this->mass * this->radius * this->radius;
	this->inertia_iyy = 1.0 / 12.0 * this->mass * this->height * this->height + 1.0 / 4.0 * this->mass * this->radius * this->radius;
	this->inertia_izz = 1.0 / 2.0 * this->mass * this->radius * this->radius;
	this->inertia_ixy = (float)0.0;
	this->inertia_ixz = (float)0.0;
	this->inertia_iyz = (float)0.0;
}

void update(const char* xmlPath, Cylinder* Cylinder)
{
	XMLDocument doc;
	if (doc.LoadFile(xmlPath) != 0)
	{
		cout << "´ò¿ªÊ§°Ü£¡" << endl;
		return;
	}
	XMLElement* root = doc.RootElement();
	XMLElement* link = root->FirstChildElement("link");

	XMLElement* visual = link->FirstChildElement("visual");
	XMLElement* visual_geometry = visual->FirstChildElement("geometry");
	XMLElement* visual_cylinder = visual_geometry->FirstChildElement("cylinder");
	visual_cylinder->SetAttribute("radius", Cylinder->radius);
	visual_cylinder->SetAttribute("length", Cylinder->height);

	XMLElement* collision = link->FirstChildElement("collision");
	XMLElement* collision_geometry = collision->FirstChildElement("geometry");
	XMLElement* collision_cylinder = collision_geometry->FirstChildElement("cylinder");
	collision_cylinder->SetAttribute("radius", Cylinder->radius);
	collision_cylinder->SetAttribute("length", Cylinder->height);

	XMLElement* inertial = link->FirstChildElement("inertial");
	XMLElement* inertial_origin = inertial->FirstChildElement("origin");
	//inertial_origin->SetAttribute("xyz", Cylinder->inertial_origin_xyz.c_str());
	XMLElement* mass = inertial->FirstChildElement("mass");
	mass->SetAttribute("value", Cylinder->mass);
	XMLElement* inertia = inertial->FirstChildElement("inertia");
	inertia->SetAttribute("ixx", Cylinder->inertia_ixx);
	inertia->SetAttribute("iyy", Cylinder->inertia_iyy);
	inertia->SetAttribute("izz", Cylinder->inertia_izz);
	inertia->SetAttribute("ixy", Cylinder->inertia_ixy);
	inertia->SetAttribute("ixz", Cylinder->inertia_ixz);
	inertia->SetAttribute("iyz", Cylinder->inertia_iyz);
	doc.SaveFile(xmlPath);
}