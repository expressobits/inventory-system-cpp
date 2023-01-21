#include "item.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/global_constants.hpp>

using namespace godot;

void Item::_bind_methods() { 
    ClassDB::bind_method(D_METHOD("set_max_stack", "max_stack"), &Item::set_max_stack);
    ClassDB::bind_method(D_METHOD("get_max_stack"), &Item::get_max_stack);
    ClassDB::bind_method(D_METHOD("set_name", "name"), &Item::set_name);
    ClassDB::bind_method(D_METHOD("get_name"), &Item::get_name);
    ClassDB::bind_method(D_METHOD("set_icon", "icon"), &Item::set_icon);
    ClassDB::bind_method(D_METHOD("get_icon"), &Item::get_icon);
    ClassDB::bind_method(D_METHOD("set_objects", "objects"), &Item::set_objects);
    ClassDB::bind_method(D_METHOD("get_objects"), &Item::get_objects);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_stack"), "set_max_stack", "get_max_stack");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "objects"), "set_objects", "get_objects");
}

Item::Item() {
}

Item::~Item() {
}

// Properties
void Item::set_max_stack(const int &new_max_stack) {
	max_stack = new_max_stack;
}

int Item::get_max_stack() const {
	return max_stack;
}

void Item::set_name(const String &new_name) {
    name = new_name;
}

String Item::get_name() const {
    return name;
}

void Item::set_icon(const Ref<Texture2D> &p_icon) {
    icon = p_icon;
    notify_property_list_changed();
}

Ref<Texture2D> Item::get_icon() const {
    return icon;
}

void Item::set_objects(const Dictionary &p_objects) {
    objects = p_objects;
}

Dictionary Item::get_objects() const {
    return objects;
}
