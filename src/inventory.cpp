#include "inventory.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/object.hpp>

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

int Inventory::add_to_slot(const int &p_slot_index, const Ref<Item> &p_item, const int &p_amount) {
    Dictionary slot = slots[p_slot_index];
    Ref<Item> item = Ref<Item>(slot["item"]);
    if(p_amount <= 0 || (item != p_item && item != NULL)) {
        return p_amount;
    }
    int _amount_to_add = godot::Math::min(p_amount, p_item->get_max_stack() - int(slot["amount"]));
    slot["amount"] = int(slot["amount"]) + _amount_to_add;
    // TODO Check if remove item information
    if(_amount_to_add > 0 && item == NULL)
    {
        slot["item"] = p_item;
    }
    return p_amount - _amount_to_add;
}

int Inventory::remove_from_slot(const int &p_slot_index, const Ref<Item> &p_item, const int &p_amount) {
    Dictionary slot = slots[p_slot_index];
    Ref<Item> item = Ref<Item>(slot["item"]);
    if(p_amount <= 0 || (item != p_item && item != NULL))
    {
        return p_amount;
    }
    int amount_to_remove = godot::Math::min(p_amount, int(slot["amount"]));
    slot["amount"] = int(slot["amount"]) - amount_to_remove;
    //TODO Check if remove item information
    if(int(slot["amount"]) <= 0) {
        slot["item"] = NULL;
    }
    return p_amount - amount_to_remove;
}

Inventory::~Inventory() {
}

bool Inventory::is_fixed_size() const {
    return fixed_size;
}

void Inventory::set_fixed_size(const bool &f_size) {
    fixed_size = f_size;
}

TypedArray<Dictionary> Inventory::get_slots() const {
	return slots;
}

void Inventory::set_slots(const TypedArray<Dictionary> &p_slots) {
	slots = p_slots;
}

int Inventory::add(const Ref<Item> &p_item, const int &p_amount) {
	int amount_in_interact = p_amount;
    int i = 0;
	for(;i < slots.size(); i++) {
        Dictionary slot = slots[i];
        amount_in_interact = add_to_slot(i, p_item, amount_in_interact);
    }
	if(amount_in_interact > 0 && !fixed_size) {
        Dictionary slot;
		slots.append(slot);
        emit_signal("slot_added", slots.size() - 1);
		amount_in_interact = add_to_slot(i, p_item, amount_in_interact);
        if(slots.size() == 0) {
            emit_signal("emptied");
        }
    }
    emit_signal("inventory_changed");
    return amount_in_interact;
}

int Inventory::remove(const Ref<Item> &p_item, const int &p_amount) {
	int amount_in_interact = p_amount;
    for(int i = slots.size() - 1; i >= 0; i--) {
		Dictionary slot = slots[i];
		amount_in_interact = remove_from_slot(i, p_item, amount_in_interact);
        if(int(slot["amount"]) == 0 && !fixed_size) {
            slots.remove_at(i);
            emit_signal("slot_removed", i);
            if(slots.size() == 0) {
                emit_signal("emptied");
            }
        }
    }
	emit_signal("inventory_changed");
	return amount_in_interact;
}

bool Inventory::contains(const Ref<Item> &p_item, const int &p_amount) const {
    int amount_in_inventory = 0;
    for(int i = 0;i < slots.size(); i++) {
        Dictionary slot = slots[i];
        if(Ref<Item>(slot["item"]) == p_item) {
            amount_in_inventory += int(slot["amount"]);
            if(amount_in_inventory > p_amount) {
                return true;
            }
        }
    }
    return false;
}

int Inventory::get_amount_of(const Ref<Item> &p_item, const int &p_amount) const {
    int amount_in_inventory = 0;
    for(int i = 0;i < slots.size(); i++) {
        Dictionary slot = slots[i];
        if(Ref<Item>(slot["item"]) == p_item) {
            amount_in_inventory += int(slot["amount"]);
        }
    }
    return amount_in_inventory;
}

void Inventory::clear() {
    slots.clear();
    emit_signal("inventory_changed");
    emit_signal("emptied");
}

void Inventory::_bind_methods() {
    ClassDB::bind_method(D_METHOD("is_fixed_size"), &Inventory::is_fixed_size);
    ClassDB::bind_method(D_METHOD("set_fixed_size","fixed_size"), &Inventory::set_fixed_size);
    ClassDB::bind_method(D_METHOD("get_slots"), &Inventory::get_slots);
    ClassDB::bind_method(D_METHOD("set_slots", "slots"), &Inventory::set_slots);
    ClassDB::bind_method(D_METHOD("contains", "item", "amount"), &Inventory::contains, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("get_amount_of", "item", "amount"), &Inventory::get_amount_of, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("add", "item", "amount"), &Inventory::add, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("remove", "item", "amount"), &Inventory::remove, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("clear"), &Inventory::clear);

    ADD_SIGNAL(MethodInfo("inventory_changed"));
    ADD_SIGNAL(MethodInfo("slot_added", PropertyInfo(Variant::INT, "slot_index")));
    ADD_SIGNAL(MethodInfo("slot_removed", PropertyInfo(Variant::INT, "slot_index")));

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "fixed_size"), "set_fixed_size", "is_fixed_size");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "slots"), "set_slots", "get_slots");
}