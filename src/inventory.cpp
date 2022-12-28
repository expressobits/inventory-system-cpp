#include "inventory.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Inventory::Inventory() {
    // if(fixed_size) {
    //     for(int i = 0; i < size; i++) {
    //         Ref<Slot> slot;
    //         slot.instantiate();
    //         slots.append(slot);
    //     }
    // }
}

Inventory::~Inventory() {
}

bool Inventory::is_fixed_size() const {
    return fixed_size;
}

void Inventory::set_fixed_size(const bool &f_size) {
    fixed_size = f_size;
}

Array Inventory::get_slots() const {
	return slots;
}

void Inventory::set_slots(const Array &p_slots) {
	slots = p_slots;
}

int Inventory::add(const Ref<Item> &p_item, const int &p_amount) {
	int amount_in_interact = p_amount;
	for(int i = 0; i < slots.size(); i++) {
        Ref<Slot> slot = slots[i];
        amount_in_interact = slot->add(p_item, amount_in_interact);
    }
	if(amount_in_interact > 0 && !fixed_size) {
        Ref<Slot> slot;
		slot.instantiate();
		slots.append(slot);
        emit_signal("slot_added", slots.size() - 1);
		amount_in_interact = slot->add(p_item, amount_in_interact);
    }
    emit_signal("inventory_changed");
    return amount_in_interact;
}

int Inventory::remove(const Ref<Item> &p_item, const int &p_amount) {
	int amount_in_interact = p_amount;
    for(int i = slots.size() - 1; i >= 0; i--) {
		Ref<Slot> slot = slots[i];
		amount_in_interact = slot->remove(p_item, amount_in_interact);
        if(slot->is_empty() && !fixed_size) {
            slots.remove_at(i);
            emit_signal("slot_removed", i);
        }
    }
	emit_signal("inventory_changed");
	return amount_in_interact;
}

bool Inventory::contains(const Ref<Item> &item, const int &amount) const {
    return false;
}

void Inventory::clear() {
    slots.clear();
    emit_signal("inventory_changed");
}

void Inventory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_fixed_size"), &Inventory::is_fixed_size);
    ClassDB::bind_method(D_METHOD("set_fixed_size","fixed_size"), &Inventory::set_fixed_size);
    ClassDB::bind_method(D_METHOD("get_slots"), &Inventory::get_slots);
    ClassDB::bind_method(D_METHOD("set_slots", "slots"), &Inventory::set_slots);
    ClassDB::bind_method(D_METHOD("contains", "item", "amount"), &Inventory::contains);
    ClassDB::bind_method(D_METHOD("add", "item", "amount"), &Inventory::add);
    ClassDB::bind_method(D_METHOD("remove", "item", "amount"), &Inventory::remove);
    ClassDB::bind_method(D_METHOD("clear"), &Inventory::clear);

    ADD_SIGNAL(MethodInfo("inventory_changed"));
    ADD_SIGNAL(MethodInfo("slot_added", PropertyInfo(Variant::INT, "slot_index")));
    ADD_SIGNAL(MethodInfo("slot_removed", PropertyInfo(Variant::INT, "slot_index")));

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fixed_size"), "set_fixed_size", "is_fixed_size");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "slots"), "set_slots", "get_slots");
}