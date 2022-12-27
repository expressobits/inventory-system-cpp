#include "inventory.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Inventory::Inventory() {
}

Inventory::~Inventory() {
}

bool Inventory::is_fixed_size() const {
    return fixed_size;
}

void Inventory::set_fixed_size(const bool &f_size) {
    fixed_size = f_size;
}

void Inventory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_fixed_size"), &Inventory::is_fixed_size);
    ClassDB::bind_method(D_METHOD("set_fixed_size","fixed_size"), &Inventory::set_fixed_size);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fixed_size"), "set_fixed_size", "is_fixed_size");
}