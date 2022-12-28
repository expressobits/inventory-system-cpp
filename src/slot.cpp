#include "slot.h"
#include <godot_cpp/classes/global_constants.hpp>

using namespace godot;

Slot::Slot() {

}

Slot::~Slot() {

}

void Slot::set_item(const Ref<Item> &new_item) {
    item = new_item;
}

Ref<Item> Slot::get_item() const {
    return item;
}

void Slot::set_amount(const int &new_amount) {
    amount = new_amount;
}

int Slot::get_amount() const {
    return amount;
}

bool Slot::is_empty() const {
    return amount == 0;
}

int Slot::add(const Ref<Item> &item, const int &amount) {
    if(amount <= 0 || (this->item != item && this->item != nullptr)) {
        return amount;
    }
    int _amount_to_add = godot::Math::min(amount, item->get_max_stack() - this->amount);
    this->amount += _amount_to_add;
    // TODO Check if remove item information
    if(_amount_to_add > 0 && this->item == NULL)
    {
        this->item = item;
    }
    return amount - _amount_to_add;
}

int Slot::remove(const Ref<Item> &item, const int &amount) {
    if(amount <= 0 || (this->item != item && this->item != nullptr))
    {
        return amount;
    }
    int amount_to_remove = godot::Math::min(amount, this->amount);
    this->amount -= amount_to_remove;
    //TODO Check if remove item information
    if(this->amount <= 0) {
        this->set_item(nullptr);
    }
    return amount - amount_to_remove;
}

void Slot::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &Slot::get_item);
    ClassDB::bind_method(D_METHOD("set_item", "item"), &Slot::set_item);
    ClassDB::bind_method(D_METHOD("get_amount"), &Slot::get_amount);
    ClassDB::bind_method(D_METHOD("set_amount", "amount"), &Slot::set_amount);
    ClassDB::bind_method(D_METHOD("add", "item", "amount"), &Slot::add);
    ClassDB::bind_method(D_METHOD("remove", "item", "amount"), &Slot::remove);
    ClassDB::bind_method(D_METHOD("is_empty"), &Slot::is_empty);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item"), "set_item", "get_item");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "amount"), "set_amount", "get_amount");
}